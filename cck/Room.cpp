#include "stdafx.h"
#include "Room.h"

#include "Position.h"
#include "Helpers.h"


Room::Room()
{
}


Room::~Room()
{
}

void Room::AddPosition(Position pos)
{
	positions.emplace_back(pos);
}

Position Room::GetRandomPositionInRoom() const
{
	int elementIndex = Helpers::getRandom(0, positions.size() - 1);
	return positions.at(elementIndex);
}

bool Room::ContainsPosition(const Position & position)
{
	for (Position &pos : positions)
	{
		if (position == pos)
			return true;
	}
	return false;
}

std::ostream &operator<<(std::ostream &os, Room &room)
{
	for (auto pos : room.positions)
	{
		os << "(" << pos.x << "," << pos.y << ")" << std::endl;
	}

	return os;
}