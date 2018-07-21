#include "stdafx.h"
#include "Treasure.h"
#include "Player.h"


Treasure::Treasure(Position position, TreasureStats stats) 
	: Item{'G', position, Item::PickupMethod::Walkover, stats.CanBePickedUp}, stats { stats }
{

}

Treasure::~Treasure() {}


std::shared_ptr<Event> Treasure::GetPickedUpBy(std::shared_ptr<Player> player)
{ 
	return player->Use(stats);
}
