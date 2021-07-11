#ifndef ENGINE_RENDER_RENDERER_H
#define ENGINE_RENDER_RENDERER_H

#include <cstdint>

namespace engine
{
	namespace display
	{
		class Window;
	}

	namespace render
	{
		struct ColourRGBA
		{
			uint32_t m_r;
			uint32_t m_g;
			uint32_t m_b;
			uint32_t m_a;
		};

		struct Position
		{
			uint16_t m_x;
			uint16_t m_y;
		};

		void Init(display::Window& window);
		void Shutdown();

		void Clear();
		void SetClearColour(const ColourRGBA colour);

		void Present();

		void DrawQuad(const ColourRGBA colour, const Position pos, const uint16_t width, const uint16_t height);
	};
};

#endif