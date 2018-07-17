#include "stdafx.h"
#include "Sprite.h"
#include "Level.h"

Sprite::Sprite(char symbol, Position position)
	: symbol{ symbol }, position{ position }
{}

const Position &Sprite::GetPosition() const
{
	return position;
}

char Sprite::GetSymbol() const
{
	return symbol;
}