#pragma once

#include <string>
#include "Direction.h"


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
		return "Cannot move " + DirectionToStr(direction);
	}
};

class CannotAttack : public DirectionExeption
{
public:
	CannotAttack(Direction direction) : DirectionExeption{ direction } {}

	std::string what() const
	{
		return "Cannot attack " + DirectionToStr(direction);
	}
};

class CannotUse : public DirectionExeption
{
public:
	CannotUse(Direction direction) : DirectionExeption{ direction } {}

	std::string what() const
	{
		return "Cannot use item to the " + DirectionToStr(direction);
	}
};

class CannotParse {};