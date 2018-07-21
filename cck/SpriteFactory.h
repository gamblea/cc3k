#pragma once

#include "GameConfig.h"
#include <memory>
#include <vector>
#include <string>
#include "CharacterStats.h"

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

	std::shared_ptr<Character> CreateEnemy();
	std::shared_ptr<Treasure> CreateTreasure();
	std::shared_ptr<Potion> CreatePotion();
};

