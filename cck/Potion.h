#pragma once
#include "Item.h"
#include "PotionEffects.h"

class Player;

class Potion :
	public Item
{
private:
	PotionEffects effect;
	virtual bool isEqual(const Sprite& other) const;
public:
	Potion(Position position, PotionEffects effect);
	virtual ~Potion();

	virtual std::shared_ptr<Event> GetPickedUpBy(std::shared_ptr<Player> player);
};

