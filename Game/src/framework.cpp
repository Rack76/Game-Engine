#include <functional>
#include <map>
#include <iostream>

#include "framework.h"

//engine inclues
#include "engine/events/events.h"
#include "engine/render/renderer.h"

//game includes
#include "game/game.h"

#include <SDL_events.h>
#include <SDL_timer.h>

namespace
{
	std::map<uint32_t, std::vector<std::function<void(const SDL_Event&)>>> events;
}

GameFramework::GameFramework(engine::display::Window& window)
	: m_game(std::make_unique<Game>())
{
	engine::render::Init(window);
}

GameFramework::~GameFramework()
{
	engine::render::Shutdown();
}

void GameFramework::Run()
{
	static bool quitting = false;

	while (!quitting)
	{
		SDL_Event sdlEvent;
		while (SDL_PollEvent(&sdlEvent) != 0)
		{
			if (sdlEvent.type == SDL_EventType::SDL_QUIT)
			{
				quitting = true;
				break;
			}

			if (events.count(sdlEvent.type))
			{
				for (auto& cb : events[sdlEvent.type])
				{
					cb(sdlEvent);
				}
			}
		}

		m_game->Update(0.0f);
		m_game->Render();
	}
}

void GameFramework::AddEvent(const uint32_t eventId, std::function<void(const SDL_Event&)> cb)
{
	events[eventId].push_back(cb);
}
