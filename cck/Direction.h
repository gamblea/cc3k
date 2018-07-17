#pragma once
#ifndef DIRECTION_H
#define DIRECTION_H

enum class Direction { N, S, E, W, NW, SW, NE, SE, None};

std::string DirectionToStr(Direction direction)
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


#endif