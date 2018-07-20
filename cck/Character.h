#pragma once
#include "Sprite.h"
#include "Direction.h"
#include "CharacterStats.h"
#include "PotionEffects.h"

class Event;
class Character;

class Character : public Sprite
{
protected:
	CharacterStats stats;
	int health;
	int gold;

	Position getPosFromDir(Direction dir);
public:
	Character(CharacterStats stats, Position start);
	virtual ~Character();
	void Move(Position pos);
	std::shared_ptr<Event> Attack(std::shared_ptr<Character> enemy);

	int GetHealth() const;
	int GetStartingHealth() const;
	int GetAttack() const; // need to add potion benefits
	int GetDefense() const; // need to add potion benefits

	void DecrementHealth(int amount);

	std::string GetName() const;
	int GetGold() const;
	int PickupGold(int amount);
};

