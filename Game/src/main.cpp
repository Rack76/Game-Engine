#include<iostream>
#include"window.hpp"
#include"renderer_2d.hpp"
#include"event_processor.hpp"
#include<thread>

/* Thank you SDL, but this doesn't compile with your main */
#undef main

int main() {
	using namespace Engine;
	using enum Engine::Renderer_2d::Primitive;

	Window window("Test", 500, 500);
	Renderer_2d renderer(window);
	Event_processor event_processor;
	
	bool running = true;
	Quad cursor_following_quad(0, 0, 100, 100);
	Colour cursor_following_quad_colour(0, 0, 0, 255);
	
	event_processor.add_callback([&](Events::Quit const&) { running = false; });

	event_processor.add_callback([&](Events::Mouse_motion const& _event) {
		cursor_following_quad.x = _event.new_x;
		cursor_following_quad.y = _event.new_y;
	});

	event_processor.add_callback([&](Events::Mouse_click const& _event) {
		if (_event.action == Events::Mouse_click::Action::down) {
			cursor_following_quad_colour.r = 255;
			cursor_following_quad_colour.g = 255;
			cursor_following_quad_colour.b = 255;
		} else if (_event.action == Events::Mouse_click::Action::up) {
			cursor_following_quad_colour.r = 0;
			cursor_following_quad_colour.g = 0;
			cursor_following_quad_colour.b = 0;
		}
	});

	while (running) {
		renderer.clear({ 0, 50, 50, 255 });
		renderer.render<quad>(cursor_following_quad, cursor_following_quad_colour);
		renderer.render_present();

		event_processor.process_events();
		
		/* Dumb way to cap FPS, but it'll be changed later */
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

}
