#include "stdafx.h"
#include "SpriteFactory.h"
#include "Helpers.h"
#include "TreasureStats.h"
#include "Position.h"
#include "Character.h"
#include "Treasure.h"
#include "Potion.h"

#include <vector>
#include <map>


SpriteFactory::SpriteFactory(GameConfig gameConfig) : gameConfig{gameConfig}
{
	for (const auto &config : gameConfig.Characters)
	{
		for (int i = 0; i < config.second.Probability; i++)
		{
			enemyNamesChoose.emplace_back(config.first);
		}
	}

	for (const auto &config : gameConfig.Treasures)
	{
		for (int i = 0; i < config.second.Probability; i++)
		{
			treasureNamesChoose.emplace_back(config.first);
		}
	}
}


SpriteFactory::~SpriteFactory()
{
}

Character SpriteFactory::CreateEnemy(Position start)
{
	int size = enemyNamesChoose.size();
	int index = Helpers::getRandom(0, size - 1);
	CharacterStats stats = gameConfig.Characters.find(enemyNamesChoose.at(index))->second;

	return Character{ stats, start };
}

Character SpriteFactory::CreateEnemy(Position start, std::string name)
{
	CharacterStats stats = gameConfig.Characters.find(name)->second;

	return Character{ stats, start };
}

Treasure SpriteFactory::CreateTreasure(Position start)
{
	int size = (int) gameConfig.Treasures.size();
	int index = Helpers::getRandom(0, size - 1);
	TreasureStats stats = gameConfig.Treasures.find(treasureNamesChoose.at(index))->second;

	return Treasure{start, stats };
}

Potion SpriteFactory::CreatePotion(Position start)
{
	int size = gameConfig.Potions.size();
	int index = Helpers::getRandom(0, size - 1);
	auto elem = gameConfig.Potions.begin();
	std::advance(elem, index);
	PotionEffects stats = elem->second;

	return Potion{start , stats};
}
