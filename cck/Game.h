#pragma once
#include <map>
#include <string>
#include <memory>
#include "PotionEffects.h"
#include "TreasureStats.h"
#include "GameIO.h"
#include "GameConfig.h"
#include <time.h>


class Player;
class Level;
class TextDisplay;
class GameIO;
class SpriteFactory;

struct CharacterStats;

class Game
{
private:
	const std::string charactersFile;

	GameConfig config;

	std::shared_ptr<Player> player;
	GameIO io{std::cin,std::cout};
	std::shared_ptr<SpriteFactory> factory;

	template<typename ConfigName, typename Config>
	void ReadConfigurations(std::string directory, std::map<ConfigName, Config> &configurations);

public:
	Game(std::string charactersDirectory, std::string potionsDirectory, std::string treasuresDirectory);
	Game(std::string charactersDirectory, std::string potionsDirectory, std::string treasuresDirectory, int seed);
	Game(std::string charactersDirectory, std::string potionsDirectory, std::string treasuresDirectory, std::string floor);
	Game(std::string charactersDirectory, std::string potionsDirectory, std::string treasuresDirectory, std::string floor, int seed);
	
	void Start();
	~Game();

};

