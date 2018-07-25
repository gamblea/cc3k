#include "stdafx.h"
#include "Dragon.h"
#include "Item.h"
#include "Character.h"
#include "Position.h"
#include "Helpers.h"
#include "Event.h"
#include <cmath>

bool Dragon::isEqual(const Sprite & other) const
{
	try
	{
		const Dragon &otherDragon = dynamic_cast<const Dragon &>(other);
		if (stats == otherDragon.stats && moved == otherDragon.moved && health == otherDragon.health
			&& position == otherDragon.position && gold == otherDragon.gold)
		{
			if (itemToProtect && otherDragon.itemToProtect)
			{
				return *itemToProtect == *(otherDragon.itemToProtect);
			}
			else return true;
		}
		else return false;
	}
	catch (const std::bad_cast&)
	{
		return false;
	}
}

Dragon::Dragon(CharacterStats stats, Position start, std::shared_ptr<Item> itemToProtect)
	: Character{stats, start}, itemToProtect{itemToProtect}
{
	itemToProtect->SetGuarded(true);
}

std::shared_ptr<Item> Dragon::getItem() {
	return itemToProtect;
}


std::shared_ptr<Event> Dragon::Attack(std::shared_ptr<Character> enemy) {

	Position protectedPosition = itemToProtect->GetPosition();
	Position enemyPosition = enemy->GetPosition();
	
	bool success = true;
	int myDiffX = std::abs(position.x - enemyPosition.x);
	int myDiffY = std::abs(position.y - enemyPosition.y);

	int protectedDiffX = std::abs(enemyPosition.x - protectedPosition.x);
	int protectedDiffY = std::abs(enemyPosition.y - protectedPosition.y);

	if ((myDiffX <= 1 && myDiffY <= 1)
		|| (protectedDiffX <= 1 && protectedDiffY <= 1))
	{
		//ATTACK
		int r1 = Helpers::getRandom(0, 100);

		if (r1 > stats.AtkAccuracy) {
			success = false;
		}

		// SUCCESSFUL
		if (success) {

			// DAMAGE ON ENEMY
			int damage = (int) std::ceil((100.0 / (100.0 + enemy->GetDefense()))* GetAttack());
			enemy->DecrementHealth(damage);

			std::shared_ptr<Event> event = std::make_shared<Event>(Event::EventType::Battle, this, enemy.get(), success, damage);
			return event;

		}
		else {
			return std::make_shared<Event>(Event::EventType::Battle, this, enemy.get(), false, 0);
		}
	} else return std::make_shared<Event>(Event::EventType::None, "");
}

Dragon::~Dragon() 
{
	itemToProtect->SetGuarded(false);
}

std::string Dragon::Die()
{
	itemToProtect->SetGuarded(false);
	return stats.TreasureDrop;
}

