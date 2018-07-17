#include "stdafx.h"
#include "Stairs.h"
#include "Player.h"


Stairs::Stairs(Position position) 
	: Item{'\\',position,PickupMethod::Walkover}
{
}


Stairs::~Stairs()
{
}

std::shared_ptr<Event> Stairs::GetPickedUpBy(std::shared_ptr<Player> player)
{
	player->Use(*this);
}
