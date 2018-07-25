#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "TreasureStats.h"
#include "PotionEffects.h"
#include "Direction.h"
#include <memory>
#include <vector>
#include <string>

class Stairs;
class Event;

class Player :
	public Character
{
private:
	int AtkChange = 0;
	int DefChange = 0;
	virtual bool isEqual(const Sprite& other) const; // not all fields but a good amount
	std::vector<std::string> SeenPotions;

public:
	Player(CharacterStats stats, Position start);
	Player(CharacterStats stats);
	virtual ~Player();

	int GetAttack() const override ;
	int GetDefense() const override ;
	std::string GetName() const override;
	bool SeenPotion(std::string newPotion);

	std::shared_ptr<Event> Use(PotionEffects effect);
	std::shared_ptr<Event> Use(TreasureStats treasureStats);
	std::shared_ptr<Event> Use(const Stairs &stairs);

	void ResetForLevel();

	int GetScore();
};
#endif
