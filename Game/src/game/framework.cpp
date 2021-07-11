#include <functional>
#include <map>
#include <iostream>

#include "framework.h"

#include "engine/events/events.h"
#include "engine/render/renderer.h"

#include <SDL_events.h>
#include <SDL_timer.h>

std::map<int, std::vector<std::function<void(const SDL_Event&)>>> events;
constexpr uint32_t MOUSE_EVENTS = SDL_EventType::SDL_MOUSEBUTTONDOWN | SDL_EventType::SDL_MOUSEBUTTONUP | SDL_EventType::SDL_MOUSEMOTION | SDL_EventType::SDL_MOUSEWHEEL;

//quad
static engine::render::Position s_quadPosition;
//

//#todo move events/gameplay out of the framework, this is just for testing
//#todo convert this to use Event_emitter - currently there is no way to only emit to specific listeners
static void OnMouseEvent(const SDL_Event& sdlEvent)
{
	switch (sdlEvent.type)
	{
	case SDL_MOUSEMOTION:
	{
		const SDL_MouseMotionEvent& motionEvent = sdlEvent.motion;

		s_quadPosition = { motionEvent.x, motionEvent.y };
		break;
	}

	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
	{
		const SDL_MouseButtonEvent& buttonEvent = sdlEvent.button;

		break;
	}

	case SDL_MOUSEWHEEL:
	{
		const SDL_MouseWheelEvent& wheelEvent = sdlEvent.wheel;
		break;
	}

	default:
		//unsupported, only mouse events
		break;
	}
}

GameFramework::GameFramework(engine::display::Window& window)
{
	engine::render::Init(window);

	events.insert({ MOUSE_EVENTS, {std::bind(&OnMouseEvent, std::placeholders::_1)} });
}

GameFramework::~GameFramework()
{
	engine::render::Shutdown();
}

void GameFramework::Run()
{
	while (true)
	{
		SDL_Event sdlEvent;
		while (SDL_PollEvent(&sdlEvent) != 0)
		{
			if (sdlEvent.type & MOUSE_EVENTS)
			{
				for (auto& cb : events[MOUSE_EVENTS])
				{
					cb(sdlEvent);
				}
			}
		}

		engine::render::SetClearColour({ 255, 0, 0, 255 });
		engine::render::Clear();
		engine::render::DrawQuad({ 0, 0, 255, 255 }, s_quadPosition, 100, 100);
		engine::render::Present();
	}


}
