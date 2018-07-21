#pragma once
#include "Map.h"
#include "Position.h"
#include "GameIO.h"
#include "GameConfig.h"

#include <vector>
#include <memory>



class Item;
class Character;
class Player;

typedef std::shared_ptr<Player> PPlayer;
typedef std::vector<std::shared_ptr<Character>> VectorPCharacter;
typedef std::vector<std::shared_ptr<Sprite>> VectorPSprite;
typedef std::vector<std::shared_ptr<Item>> VectorPItem;
typedef std::vector<std::shared_ptr<Event>> VectorPEvent;

typedef std::shared_ptr<Character> PCharacter;

class Level
{
private:
	GameIO &io;
	const GameConfig &gameConfig;

	PPlayer player;
	VectorPCharacter enemies;
	VectorPItem items;
	VectorPSprite sprites;
	VectorPEvent events;


	Map mapOfLevel;

	

	bool enemiesMoveable = true;

	bool nonPickUpAt(const Position &pos);

	Position calcPosition(Position current, Direction direction);
	bool accessibleCell(const Position &pos, bool accessToPaths);
	bool cellOccupied(const Position &pos);
	std::shared_ptr<Item> getItemAt(Position position);

	void removeEnemy(std::shared_ptr<Character> enemy);
	void removeItem(std::shared_ptr<Item> item);

	std::shared_ptr<Item> getWalkoverItemAt(Position position);
	bool completed = false;

	Position getRandomPosition();

public:
	Level(std::shared_ptr<Player> player, std::string fileName, GameIO &io, const GameConfig &gameConfig);
	~Level();
	bool Play();

	void AddStaircase();
	void AddPotions();
	void AddTreasure();
	void AddEnemies();

	const Map &GetMap();
	PPlayer GetPlayer();
	const VectorPCharacter& GetEnemies();
	const VectorPSprite& GetSprites();
	const VectorPItem& GetItems();
	const VectorPEvent& GetEvents();

	void ToggleEnemies();
	void MoveEnemies();
	void MovePlayer(Direction direction);
	
	bool CanAttack(const Position &pos);

	std::shared_ptr<Character> getEnemyAt(Position position);
};

