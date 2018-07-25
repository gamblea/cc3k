#ifndef HELPERS_H
#define HELPERS_H
#include <string>

enum class Direction;


namespace Helpers
{
	bool stringToBool(std::string str);
	std::string directionToStr(Direction direction);
	Direction strToDirection(const std::string &str);
	int getRandom(int min, int max);
}
#endif
