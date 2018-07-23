#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include "Position.h"
#include <memory>
#include "Direction.h"

class Level;

class Sprite
{
private:
	char symbol;

	virtual bool isEqual(const Sprite& other) const = 0;
protected:
	Position position;
public:
	Sprite(char symbol, Position position);
	virtual const Position &GetPosition() const;
	virtual void Move(Position pos);
	char GetSymbol() const;
	virtual ~Sprite() = 0;

	bool operator==(const Sprite& other) const;
	bool operator!=(const Sprite& other) const;
};

#endif
