#include<iostream>
#include"window.hpp"
#include"renderer_2d.hpp"
#include<thread>

/* Thank you SDL, but this doesn't compile with your main */
#undef main

int main() {
	using namespace Engine;
	using enum Engine::Renderer_2d::Primitive;

	Window window("Test", 500, 500);
	Renderer_2d renderer(window);
	
	renderer.clear({ 0, 100, 0, 255 });
	renderer.render<quad>(Quad{ 100, 100, 200, 100 }, Colour{ 0, 0, 100, 255 });
	renderer.render_present();

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	return 0;
}
