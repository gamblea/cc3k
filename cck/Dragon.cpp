#include "stdafx.h"
#include "Dragon.h"
#include "Item.h"
#include "Character.h"
#include "Position.h"
#include "Helpers.h"
#include "Event.h"

Dragon::Dragon(CharacterStats stats, Position start, std::shared_ptr<Item> itemToProtect):
	Character{stats, start}, itemToProtect{itemToProtect}
	{}

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
		|| (protectedDiffX <= 1 && protectedDiffY <= 1)) {

		int dodgeChance = Helpers::getRandom(0, 100);
		int attackChance = Helpers::getRandom(0, 100);
		bool success = true;
		
		if (dodgeChance > stats.AtkAccuray) {
			success = false;
		} else if (attackChance > enemy->stats.dodgeAccuracy) {
			success = false;
		}
		
		if (success) {
			health += stats.AtkHpGain;
		}
		
		if(stats.MaxHp && health > stats.HpStart) {
			health = stats.HpStart;
		}

		int damage = std::ceil((100/(100+enemy->stats.Def))*stats.Atk);
		enemy->DecrementHealth(damage);
		std::shared_ptr<Event> event = std::make_shared<Event>(Event::EventType::Battle, std::make_shared<Character>(this), enemy, success, damage);
		
		return event; 
	} else {
		return std::make_shared<Event>(Event::EventType::None, "");
	}
}

Dragon::~Dragon() {
	itemToProtect->guarded = false;
}