#ifndef INCLUDED_EVENT_PROCESSOR_HPP
#define INCLUDED_EVENT_PROCESSOR_HPP

#include"event_emitter.hpp"
#include"events.hpp"
#include<unordered_map>
#include<SDL.h>
#include<functional>

namespace Engine {
	class Event_processor :
		public Event_emitter<
			Events::Quit,
			Events::Mouse_motion,
			Events::Mouse_click
		>
	{
	public:
		/* Inherited from Event_emitter: 
		
		   Callback_handle add_callback();
		   void remove_callback(Callback_handle);
		*/

		void process_events();

		Event_processor();
		~Event_processor() = default;

		Event_processor(Event_processor const&) = delete;
		Event_processor& operator=(Event_processor const&) = delete;

	private:
		typedef decltype(std::declval<SDL_Event>().type) Sdl_event_id;
		
		/* Dispatchers transform SDL events into events from namespace Engine::Events, and dispatch them */
		using Dispatcher_function_type = void(SDL_Event const&);
		std::unordered_map<Sdl_event_id, std::function<Dispatcher_function_type>> dispatchers;

		template<typename> void dispatch(SDL_Event const&) = delete;
		template<> void dispatch<Events::Quit>(SDL_Event const& _event);
		template<> void dispatch<Events::Mouse_motion>(SDL_Event const& _event);
		template<> void dispatch<Events::Mouse_click>(SDL_Event const& _event);

	};
}

#endif