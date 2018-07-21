#pragma once
#include "Sprite.h"
#include <memory>


class Event;
class Player;

class Item : public Sprite
{
public:
	enum class PickupMethod { Walkover, Use };
private:
	bool guarded;
	PickupMethod method;
public:
	Item(char symbol, Position position, PickupMethod method, bool guarded);
	virtual ~Item() = 0;

	Item::PickupMethod GetPickupMethod();
	virtual std::shared_ptr<Event> GetPickedUpBy(std::shared_ptr<Player> player) = 0;

	bool IsGuarded() const;
	void SetGuarded(bool value);
};

