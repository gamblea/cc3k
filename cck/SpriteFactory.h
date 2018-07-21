#pragma once

#include "GameConfig.h"
#include <memory>
#include <vector>
#include <string>
#include "CharacterStats.h"
#include "Position.h"

class Treasure;
class Potion;
class Character;

class SpriteFactory
{
private:
	GameConfig gameConfig;
	std::vector<std::string> enemyNamesChoose;
	std::vector<std::string> treasureNamesChoose;
public:
	SpriteFactory(GameConfig gameConfig);
	~SpriteFactory();

	Character CreateEnemy(Position start);
	Character CreateEnemy(Position start, std::string name);
	Treasure CreateTreasure(Position start);
	Potion CreatePotion(Position start);
};

