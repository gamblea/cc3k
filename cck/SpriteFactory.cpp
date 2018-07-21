#include "stdafx.h"
#include "SpriteFactory.h"
#include "Helpers.h"
#include "TreasureStats.h"


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

std::shared_ptr<Character> SpriteFactory::CreateEnemy()
{
	int size = enemyNamesChoose.size();
	int index = Helpers::getRandom(0, size - 1);
	auto elem = gameConfig.Characters.find(enemyNamesChoose.at(index));

	return std::make_shared<Character>(elem->second);
}

std::shared_ptr<Treasure> SpriteFactory::CreateTreasure()
{
	int size = gameConfig.Treasures.size();
	int index = Helpers::getRandom(0, size - 1);
	auto elem = gameConfig.Treasures.find(treasureNamesChoose.at(index));

	return std::make_shared<Treasure>(elem->second);
}

std::shared_ptr<Potion> SpriteFactory::CreatePotion()
{
	int size = gameConfig.Potions.size();
	int index = Helpers::getRandom(0, size - 1);
	auto elem = gameConfig.Characters.begin();
	std::advance(elem, index);

	return std::make_shared<Potion>(elem->second);
}
