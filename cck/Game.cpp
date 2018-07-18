#include "stdafx.h"
#include "Game.h"
#include "CharacterStats.h"
#include <fstream>
#include "Player.h"
#include "Level.h"



Game::Game(std::string charactersFile, std::string potionsFile, std::string treasureFile)
{
	ReadConfigurations<std::string, CharacterStats>(charactersFile, gameConfig.Characters);
	ReadConfigurations<std::string, PotionEffects>(charactersFile, gameConfig.Potions);
	ReadConfigurations<std::string, TreasureStats>(charactersFile, gameConfig.Treasures);
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
		Config configuration{};
		configFile >> configuration;
		configurations.emplace(configName, configuration);
	}
}


void Game::Start()
{
	bool play = true;
	while (play)
	{
		bool passLevel = true;
		player = std::make_shared<Player>(io.GetPlayerRace(gameConfig.Characters));
		io.AttachPlayer(player);

		for (int i = 0; i < 5 && passLevel; i++ ) // Play the levels
		{
			level = std::make_shared<Level>(player, "level.map", io);
			passLevel = level->Play();			
		}

		play = io.PlayAgain();
	}

}
