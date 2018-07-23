#include "stdafx.h"
#include "Game.h"
#include "CharacterStats.h"
#include <fstream>
#include "Player.h"
#include "Character.h"
#include "Command.h"
#include "Level.h"



Game::Game(std::string charactersDirectory, std::string potionsDirectory, std::string treasuresDirectory)
	:factory{nullptr}
{
	ReadConfigurations<std::string, CharacterStats>(charactersDirectory, config.Characters);
	ReadConfigurations<std::string, PotionEffects>(potionsDirectory, config.Potions);
	ReadConfigurations<std::string, TreasureStats>(treasuresDirectory, config.Treasures);
	this->factory = std::make_shared<SpriteFactory>(config);
	srand((unsigned int) time(nullptr));
}

Game::Game(std::string charactersDirectory, std::string potionsDirectory, std::string treasuresDirectory, int seed)
	:factory{ nullptr }
{
	ReadConfigurations<std::string, CharacterStats>(charactersDirectory, config.Characters);
	ReadConfigurations<std::string, PotionEffects>(potionsDirectory, config.Potions);
	ReadConfigurations<std::string, TreasureStats>(treasuresDirectory, config.Treasures);
	this->factory = std::make_shared<SpriteFactory>(config);
	srand(seed);
}


Game::~Game()
{
}


template<typename ConfigName, typename Config> 
void Game::ReadConfigurations(std::string directory, std::map<ConfigName, Config> configurations)
{
	std::ifstream file{ directory + '/' + directory + "List.txt" };
	std::string configName{};
	while (file >> configName)
	{
		std::ifstream configFile{directory + '/' + configName + ".config" };
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
			std::shared_ptr<Level> level = std::make_shared<Level>(player, "floor.txt", io, factory);
			io.AttachLevel(level);
			passLevel = level->Play();			
		}

		play = io.PlayAgain();
	}

}
