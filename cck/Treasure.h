#pragma once
#include "Item.h"
#include "TreasureStats.h"
#include "CharacterStats.h"

class Treasure :
	public Item
{
private:
	TreasureStats stats;

	virtual bool isEqual(const Sprite& other) const;
public:
	Treasure(Position position, TreasureStats stats);
	virtual ~Treasure();

	virtual std::shared_ptr<Event> GetPickedUpBy(std::shared_ptr<Player> player);
};

