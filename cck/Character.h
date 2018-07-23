#pragma once
#include "Sprite.h"
#include "Direction.h"
#include "CharacterStats.h"
#include "PotionEffects.h"

class Event;
class Character;

class Character : public Sprite
{
private:
	virtual bool isEqual(const Sprite& other) const;
protected:
	CharacterStats stats;
	bool moved = false;
	int health;
	int gold;


	Position getPosFromDir(Direction dir);
public:
	Character(CharacterStats stats, Position start);
	virtual ~Character();
	virtual std::shared_ptr<Event> Attack(std::shared_ptr<Character> enemy);

	int GetHealth() const;
	int GetStartingHealth() const;
	virtual int GetAttack() const; // need to add potion benefits
	virtual int GetDefense() const; // need to add potion benefits

	void DecrementHealth(int amount);

	std::string GetName() const;
	int GetGold() const;
	int PickupGold(int amount);

	bool BeenMoved() const;
	void SetMoved(bool value);
	bool AccessToPath();
};

