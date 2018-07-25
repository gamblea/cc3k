#include "stdafx.h"
#include "Potion.h"
#include "Player.h"
#include "Event.h"


bool Potion::isEqual(const Sprite & other) const
{
	try
	{
		const Potion &otherPotion = dynamic_cast<const Potion &>(other);
		if (position == otherPotion.position && effect == otherPotion.effect)
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

Potion::Potion(Position position, PotionEffects effect)
	: Item{ 'P' , position, Item::PickupMethod::Use}, effect{ effect }
{
}


Potion::~Potion()
{
}

std::string Potion::GetName() const
{
	return effect.Name;
}

std::shared_ptr<Event> Potion::GetPickedUpBy(std::shared_ptr<Player> player)
{
	return player->Use(effect);
}