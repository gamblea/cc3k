#include "stdafx.h"
#include "Character.h"
#include "Level.h"
#include "Errors.h"
#include "Event.h"

#include <memory>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>

Character::Character(CharacterStats stats, Position start)
	: Sprite{stats.Symbol, start}, stats { stats }, health{ stats.HpStart }, neutral{stats.Neutral}
{
}

Character::~Character()
{
}


std::shared_ptr<Event> Character::Attack(std::shared_ptr<Character> enemy)
{
	Position enemyPosition = enemy->GetPosition();
	int myDiffX = std::abs(position.x - enemyPosition.x);
	int myDiffY = std::abs(position.y - enemyPosition.y);

	if (myDiffX <= 1 && myDiffY <= 1 && !neutral)
	{
		int r1 = Helpers::getRandom(0, 100);
		int r2 = Helpers::getRandom(0, 100);
		bool success = true;

		//ATTACK
		if (r1 > stats.AtkAccuracy)
			success = false;

		// DODGE
		// halfing have a 50% chance to dodge to attack
		if (r2 < enemy->GetDodgeAccuracy())
			success = false;

		// SUCCESSFUL
		if (success)
		{
			// check if it loses HP because it is allergic to enemy

			if (std::find(stats.AllergicTo.begin(), stats.AllergicTo.end(), enemy->GetRace()) 
				!= stats.AllergicTo.end())  // allergic to enemy
				health -= stats.AtkHpGain;
			else  // else then we want to add gain HP
				health += stats.AtkHpGain;

			if (stats.MaxHp && health > stats.HpStart)
				health = stats.HpStart;

			// DAMAGE ON ENEMY
			int damage = (int) std::ceil((100.0 / (100 + enemy->GetDefense())) * GetAttack());

			// check if we do more damage on a certain type
			auto damageAmount = stats.DamageEffect.find(enemy->stats.Name);
			double effect = 1.0;
			if (damageAmount != stats.DamageEffect.end())
				effect = damageAmount->second / 100;


			enemy->DecrementHealth(damage * effect);

			if (enemy->GetHealth() <= 0)
			{
				AddGold(enemy->GetGoldValue());
				AddGold(stats.GoldForKill);
			}

			std::shared_ptr<Event> battle = std::make_shared<Event>(Event::EventType::Battle, this, enemy.get(), true, damage);
			return battle;
		}
		else
		{
			return std::make_shared<Event>(Event::EventType::Battle, this, enemy.get(), false, 0);
		}

	}
	else 
		return std::make_shared<Event>(Event::EventType::None, "");
	
	// memory error in this passing pointer where reference is wanted
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

int Character::GetDodgeAccuracy() const
{
	return stats.DodgeAccuracy;
}

std::vector<std::string> Character::GetAllergicTo() const
{
	return stats.AllergicTo;
}

int Character::GetGold() const
{
	return gold;
}

void Character::AddGold(int val)
{
	gold += val;
}

std::string Character::GetRace() const
{
	return stats.Name;
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

bool Character::GetNeutral() const
{
	return neutral;
}

void Character::SetNeutral(bool val)
{
	neutral = val;
}

bool Character::GetMoves() const
{
	return stats.Moves;
}

bool Character::Alive()
{
	return health > 0;
}

int Character::GetGoldValue() const
{
	return stats.GoldValue;
}

int Character::GetNumAttack(std::string race)
{
	if (stats.DifferentAtkNumber.find(race) == stats.DifferentAtkNumber.end())
	{
		return stats.NumberOfAtks;
	} 
	else return stats.DifferentAtkNumber.find(race)->second;
}

std::string Character::Character::Die()
{
	return stats.TreasureDrop;
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
