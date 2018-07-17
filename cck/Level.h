#pragma once
#include "Map.h"
#include "Position.h"
#include "GameIO.h"

#include <vector>
#include <memory>


class Item;
class Character;
class Player;

class Level
{
private:
	GameIO &io;

	std::shared_ptr<Player> player;
	std::vector<std::shared_ptr<Character>> enemies;
	std::vector<std::shared_ptr<Item>> items;

	std::vector<std::shared_ptr<Sprite>> sprites;

	Map mapOfLevel;

	bool nonPickUpAt(const Position &pos);

	Position calcPosition(Position current, Direction direction);
	bool accessibleCell(const Position &pos, bool accessToPaths);
	bool cellOccupied(const Position &pos);
	std::shared_ptr<Item> getItemAt(Position position);

	void removeEnemy(std::shared_ptr<Character> enemy);
	void removeItem(std::shared_ptr<Item> item);

	std::shared_ptr<Item> getWalkoverItemAt(Position position);



public:
	Level(std::shared_ptr<Player> player, std::string fileName, GameIO &io);
	bool Play();

	void AddStaircase();
	void AddPotions();
	void AddTreasure();
	void AddEnemies();



	void BuildLevel();
	void ToggleEnemies();
	void MoveEnemies();
	void MovePlayer();
	
	bool CanAttack(const Position &pos);

	std::shared_ptr<Character> getEnemyAt(Position position);
};

