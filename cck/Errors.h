#pragma once

#include <string>
#include "Direction.h"
#include "Helpers.h"


class DirectionExeption
{
protected:
	Direction direction;
public:
	DirectionExeption(Direction direction) : direction{ direction } {}
	virtual ~DirectionExeption() {}
	virtual std::string what() const = 0;
};


class CannotMove : public DirectionExeption
{
public:
	CannotMove(Direction direction) : DirectionExeption{ direction } {}

	std::string what() const
	{
		return "Cannot move " + Helpers::directionToStr(direction);
	}
};

class CannotAttack : public DirectionExeption
{
public:
	CannotAttack(Direction direction) : DirectionExeption{ direction } {}

	std::string what() const
	{
		return "Cannot attack " + Helpers::directionToStr(direction);
	}
};

class CannotUse : public DirectionExeption
{
public:
	CannotUse(Direction direction) : DirectionExeption{ direction } {}

	std::string what() const
	{
		return "Cannot use item to the " + Helpers::directionToStr(direction);
	}
};

class CannotParse {};