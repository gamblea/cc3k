#include "stdafx.h"
#include "Character.h"
#include "Level.h"
#include "Errors.h"
#include "Event.h"

#include <memory>
#include <algorithm>
#include <cmath>

Character::Character(CharacterStats stats, Position start)
	: Sprite{stats.Symbol, start}, stats { stats }, health{ stats.HpStart }
{
}

Character::~Character()
{
}


std::shared_ptr<Event> Character::Attack(std::shared_ptr<Character> enemy)
{
	// memory error in this passing pointer where reference is wanted
	int r1 = Helpers::getRandom(0, 100);
	int r2 = Helpers::getRandom(0, 100);
	bool success = true;

	//ATTACK
	if (r1 > stats.AtkAccuracy) {
		success = false;	
	} 
	
	// DODGE
	// halfing have a 50% chance to dodge to attack
	if (r2 > enemy->getDodgeAccuary()) {
		success = false;
	}

	// SUCCESSFUL
	if(success) {
		// check if it loses HP because it is allergic to enemy
		auto allergic = td::find(AllergicTo.begin(), AllergicTo.end(), enemy->stats.Name);
		
		if (allergic != AllergicTo.end()) { // allergic to enemy
			health -= stats.AtkHpGain;
		} else { // else then we want to add gain HP
			health += stats.AtkHpGain;
		}
		// add gold for successful attack
			gold += stats.GoldForKill;

		if (stats.MaxHp && health > stats.HpStart) {
			health = stats.HpStart;
		}

		// DAMAGE ON ENEMY
		int damage = std::ceil((100/(100+enemy->getDefense()))*stats.Atk);

		// check if we do more damage on a certain type
		auto damageAmount = DamageEffect.find(enemy->stats.Name);
		if (damageEnemy != DamageEffect.end()) {
			double effect = 1;
			effect = *damageAmount / 100;
		} 

		enemy->DecrementHealth(damage * effect);

		std::shared_ptr<Event> event = std::make_shared<Event>(Event::EventType::Battle, std::make_shared<Character>(*this), enemy, success, damage);
		return event; 
	} else { // NOT SUCCESSFUL
		return std::make_shared<Event>(Event::EventType::None, "");
	}
}

int Character::GetHealth() const
{
	return health;
}

int Character::GetStartingHealth() const
{
	return stats.HpStart; 
}

int Character::GetAttack() const
{
	return stats.Atk; // need to add + potion effects
}

int Character::GetDefense() const
{
	return stats.Def; // neee to add + potion effects
}

std::string Character::GetName() const
{
	return stats.Name;
}

int Character::GetDodgeAccuray() const
{
	return stats.DodgeAccuracy;
}

int Character::GetGold() const
{
	return gold;
}

int Character::PickupGold(int amount)
{
	gold += amount;
	return gold;
}


bool Character::BeenMoved() const
{
	return moved;
}

void Character::SetMoved(bool value)
{
	moved = value;
}

bool Character::AccessToPath()
{
	return stats.AccessToPath;
}


bool Character::isEqual(const Sprite & other) const
{
	try
	{
		const Character &otherCharacter = dynamic_cast<const Character &>(other);
		if (stats == otherCharacter.stats && moved == otherCharacter.moved && health == otherCharacter.health
			&& position == otherCharacter.position && gold == otherCharacter.gold)
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

Position Character::getPosFromDir(Direction dir)
{
	int changeX = 0;
	int changeY = 0;
	switch (dir)
	{
	case Direction::N:
		changeX = 0;
		changeY = -1;
		break;
	case Direction::S:
		changeX = 0;
		changeY = 1;
		break;
	case Direction::E:
		changeX = 1;
		changeY = 0;
		break;
	case Direction::W:
		changeX = -1;
		changeY = 0;
		break;
	case Direction::NW:
		changeX = -1;
		changeY = -1;
		break;
	case Direction::NE:
		changeX = 1;
		changeY = -1;
		break;
	case Direction::SE:
		changeX = 1;
		changeY = 1;
		break;
	case Direction::SW:
		changeX = -1;
		changeY = 1;
		break;
	}

	return { position.x + changeX, position.y + changeY };
}

void Character::DecrementHealth(int amount)
{
	health = std::max(health - amount, 0);	
}
