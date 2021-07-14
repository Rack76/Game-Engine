#include"event_processor.hpp"

void Engine::Event_processor::process_events() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (auto element = dispatchers.find(event.type); element != std::cend(dispatchers)) {
			auto const& [event_type, dispatcher] = *element;
			dispatcher(event);
		}
	}
}

Engine::Event_processor::Event_processor() {
	dispatchers.emplace(SDL_QUIT, std::bind_front(&Event_processor::dispatch<Events::Quit>, this));
	dispatchers.emplace(SDL_MOUSEMOTION, std::bind_front(&Event_processor::dispatch<Events::Mouse_motion>, this));
	dispatchers.emplace(SDL_MOUSEBUTTONDOWN, std::bind_front(&Event_processor::dispatch<Events::Mouse_click>, this));
	dispatchers.emplace(SDL_MOUSEBUTTONUP, std::bind_front(&Event_processor::dispatch<Events::Mouse_click>, this));
}

template<> void Engine::Event_processor::dispatch<Engine::Events::Quit>(SDL_Event const& _event) {
	Events::Quit const event;
	(void)_event;
	post_event(event);
}

template<> void Engine::Event_processor::dispatch<Engine::Events::Mouse_motion>(SDL_Event const& _event) {
	Events::Mouse_motion const event(_event.motion.x, _event.motion.y);
	post_event(event);
}

template<> void Engine::Event_processor::dispatch<Engine::Events::Mouse_click>(SDL_Event const& _event) {
	Events::Mouse_click const event(
		_event.button.state == SDL_PRESSED ? Events::Mouse_click::Action::down : Events::Mouse_click::Action::up,
		Events::Mouse_click::Button::left /* obviously this has to be changed, I'll look it up in the docs later */
	);
	post_event(event);
}




