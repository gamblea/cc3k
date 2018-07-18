#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>

#include "Command.h"
#include "Map.h"
#include "CharacterStats.h"

struct CharacterStats;
class Character;
class Sprite;
class Player;

class Event;


typedef std::shared_ptr<const std::map<std::string, CharacterStats>> PointerConstCharactersStatsMap;


/*
	Can be refactored to be the abstract super class if multiple 
	IO options are need. Or if WASD input is to be implemented
*/
 
typedef std::shared_ptr<const Player> PPlayer;
typedef std::vector <std::shared_ptr<const Sprite>> VectorSprite;
typedef std::vector <std::shared_ptr<const Event>> VectorEvent;

typedef std::shared_ptr<std::vector<std::shared_ptr<const Sprite>>> PVectorSprite;
typedef std::shared_ptr<std::vector<std::shared_ptr<const Event>>> PVectorEvent;

typedef std::shared_ptr<const Map> PMap;


class GameIO
{	
	std::istream &in;
	std::ostream &out;
	std::vector<std::vector<char>> board;
	int width = 0;
	int height = 0;

	PPlayer player;
	PVectorSprite sprites;
	PVectorEvent events;
	PMap map;

	char &getBoardAt(Position pos);
	void PrintBothEnds(const std::string &front, const std::string &back) const;
public:
	GameIO(std::istream &in, std::ostream &out);
	virtual ~GameIO();

	CharacterStats GetPlayerRace(const std::map<std::string, CharacterStats> &races);
	Command GetCommand();

	void UpdateBoard();

	void DrawBoard();
	void DrawDetails(std::string levelName);
	void LevelCompleted();
	void InvalidMove(const std::string &msg) const;
	void EndGame();

	void AttachPlayer(PPlayer player);
	void AttachSprites(PVectorSprite sprites);
	void AttachEvents(PVectorEvent events);
	void AttachMap(PMap map);

	bool PlayAgain();


	friend std::ostream &operator<<(std::ostream &out, const std::vector<std::vector<char>> &dVector);

};

std::ostream &operator<<(std::ostream &out, const std::vector<std::vector<char>> &dVector);