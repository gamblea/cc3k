#include "stdafx.h"
#include "Player.h"
#include "Event.h"


Player::Player(CharacterStats stats, Position start)
	: Character{ stats, start}
{
	stats.Symbol = '@';
}

Player::Player(CharacterStats stats)
	: Character{ stats, {0,0} }
{
	stats.Symbol = '@';
}


Player::~Player()
{
}

int Player::GetAttack()
{
	return stats.Atk + AtkChange;
}

int Plaer::GetDefense()
{
	return stats.Def + DefChange;
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

	if(GetAttack() < 0) AtkChange = -stats.Atk;
	if(GetDefense() < 0) DefChange = -stats.Def;
	if(getMaxHealth() && health > GetStartingHealth()) health = GetStartingHealth();
	
	return std::make_shared<Event>(Event::EventType::GetPotion, std::make_shared<Player>(*this), effect);
}

std::shared_ptr<Event> Player::Use(TreasureStats treasureStats) // called by Item
{
	gold += treasureStats.Value;
	std::string msg = stats.Name + " picked up: " + std::to_string(treasureStats.Value) + " gold from a " + treasureStats.Name + ".";
	return std::make_shared<Event>(Event::EventType::GetTreasure, msg);
}

std::shared_ptr<Event> Player::Use(const Stairs &stairs)
{
	
	return std::make_shared<Event>(Event::EventType::EndLevel, "Level Complete!");
}


void Player::ResetForLevel()
{
	AtkChange = 0;
	DefChnage = 0;
}
