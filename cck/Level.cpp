#include "stdafx.h"
#include "Level.h"
#include "Character.h"
#include "Sprite.h"
#include "Item.h"
#include "Errors.h"
#include "Player.h"
#include "Map.h"
#include "Event.h"

#include <exception>
#include <memory>

Level::Level(std::shared_ptr<Player> player, std::string fileName, GameIO &io)
	: player{player}, mapOfLevel{fileName}, io{io}
{
	// needs to be implemented
	AddStaircase();
	AddPotions();
	AddTreasure();
	AddEnemies();
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

					if (defender->GetHealth() <= 0)
						removeEnemy(defender); // should be tested
				}
				catch (...)
				{
					throw CannotAttack{ command.direction };
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

void Level::BuildLevel()
{

}

void Level::MovePlayer(Direction direction)
{
	Position newPos = calcPosition(player->GetPosition(), direction);

	bool accessible = accessibleCell(newPos, true);
	if (accessible && !cellOccupied(newPos))
	{
		player->Move(newPos);
		std::string msg = player->GetName() + " moved " + Helpers::directionToStr(direction) + ".";
		events.emplace_back(std::make_shared<Event>(Event::EventType::Move, msg));

	}
	else if (accessible)
	{
		std::shared_ptr<Item> item = getWalkoverItemAt(newPos); // throws exception if it can be picked up
		std::shared_ptr<Event> event = item->GetPickedUpBy(player);
		if (event->GetType() == Event::EventType::EndLevel)
		{
			completed = true;
		}
		events.emplace_back(std::a);
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

void Level::removeEnemy(std::shared_ptr<Character> enemy)
{
	enemies.erase(std::find(enemies.begin(), enemies.end(), enemy));
	sprites.erase(std::find(sprites.begin(), sprites.end(), std::static_pointer_cast<Sprite>(enemy)));
}

void Level::removeItem(std::shared_ptr<Item> item)
{
	items.erase(std::find(items.begin(), items.end(), item));
	sprites.erase(std::find(sprites.begin(), sprites.end(), std::static_pointer_cast<Sprite>(item)));
}

std::shared_ptr<Item> Level::getWalkoverItemAt(Position position)
{\
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
