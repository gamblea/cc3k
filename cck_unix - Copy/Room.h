#ifndef ROOM_H
#define ROOM_H
#include <vector>
#include <iostream>

struct Position;

class Room
{
private:
	std::vector<Position> positions;

public:
	Room();
	~Room();

	void AddPosition(Position pos);
	Position GetRandomPositionInRoom() const;

	bool ContainsPosition(const Position &pos);
	

	friend std::ostream &operator<<(std::ostream &os, Room &room);
};

std::ostream &operator<<(std::ostream &os, Room &room);
#endif
