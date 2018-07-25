#ifndef POSITION_H
#define POSITION_H

struct Position
{
	int x, y;

	bool operator==(const Position &other) const;
	bool operator!=(const Position &other) const;
};


#endif 
