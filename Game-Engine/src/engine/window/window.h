#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include <cstdint>
#include <string>

namespace engine
{
	namespace display
	{
		using WindowHandle = void*;

		class Window
		{
		public:
			Window(std::string_view windowName, const uint16_t width, const uint16_t height);
			~Window();

			[[nodiscard]] uint16_t GetWidth() const { return m_width; }
			[[nodiscard]] uint16_t GetHeight() const { return m_height; }

			[[nodiscard]] WindowHandle GetHandle() const { return m_handle; }

		private:
			std::string		m_windowName;
			uint16_t		m_width;
			uint16_t		m_height;

			WindowHandle	m_handle;
		};

		void UpdateWindow(Window& window);
	}
}
#endif