#include "stdafx.h"
#include "Character.h"
#include "Level.h"
#include "Errors.h"
#include "Event.h"

#include <memory>


Character::Character(CharacterStats stats, Position start)
	: Sprite{stats.Symbol, start}, stats { stats }, health{ stats.HpStart }
{
}

Character::~Character()
{
}

// Could throw exceptions from the Level
void Character::Move(Position pos)
{
	position = pos;
}

std::shared_ptr<Event> Character::Attack(std::shared_ptr<Character> enemy)
{
	// not completed
	bool hit = false;
	int damage = 0;

	// mutate me and the enemy 

	//make a pointer to event that is actaully a battle

	return std::make_shared<Event>(Event::EventType::Battle,std::make_shared<Character>(*this), enemy, hit, damage);
}

int Character::GetHealth() const
{
	return health;
}

int Character::GetStartingHealth() const
{
	return stats.HpStart; 
}

int Character::GetAttack() const
{
	return stats.Atk; // need to add + potion effects
}

int Character::GetDefense() const
{
	return stats.Def; // neee to add + potion effects
}

std::string Character::GetName() const
{
	return stats.Name;
}

int Character::GetGold() const
{
	return gold;
}

int Character::PickupGold(int amount)
{
	gold += amount;
	return gold;
}

Position Character::getPosFromDir(Direction dir)
{
	int changeX = 0;
	int changeY = 0;
	switch (dir)
	{
	case Direction::N:
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
	}

	return { position.x + changeX, position.y + changeY };
}