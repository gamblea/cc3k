#ifndef ITEM_H
#define ITEM_H
#include "Sprite.h"
#include "CharacterStats.h"
#include "Character.h"
#include "Dragon.h"
#include <string>
#include <memory>

class Event;
class Player;

class Item : public Sprite
{
public:
	enum class PickupMethod { Walkover, Use };
private:
	const bool toBeGuarded = false;
	const std::string guardName = "";
	bool guarded = false;
	PickupMethod method;

public:
	Item(char symbol, Position position, PickupMethod method, bool toBeGuarded, std::string guardName);
	Item(char symbol, Position position, PickupMethod method);
	virtual ~Item() = 0;

	virtual std::string GetName() const = 0;

	Item::PickupMethod GetPickupMethod();
	virtual std::shared_ptr<Event> GetPickedUpBy(std::shared_ptr<Player> player) = 0;

	std::string GetGuardName() const;
	bool ToBeGuarded() const;
	void SetGuarded(bool value);
	bool GetGuarded() const;
};

#endif
