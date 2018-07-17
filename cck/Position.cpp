#include "stdafx.h"
#include "Position.h"

bool Position::operator==(const Position &other) const
{
	if (x == other.x && y == other.y)
		return true;
	else
		return false;
}

bool Position::operator!=(const Position &other) const
{
	return !(*this == other);
}

