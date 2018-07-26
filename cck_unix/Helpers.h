#ifndef HELPERS_H
#define HELPERS_H
#include <string>
#include "Position.h"

enum class Direction;


namespace Helpers
{
	bool stringToBool(std::string str);
	std::string directionToStr(Direction direction);
	Direction strToDirection(const std::string &str);
	int getRandom(int min, int max);

	bool OneRadiiAway(Position pos1, Position pos2);
}
#endif
