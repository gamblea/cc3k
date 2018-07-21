#pragma once
#include "Item.h"
class Stairs : public Item
{
public:
	Stairs(Position position);
	virtual ~Stairs();

	std::shared_ptr<Event> GetPickedUpBy(std::shared_ptr<Player> player) override;
};

