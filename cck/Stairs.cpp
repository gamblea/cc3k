#include "stdafx.h"
#include "Stairs.h"
#include "Player.h"


bool Stairs::isEqual(const Sprite & other) const
{
	try
	{
		const Stairs &otherStairs = dynamic_cast<const Stairs &>(other);
		if (position == otherStairs.position && GetSymbol() == other.GetSymbol())
		{
			return true;
		}
		else return false;
	}
	catch (const std::bad_cast&)
	{
		return false;
	}
}

Stairs::Stairs(Position position)
	: Item{'\\',position,PickupMethod::Walkover}
{
}


Stairs::~Stairs()
{
}

std::shared_ptr<Event> Stairs::GetPickedUpBy(std::shared_ptr<Player> player)
{
	return player->Use(*this);
}
