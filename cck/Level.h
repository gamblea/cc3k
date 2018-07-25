#ifndef LEVEL_H
#define LEVEL_H
#include "Map.h"
#include "Position.h"
#include "GameIO.h"
#include "GameConfig.h"
#include "SpriteFactory.h"

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

	PPlayer player;
	VectorPCharacter enemies;
	VectorPItem items;
	VectorPSprite sprites;
	VectorPEvent events;


	Map mapOfLevel;

	std::shared_ptr<SpriteFactory> factory;
	
	bool enemiesMoveable = true;
	int roomOfStairs;

	bool nonPickUpAt(const Position &pos);

	Position calcPosition(Position current, Direction direction);
	bool accessibleCell(const Position &pos, bool accessToPaths);
	bool cellOccupied(const Position &pos);
	std::shared_ptr<Item> getItemAt(Position position);

	const int levelNum;

	void addPlayer();

	void addEnemy(std::shared_ptr<Character> enemy);
	void addItem(std::shared_ptr<Item> item);
	void addSprite(std::shared_ptr<Sprite> sprite);
	void removeEnemy(std::shared_ptr<Character> enemy);
	void removeItem(std::shared_ptr<Item> item);
	void removeSprite(std::shared_ptr<Sprite> sprite);


	std::shared_ptr<Item> getWalkoverItemAt(Position position);
	bool completed = false;

	void addStaircase();
	void addPotions();
	void addTreasure();
	void addEnemies();

	Position GetAvalibleRandomPos();
	Position GetAvalibleRandomPosRoom(int room);

	Position GetAvalibleAdjacent(Position pos);

	void SetRaceNeutralality(std::string name, bool val);

	void AddSeeEvents();

public:
	Level(std::shared_ptr<Player> player, std::string fileName, GameIO &io, std::shared_ptr<SpriteFactory> factory, int levelNum);
	~Level();
	bool Play();

	const Map &GetMap();
	PPlayer GetPlayer();
	const VectorPCharacter& GetEnemies();
	const VectorPSprite& GetSprites();
	const VectorPItem& GetItems();
	const VectorPEvent& GetEvents();

	void ToggleEnemies();
	void MoveEnemies();
	void MovePlayer(Direction direction);

	int GetLevelNum() const;

	std::shared_ptr<Character> getEnemyAt(Position position);
};
#endif
