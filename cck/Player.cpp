#include "stdafx.h"
#include "Player.h"
#include "Event.h"


bool Player::isEqual(const Sprite & other) const
{
	try
	{
		const Player &otherCharacter = dynamic_cast<const Player &>(other);
		if (position == otherCharacter.position && stats == otherCharacter.stats && health == otherCharacter.health
			&& gold == otherCharacter.gold)
		{
			return true;
		}
		else return false;
	}
	catch (const std::bad_cast&)
	{
		return false;
	}
}

Player::Player(CharacterStats stats, Position start)
	: Character{ stats, start}
{
	this->symbol = '@';
}

Player::Player(CharacterStats stats)
	: Character{ stats, {0,0} }
{
	this->symbol = '@';
}


Player::~Player()
{
}


int Player::GetAttack() const
{
	return stats.Atk + AtkChange;
}

int Player::GetDefense() const
{
	return stats.Def + DefChange;
}

std::string Player::GetName() const
{
	return "Player";
}

std::shared_ptr<Event> Player::Use(PotionEffects effect) // called by Item
{

	if(stats.PotionEffect != 100){
		effect.DefEffect = stats.PotionEffect * effect.DefEffect / 100;
		effect.AtkEffect = stats.PotionEffect * effect.AtkEffect / 100;
		effect.HealthEffect = stats.PotionEffect * effect.HealthEffect / 100;
	}	

	DefChange += effect.DefEffect;
	AtkChange += effect.AtkEffect;
	health += effect.HealthEffect;

	if (GetAttack() < 0)
		AtkChange = 0;
	if (GetDefense() < 0)
		DefChange = 0;
	if(stats.MaxHp && health > GetStartingHealth())
		health = GetStartingHealth();
	
	return std::make_shared<Event>(Event::EventType::GetPotion, *this, effect);
}

std::shared_ptr<Event> Player::Use(TreasureStats treasureStats) // called by Item
{
	gold += treasureStats.Value;
	std::string msg = stats.Name + " picked up: " + std::to_string(treasureStats.Value) + " gold.";
	return std::make_shared<Event>(Event::EventType::GetTreasure, msg);
}

std::shared_ptr<Event> Player::Use(const Stairs &stairs)
{
	
	return std::make_shared<Event>(Event::EventType::EndLevel, "Level Completed!");
}


void Player::ResetForLevel()
{
	AtkChange = 0;
	DefChange = 0;
}
