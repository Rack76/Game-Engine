#include<iostream>
#include"window.hpp"
#include<thread>

/* Thank you SDL, but this doesn't compile with your main */
#undef main

int main() {
	Engine::Window window("Test", 500, 500);
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	return 0;
}
