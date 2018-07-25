#ifndef SPRITE_H
#define SPRITE_H

#include "Position.h"
#include <memory>
#include "Direction.h"
#include <string>

class Level;

class Sprite
{
private:
	virtual bool isEqual(const Sprite& other) const = 0;
protected:
	char symbol;
	Position position;
public:
	Sprite(char symbol, Position position);
	virtual const Position &GetPosition() const;
	virtual void Move(Position pos);
	char GetSymbol() const;

	virtual std::string GetName() const = 0;

	virtual ~Sprite() = 0;

	bool operator==(const Sprite& other) const;
	bool operator!=(const Sprite& other) const;
};

#endif
