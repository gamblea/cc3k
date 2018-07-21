#include "stdafx.h"
#include "Game.h"
#include "CharacterStats.h"
#include <fstream>
#include "Player.h"
#include "Level.h"



Game::Game(std::string charactersFile, std::string potionsFile, std::string treasureFile)
{
	ReadConfigurations<std::string, CharacterStats>(charactersFile, config.Characters);
	ReadConfigurations<std::string, PotionEffects>(charactersFile, config.Potions);
	ReadConfigurations<std::string, TreasureStats>(charactersFile, config.Treasures);
	factory = std::make_shared<SpriteFactory>(config);
	srand(time(nullptr));
}

Game::Game(std::string charactersFile, std::string potionFile, std::string treasureFile, int seed)
{
	ReadConfigurations<std::string, CharacterStats>(charactersFile, config.Characters);
	ReadConfigurations<std::string, PotionEffects>(charactersFile, config.Potions);
	ReadConfigurations<std::string, TreasureStats>(charactersFile, config.Treasures);
	factory = std::make_shared<SpriteFactory>(config);
	srand(seed);
}


Game::~Game()
{
}


template<typename ConfigName, typename Config> 
void Game::ReadConfigurations(std::string fileName, std::map<ConfigName, Config> configurations)
{
	std::ifstream file{ fileName };
	std::string configName{};
	while (file >> configName)
	{
		std::ifstream configFile{ configName + ".config" };
		Config config{};
		configFile >> config;
		configurations.emplace(config.Name, config);
	}
}


void Game::Start()
{
	bool play = true;
	while (play)
	{
		bool passLevel = true;
		player = std::make_shared<Player>(io.GetPlayerRace(config.Characters));

		for (int i = 0; i < 5 && passLevel; i++ ) // Play the levels
		{
			std::shared_ptr<Level> level = std::make_shared<Level>(player, "level.map", io);
			io.AttachLevel(level);
			passLevel = level->Play();			
		}

		play = io.PlayAgain();
	}

}
