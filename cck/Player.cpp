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


std::shared_ptr<Event> Player::Use(PotionEffects effect) // called by Item
{
	return std::make_shared<Event>(Event::EventType::GetPotion, std::make_shared<Player>(*this), effect);
}

std::shared_ptr<Event> Player::Use(TreasureStats treasureStats) // called by Item
{
	// needs impementation
	std::string msg = stats.Name + "Picked up: " + std::to_string(treasureStats.Value) + " gold.";
	return std::make_shared<Event>(Event::EventType::GetTreasure, msg);
}

std::shared_ptr<Event> Player::Use(const Stairs &stairs)
{
	return std::make_shared<Event>(Event::EventType::EndLevel, "Level Complete!");
}


void Player::ResetForLevel()
{
	// reset potion effects
}
