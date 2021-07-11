#pragma once

namespace Math
{
	class vec2
	{
	public:
		vec2(float x, float y) : x(x), y(y)
		{}
		float x, y;
	};

	class vec3
	{
	public:
		vec3(float x, float y, float z) : x(x), y(y), z(z)
		{}
		float x, y, z;
	};
}