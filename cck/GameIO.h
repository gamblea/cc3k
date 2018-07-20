#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>

#include "Command.h"
#include "Map.h"

struct CharacterStats;
class Character;
class Sprite;
class Player;

class Event;
class Level;


typedef std::shared_ptr<const std::map<std::string, CharacterStats>> PointerConstCharactersStatsMap;


/*
	Can be refactored to be the abstract super class if multiple 
	IO options are need. Or if WASD input is to be implemented
*/
 
typedef std::shared_ptr<const Player> PPlayer;
typedef std::vector <const std::shared_ptr<const Sprite>> VectorSprite;
typedef std::vector <const std::shared_ptr<const Event>> VectorEvent;

typedef std::shared_ptr<std::vector<const std::shared_ptr<const Sprite>>> PVectorSprite;
typedef std::shared_ptr<std::vector<const std::shared_ptr<const Event>>> PVectorEvent;

typedef std::shared_ptr<const Map> PMap;


class GameIO
{	
	std::istream &in;
	std::ostream &out;
	std::vector<std::vector<char>> board;
	int width = 0;
	int height = 0;

	std::shared_ptr<Level> level;

	char &getBoardAt(Position pos);
	void PrintBothEnds(const std::string &front, const std::string &back) const;
public:
	GameIO(std::istream &in, std::ostream &out);
	virtual ~GameIO();

	CharacterStats GetPlayerRace(const std::map<std::string, CharacterStats> &races);
	Command GetCommand();

	void UpdateBoard();

	void DrawBoard();
	void DrawDetails();
	void LevelCompleted();
	void InvalidCommand(const std::string &msg) const;
	void EndGame();

	void AttachLevel(std::shared_ptr<Level> level);

	bool PlayAgain();

	friend std::ostream &operator<<(std::ostream &out, const std::vector<std::vector<char>> &dVector);
};

std::ostream &operator<<(std::ostream &out, const std::vector<std::vector<char>> &dVector);