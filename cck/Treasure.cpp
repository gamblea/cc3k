#include "stdafx.h"
#include "Treasure.h"
#include "Player.h"
#include "TreasureStats.h"


Treasure::Treasure(Position position, TreasureStats stats) 
	: Item{ 'G', position, Item::PickupMethod::Walkover, stats.ToBeGuarded, stats.GuardName}, stats{ stats } 
{

}

Treasure::~Treasure() {}


std::shared_ptr<Event> Treasure::GetPickedUpBy(std::shared_ptr<Player> player)
{ 
	return player->Use(stats);
}
