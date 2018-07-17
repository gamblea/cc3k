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
}

std::shared_ptr<Event> Player::Use(TreasureStats stats) // called by Item
{
}

std::shared_ptr<Event> Player::Use(const Stairs &stairs)
{
	return std::make_shared<Event>(Event::EventType::EndLevel, "Level Complete!");
}


void Player::ResetForLevel()
{
	finishedLevel = false;
	// reset potion effects
}
