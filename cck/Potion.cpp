#include "stdafx.h"
#include "Potion.h"
#include "Player.h"
#include "Event.h"


Potion::Potion(Position position, PotionEffects effect)
	: Item{ 'P' , position, Item::PickupMethod::Use }, effect{ effect }
{
}


Potion::~Potion()
{
}

std::shared_ptr<Event> Potion::GetPickedUpBy(std::shared_ptr<Player> player)
{
	return player->Use(effect);
}