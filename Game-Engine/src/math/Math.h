#pragma once

namespace Math
{
	class vec2
	{
		vec2(int x, int y) : m_x(x), m_y(y)
		{}
		int getX() { return m_x; }
		int getY() { return m_y; }
	private:
		int m_x, m_y;
	};
}