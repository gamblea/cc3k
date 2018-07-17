#pragma once
#include "Sprite.h"
#include <memory>

class Player;
class Event;

class Item : public Sprite
{
public:
	enum class PickupMethod { Walkover, Use };
private:
	PickupMethod method;
public:
	Item(char symbol, Position position, PickupMethod method);
	virtual ~Item() = 0;

	Item::PickupMethod GetPickupMethod();
	virtual std::shared_ptr<Event> GetPickedUpBy(std::shared_ptr<Player> player) = 0;
};

