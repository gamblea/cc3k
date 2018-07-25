#include "stdafx.h"
#include "Helpers.h"
#include "Direction.h"

#include <string>
#include <cstdlib>
#include <stdexcept>


bool Helpers::stringToBool(std::string str)
{
	if (str == "true") return true;
	else if (str == "false") return false;
	else throw std::runtime_error("Expected true or false");
}

std::string Helpers::directionToStr(Direction direction)
{
	switch (direction)
	{
	case Direction::N:
		return "North";
		break;
	case Direction::S:
		return "South";
		break;
	case Direction::E:
		return "East";
		break;
	case Direction::W:
		return "West";
		break;
	case Direction::NW:
		return "Northwest";
		break;
	case Direction::SW:
		return "Southwest";
		break;
	case Direction::NE:
		return "Northeast";
		break;
	case Direction::SE:
		return "Southeast";
		break;
	case Direction::None:
		return "None";
		break;
	default:
		throw std::runtime_error("Invalid direction!");
		break;
	}
}

Direction Helpers::strToDirection(const std::string &str)
{
	if (str == "N" || str == "north" || str == "n")
	{
		return Direction::N;
	}
	else if (str == "S" || str == "south" || str == "s")
	{
		return Direction::S;
	}
	else if (str == "W" || str == "west" || str == "w")
	{
		return Direction::W;
	}
	else if (str == "E" || str == "east" || str == "e")
	{
		return Direction::E;
	}
	else if (str == "NW" || str == "northwest" || str == "nw")
	{
		return Direction::NW;
	}
	else if (str == "NE" || str == "northeast" || str == "ne")
	{
		return Direction::NE;
	}
	else if (str == "SW" || str == "southwest" || str =="sw")
	{
		return Direction::SW;
	}
	else if (str == "SE" || str == "Southeast" || str == "se")
	{
		return Direction::SE;
	}
	else return Direction::None;
}

int Helpers::getRandom(int min, int max)
{
	if (min > max) std::swap(min, max);
	int range = max - min + 1;
	int random = rand() % range;
	return random + min;
}