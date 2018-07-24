#include "stdafx.h"
#include "Dragon.h"
#include "Item.h"
#include "Character.h"
#include "Position.h"
#include "Helpers.h"
#include "Event.h"

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
	
	int myDiffX = position.x - enemyPosition.x;
	int myDiffY = position.y - enemyPosition.y;

	int protectedDiffX = position.x - protectedPosition.x;
	int protectedDiffY = position.y - protectedPosition.y;

	if ((myDiffX <= 1 && myDiffY <= 1)
		|| (protectedDiffX <= 1 && protectedDiffY <= 1)) 
	{

	//ATTACK
	int r1 = Helpers::getRandom(0, 100);

	if (r1 > stats.AtkAccuracy) {
		success = false;	
	} 

	// SUCCESSFUL
	if(success) {

		// DAMAGE ON ENEMY
		int damage = std::ceil((100/(100+enemy->getDefense()))*stats.Atk);
		enemy->DecrementHealth(damage * effect);
		
		std::shared_ptr<Event> event = std::make_shared<Event>(Event::EventType::Battle, std::make_shared<Character>(*this), enemy, success, damage);
		return event; 
		
	} else {
		return std::make_shared<Event>(Event::EventType::None, "");
	}
}

Dragon::~Dragon() {
	itemToProtect->SetGuarded(false);
}

