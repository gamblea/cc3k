#pragma once
#include "Character.h"
#include "TreasureStats.h"
#include "PotionEffects.h"
#include "Direction.h"
#include <memory>

class Stairs;
class Event;

class Player :
	public Character
{
private:
	int AtkChange = 0;
	int DefChange = 0;
public:
	Player(CharacterStats stats, Position start);
	Player(CharacterStats stats);
	virtual ~Player();

	int GetAttack() const override ;
	int GetDefense() const override ;

	std::shared_ptr<Event> Use(PotionEffects effect);
	std::shared_ptr<Event> Use(TreasureStats treasureStats);
	std::shared_ptr<Event> Use(const Stairs &stairs);

	void ResetForLevel();
};

