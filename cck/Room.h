#pragma once
#include <vector>

class Position;

class Room
{
private:
	std::vector<Position> positions;

public:
	Room();
	~Room();


	void AddPosition(Position pos);
	Position GetRandomPosition();

	bool ContainsPosition(const Position &pos);
	

	friend std::ostream &operator<<(std::ostream &os, Room &room);
};

std::ostream &operator<<(std::ostream &os, Room &room);