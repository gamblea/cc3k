#include "stdafx.h"
#include "Level.h"
#include "Character.h"
#include "Sprite.h"
#include "Item.h"
#include "Errors.h"
#include "Player.h"
#include "Map.h"
#include "Event.h"
#include "Treasure.h"
#include "Potion.h"
#include "GameConfig.h"
#include "Stairs.h"

#include <exception>
#include <memory>
#include <algorithm>

Level::Level(std::shared_ptr<Player> player, std::string fileName, GameIO &io, std::shared_ptr<SpriteFactory> factory)
	: player{player}, mapOfLevel{fileName}, io{io}, factory{factory}
{
	// needs to be implemented
	addStaircase();
	addPotions();
	addTreasure();
	addEnemies();
}

Level::~Level()
{
}

bool Level::Play()
{
	io.DrawBoard();
	io.DrawDetails();

	while (!completed)
	{
		Command command = io.GetCommand();
		try
		{
			switch (command.action)
			{
			case Command::Action::Attack :
				try
				{
					Position attackPos = calcPosition(player->GetPosition(), command.direction);
					std::shared_ptr<Character> defender = getEnemyAt(attackPos);
					std::shared_ptr<Event> battle = player->Attack(defender); // Handles the attack

					events.emplace_back(battle);
					if (defender->GetHealth() <= 0)
						removeEnemy(defender); // should be tested
				}
				catch (...)
				{
					throw CannotAttack{command.direction};
				}

				break;

			case Command::Action::Move : 
				try
				{
					MovePlayer(command.direction);
				}
				catch(...)
				{
					throw CannotMove{command.direction};
				}

				break;

			case Command::Action::Use :
				try
				{
					Position itemPos = calcPosition(player->GetPosition(), command.direction);
					std::shared_ptr<Item> item = getItemAt(itemPos);

					std::shared_ptr<Event> event = item->GetPickedUpBy(player);
					
					removeItem(item); // needs to be tested
				}
				catch (...)
				{
					throw CannotUse{command.direction};
				}
				break;

			case Command::Action::Quit :
				io.EndGame();
				exit(0);
				break;
			default:
				break;
			}
		}
		// can make all these to one with supercalss of exception and overload what ()
		catch (const DirectionExeption& attempt)
		{
			io.InvalidCommand(attempt.what()); // add exception .what()
			continue;
		}

		MoveEnemies();
		// STILL HAVE TO DO ENEMIES MOVES

		io.DrawBoard();
		io.DrawDetails();
		if (completed) io.LevelCompleted();
	}

	return completed;
}




void Level::ToggleEnemies()
{
	if (enemiesMoveable) enemiesMoveable = false;
	else enemiesMoveable = true;
}

void Level::MoveEnemies()
{
	if (enemiesMoveable)
	{
		for (int x = 0; x < mapOfLevel.GetWidth(); x++)
		{
			for (PCharacter enemy : enemies)
			{
				if (enemy->GetPosition().x == x && !enemy->BeenMoved())
				{
					std::shared_ptr<Event> enemyEvent = enemy->Attack(player);
					if (enemyEvent->GetType() == Event::EventType::Battle)
					{
						events.emplace_back(enemyEvent);
						enemy->SetMoved(true);
					}
					else
					{
						while (!enemy->BeenMoved())
						{
							Direction direction = static_cast<Direction>(Helpers::getRandom(0, 7));
							Position newPos = calcPosition(player->GetPosition(), direction);
							if (cellOccupied(newPos) && accessibleCell(newPos, enemy->AccessToPath()))
							{
								enemy->Move(newPos);
								enemy->SetMoved(true);
							}
						}
					}
				}
			}
		}
		for (PCharacter enemy : enemies)
		{
			enemy->SetMoved(false);
		}
	}
	
}

void Level::MovePlayer(Direction direction)
{
	Position newPos = calcPosition(player->GetPosition(), direction);

	bool accessible = accessibleCell(newPos, true);
	if (accessible && !cellOccupied(newPos))
	{
		player->Move(newPos);
		events.emplace_back(std::make_shared<Event>(Event::EventType::Move, player,direction));
	}
	else if (accessible)
	{
		std::shared_ptr<Item> item = getWalkoverItemAt(newPos); // throws exception if it can be picked up
		std::shared_ptr<Event> event = item->GetPickedUpBy(player);
		if (event->GetType() == Event::EventType::EndLevel)
		{
			completed = true;
		}
		events.emplace_back(event);
		removeItem(item);
	}
	else throw CannotMove{direction};
}

std::shared_ptr<Character> Level::getEnemyAt(Position position)
{
	for (const std::shared_ptr<Character> &enemy : enemies)
	{
		if (enemy->GetPosition() == position)
		{
			return enemy;
		}
	}
	throw std::exception();
}


bool Level::nonPickUpAt(const Position &pos)
{
	if (player->GetPosition() == pos) return true;
	for (auto &character : enemies)
	{
		if (character->GetPosition() == pos)
			return true;
	}
	for (auto &item : items)
	{
		if (item->GetPickupMethod() == Item::PickupMethod::Use && item->GetPosition() == pos)
			return true;
	}
	return false;
}

Position Level::calcPosition(Position current, Direction direction)
{
	int changeX = 0;
	int changeY = 0;
	switch (direction)
	{
	case Direction::N :
		changeX = 0;
		changeY = -1;
		break;
	case Direction::S:
		changeX = 0;
		changeY = 1;
		break;
	case Direction::E:
		changeX = 1;
		changeY = 0;
		break;
	case Direction::W:
		changeX = -1;
		changeY = 0;
		break;
	case Direction::NW:
		changeX = -1;
		changeY = -1;
		break;
	case Direction::NE:
		changeX = 1;
		changeY = -1;
		break;
	case Direction::SE:
		changeX = 1;
		changeY = 1;
		break;
	case Direction::SW:
		changeX = -1;
		changeY = 1;
		break;
	default :
		throw std::runtime_error("");
	}

	Position newPos{ current.x + changeX, current.y + changeY };
	if (newPos.x >= 0 && newPos.x < mapOfLevel.GetWidth() && newPos.y >= 0 || newPos.y < mapOfLevel.GetHeight())
		return newPos;
	else throw std::out_of_range("New Position is outside grid.");
}



bool Level::accessibleCell(const Position &pos, bool accessToPaths)
{
	Map::Cell cell = mapOfLevel.GetCell(pos);
	if (accessToPaths)
	{
		return cell == Map::Cell::Floor || cell == Map::Cell::Doorway ||  cell == Map::Cell::Passage;
	}
	else return cell == Map::Cell::Floor;

}

bool Level::cellOccupied(const Position &pos)
{
	for (const std::shared_ptr<Sprite> &sprite : sprites)
	{
		if (sprite->GetPosition() == pos)
			return true;
	}
	return false;
}

std::shared_ptr<Item> Level::getItemAt(Position position)
{
	for (const std::shared_ptr<Item> &item : items)
	{
		if (item->GetPosition() == position)
		{
			return item;
		}
	}
	throw std::exception();
}

void Level::addEnemy(std::shared_ptr<Character> enemy)
{
	enemies.emplace_back(enemy);
	addSprite(enemy);
}

void Level::addItem(std::shared_ptr<Item> item)
{
	items.emplace_back(item);
	addSprite(item);
}

void Level::addSprite(std::shared_ptr<Sprite> sprite)
{
	sprites.emplace_back(sprite);
}

void Level::removeSprite(std::shared_ptr<Sprite> sprite)
{
	sprites.erase(std::find_if(sprites.begin(), sprites.end(),
		[&sprite](const std::shared_ptr<Sprite> other) { *sprite == *other; }));
}

void Level::removeEnemy(std::shared_ptr<Character> enemy)
{
	enemies.erase(std::find_if(enemies.begin(), enemies.end(), 
		[&enemy](const std::shared_ptr<Character> other) {*enemy == *other; }));
	removeSprite(enemy);
}

void Level::removeItem(std::shared_ptr<Item> item)
{
	items.erase(std::find_if(items.begin(), items.end(), 
		[&item](const std::shared_ptr<Item> other) {*other == *item; }));
	removeSprite(item);
}

std::shared_ptr<Item> Level::getWalkoverItemAt(Position position)
{
	for (const std::shared_ptr<Item> &item : items)
	{
		if (item->GetPosition() == position && 
			item->GetPickupMethod() == Item::PickupMethod::Walkover)
		{
			return item;
		}
	}
	throw std::exception();
}

void Level::addStaircase()
{
	int room = Helpers::getRandom(0, mapOfLevel.GetNumRooms() - 1);
	Position newPos = GetAvalibleRandomPosRoom(room);
	addItem(std::make_shared<Stairs>(newPos));
	roomOfStairs = room;
}

void Level::addPotions()
{
	for (int i = 0; i < 10; i++)
	{
		Potion potion = factory->CreatePotion(GetAvalibleRandomPos());
		addItem(std::make_shared<Potion>(potion));
	}
	
}

void Level::addTreasure()
{
	for (int i = 0; i < 10; i++)
	{
		Treasure treasure = factory->CreateTreasure(GetAvalibleRandomPos());
		// if protected add dragon need to add!
		addItem(std::make_shared<Treasure>(treasure));
	}
	
}

void Level::addEnemies()
{
	for (auto &item : items)
	{
		if (item->ToBeGuarded())
		{
			bool posFound = false;
			while (!posFound)
			{
				try
				{
					Position guardPos = GetAvalibleAdjacent(item->GetPosition());
					posFound = true;
				}
				catch (...) // All Spots around Dragon Board full
				{
					item->Move(GetAvalibleRandomPos());
				}
			}

			Character enemy = 
		}
	}

	for (int i = 0; i < 20; i++)
	{
		Character enemy = factory->CreateEnemy(GetAvalibleRandomPos());
		addEnemy(std::make_shared<Character>(enemy));
	}
}

Position Level::GetAvalibleRandomPos()
{
	int numRooms = mapOfLevel.GetNumRooms();
	int room = Helpers::getRandom(0, numRooms - 1);
	return GetAvalibleRandomPosRoom(room);
}

Position Level::GetAvalibleRandomPosRoom(int room)
{
	Position newPos;
	bool found = false;
	while (!found)
	{
		newPos = mapOfLevel.GetPositionFromRoom(room);
		if (!cellOccupied(newPos) && accessibleCell(newPos, false))
			found = true;
	}
	return newPos;
}

Position Level::GetAvalibleAdjacent(Position pos)
{
	std::vector<Direction> tried;
	bool posFound = false;
	Position newPos;

	while (!posFound)
	{
		Direction direction = static_cast<Direction>(Helpers::getRandom(0, 7));
		if (std::find(tried.begin(), tried.end(), direction) != tried.end())
		{
			tried.emplace_back(direction);
			newPos = calcPosition(pos, direction);
			if (accessibleCell(newPos, false) && !cellOccupied(newPos)) posFound = true;
		}
		if (tried.size() == 8) throw std::runtime_error("No avalible adjacent positions");
	}
	
}

const Map & Level::GetMap()
{
	return mapOfLevel;
}

PPlayer Level::GetPlayer()
{
	return player;
}

const VectorPCharacter & Level::GetEnemies()
{
	return enemies;
}

const VectorPSprite & Level::GetSprites()
{
	return sprites;
}

const VectorPItem& Level::GetItems()
{
	return items;
}

const VectorPEvent & Level::GetEvents()
{
	return events;
}
