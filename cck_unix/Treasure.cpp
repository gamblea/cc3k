#include "stdafx.h"
#include "Treasure.h"
#include "Player.h"
#include "TreasureStats.h"
#include "Event.h"
#include <memory>

bool Treasure::isEqual(const Sprite & other) const
{
	try
	{
		const Treasure &otherTreasure = dynamic_cast<const Treasure &>(other);
		if (stats == otherTreasure.stats && position == otherTreasure.position)
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

Treasure::Treasure(Position position, TreasureStats stats)
	: Item{ 'G', position, Item::PickupMethod::Walkover, stats.ToBeGuarded, stats.GuardName}, stats{ stats } 
{

}

Treasure::~Treasure() {}

std::string Treasure::GetName() const
{
	return stats.Name;
}


std::shared_ptr<Event> Treasure::GetPickedUpBy(std::shared_ptr<Player> player)
{ 
	if (GetGuarded())
	{
		return std::make_shared<Event>(Event::EventType::See , stats.Name + "is still guarded by the " + GetGuardName() + ".");
	}
	else return player->Use(stats);
}
