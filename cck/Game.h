#pragma once
#include <map>
#include <string>
#include <memory>
#include "PotionEffects.h"
#include "TreasureStats.h"
#include "GameIO.h"
#include "GameConfig.h"


class Player;
class Level;
class TextDisplay;
class GameIO;

struct CharacterStats;

class Game
{
private:
	const std::string charactersFile;

	GameConfig gameConfig;

	std::shared_ptr<Level> level;
	std::shared_ptr<Player> player;
	std::shared_ptr<TextDisplay> display;
	GameIO io{std::cin,std::cout};


	template<typename ConfigName, typename Config>
	void ReadConfigurations(std::string fileName, std::map<ConfigName, Config> configurations);

public:
	Game() = default; // should delete 
	Game(std::string charactersFile, std::string potionsFile, std::string treasureFile);
	void Start();
	~Game();

};

