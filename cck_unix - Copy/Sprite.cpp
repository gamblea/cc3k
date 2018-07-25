
#include "Sprite.h"
#include "Level.h"

Sprite::Sprite(char symbol, Position position)
	: symbol{ symbol }, position{ position }
{}

Sprite::~Sprite()
{

}

const Position &Sprite::GetPosition() const
{
	return position;
}

void Sprite::Move(Position pos)
{
	position = pos;
}

char Sprite::GetSymbol() const
{
	return symbol;
}

bool Sprite::operator==(const Sprite& other) const
{
	
	return typeid(*this) == typeid(other) && isEqual(other);
}

bool Sprite::operator!=(const Sprite & other) const
{
	return !operator==(other);
}
