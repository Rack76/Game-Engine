#ifndef INCLUDED_EVENT_EMITTER_HPP
#define INCLUDED_EVENT_EMITTER_HPP

#include<concepts>
#include<memory>
#include<stdexcept>
#include<list>
#include<ranges>
#include<vector>
#include<tuple>

namespace Engine {
    namespace Internal {
        namespace Callback_impl {
            template<typename _Argument>
            class Invoke_interface {
            public:
                Invoke_interface() = default;

                virtual void invoke(_Argument& _argument) = 0;
                virtual void invoke(_Argument&& _argument) = 0;
                virtual void invoke(_Argument const& _argument) = 0;

                virtual ~Invoke_interface() = default;
            };

            template<typename _Callable, typename _Argument>
            class Callable_wrapper : public Invoke_interface<_Argument> {
            public:
                Callable_wrapper(auto&& _callable) : callable(std::forward<decltype(_callable)>(_callable)) { }

                virtual void invoke(_Argument& _argument) override {
                    if constexpr (std::invocable<_Callable, _Argument&>) callable(_argument);
                    else throw std::logic_error("Invalid callback");
                }

                virtual void invoke(_Argument&& _argument) override {
                    if constexpr (std::invocable<_Callable, _Argument&&>) callable(std::move(_argument));
                    else throw std::logic_error("Invalid callback");
                }

                virtual void invoke(_Argument const& _argument) override {
                    if constexpr (std::invocable<_Callable, _Argument const&>) callable(_argument);
                    else throw std::logic_error("Invalid callback");
                }

                virtual ~Callable_wrapper() override = default;

                Callable_wrapper(Callable_wrapper const&) = default;
                Callable_wrapper& operator=(Callable_wrapper const&) = default;
                Callable_wrapper(Callable_wrapper&&) = default;
                Callable_wrapper& operator=(Callable_wrapper&&) = default;

            private:
                _Callable callable;

            };

            namespace Concepts {
                template<typename _Type, typename _Event>
                concept Callback =
                    std::invocable<_Type, _Event&> ||
                    std::invocable<_Type, _Event&&>;
            }
        }

        template<typename _Event> requires std::same_as<_Event, typename std::decay<_Event>::type>
		class Callback {
		public:
			typedef _Event Event_type;

			Callback(Callback_impl::Concepts::Callback<_Event> auto&& _callable) :
				callable(
					std::make_unique<Callback_impl::Callable_wrapper<typename std::decay<decltype(_callable)>::type, _Event>>(
						std::forward<decltype(_callable)>(_callable)
						)
				)
			{ }

			void operator()(auto&& _argument) {
				callable->invoke(std::forward<decltype(_argument)>(_argument));
			}

			~Callback() = default;

			Callback(Callback&&) = default;
			Callback& operator=(Callback&&) = default;

		private:
			std::unique_ptr<Callback_impl::Invoke_interface<_Event>> callable;

		};

		template<typename>
		struct Callback_ctad_helper;

		template<typename _Callable, typename _Event, typename _Return>
		struct Callback_ctad_helper<_Return(_Callable::*)(_Event)> { typedef _Event Type; };

		template<typename _Callable, typename _Event, typename _Return>
		struct Callback_ctad_helper<_Return(_Callable::*)(_Event) const> { typedef _Event Type; };

		template<typename _Callable, typename _Event, typename _Return>
		struct Callback_ctad_helper<_Return(_Callable::*)(_Event) noexcept> { typedef _Event Type; };

		template<typename _Callable, typename _Event, typename _Return>
		struct Callback_ctad_helper<_Return(_Callable::*)(_Event) const noexcept> { typedef _Event Type; };

		template<typename _Event>
		Callback(auto (*)(_Event))->Callback<typename std::decay<_Event>::type>;

		template<typename _Callable>
		Callback(_Callable)->Callback<typename std::decay<typename Callback_ctad_helper<decltype(&_Callable::operator())>::Type>::type>;



		template<typename _Event>
		class Event_emitter_base {
		private:
			/* std::list never invalidates iterators */
			std::list<Callback<_Event>> callbacks;

			typedef typename decltype(callbacks)::const_iterator Callback_handle;

			std::vector<Callback_handle> callbacks_for_removal;

		protected:

			Event_emitter_base() = default;

			Callback_handle add_callback(Callback<_Event>&& _callback) {
				return callbacks.emplace(std::cend(callbacks), std::move(_callback));
			}

			void remove_callback(Callback_handle const& _handle) {
				callbacks_for_removal.emplace_back(_handle);
			}

			void post_event(auto&& _event) {
				/* All of this magic allows callbacks to register and deregister other callbacks, or themselves */
				/* If that happens, changes are only visible in future calls to post_event() */

				for (auto const& callback : callbacks_for_removal) callbacks.erase(callback);
				callbacks_for_removal.clear();

				/* This will only iterate over the original range of callbacks, whether or not this range changes during iteration */
				//for (auto& callback : callbacks | std::views::take(std::ssize(callbacks))) callback(std::forward<decltype(_event)>(_event));
				/* For whatever reason, the above line does not compile on MSVC, even though GCC compiles it without problems */
				/* This might be a MSVC bug, there's no reason for it not to compile... Especially that GCC doesn't complain at all */
				/* Here's an horribly ugly workaround: */
				auto size = std::ssize(callbacks);
				auto current = std::begin(callbacks);
				for (int i = 0; i < size; ++i, ++current) (*current)(std::forward<decltype(_event)>(_event));
			}

			~Event_emitter_base() = default;

			Event_emitter_base(Event_emitter_base const&) = delete;
			Event_emitter_base& operator= (Event_emitter_base const&) = delete;
			Event_emitter_base(Event_emitter_base&&) = default;
			Event_emitter_base& operator= (Event_emitter_base&&) = default;

		};

    }


    template<typename... _Events> requires (... && std::same_as<_Events, typename std::decay<_Events>::type>)
	class Event_emitter : private Internal::Event_emitter_base<_Events>... {
	public:
		typedef std::tuple<_Events...> Events_tuple;

		decltype(auto) add_callback(auto&& _callback) {
			return add_callback_impl(Internal::Callback(std::forward<decltype(_callback)>(_callback)));
		}

		template<typename _Callback_handle>
		void remove_callback(_Callback_handle const& _callback_handle) {
			Internal::Event_emitter_base<typename std::iterator_traits<_Callback_handle>::value_type::Event_type>::remove_callback(_callback_handle);
		}

	protected:
		Event_emitter() = default;

		void post_event(auto&& _event) {
			Internal::Event_emitter_base<typename std::decay<decltype(_event)>::type>::post_event(std::forward<decltype(_event)>(_event));
		}

		~Event_emitter() = default;

		Event_emitter(Event_emitter const&) = delete;
		Event_emitter& operator= (Event_emitter const&) = delete;
		Event_emitter(Event_emitter&&) = default;
		Event_emitter& operator= (Event_emitter&&) = default;

	private:
		template<typename _Event>
		decltype(auto) add_callback_impl(Internal::Callback<_Event>&& _callback) {
			return Internal::Event_emitter_base<_Event>::add_callback(std::move(_callback));
		}
    };
}


#endif