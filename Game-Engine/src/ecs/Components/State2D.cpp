#include "State2D.h"

void State::read(std::stringstream& stream)
{
	stream >> position.x >> position.y;
}