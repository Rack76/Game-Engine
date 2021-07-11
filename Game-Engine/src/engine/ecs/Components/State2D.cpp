#include "State2D.h"

void State2D::read(std::stringstream& stream)
{
	stream >> position.x >> position.y;
}