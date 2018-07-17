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
protected:
	Position position;
public:
	Sprite(char symbol, Position position);
	virtual const Position &GetPosition() const;
	char GetSymbol() const;
	virtual ~Sprite() = 0;
};

#endif
