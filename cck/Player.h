#pragma once
#include "Character.h"
#include "TreasureStats.h"
#include "PotionEffects.h"
#include "Direction.h"

class Stairs;
class Event;

class Player :
	public Character
{
private:

public:
	Player(CharacterStats stats, Position start);
	Player(CharacterStats stats);
	virtual ~Player();

	std::shared_ptr<Event> Use(PotionEffects effect);
	std::shared_ptr<Event> Use(TreasureStats treasureStats);
	std::shared_ptr<Event> Use(const Stairs &stairs);

	void ResetForLevel();
};

