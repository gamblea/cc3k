#include "stdafx.h"
#include "Event.h"
#include "Character.h"
#include "Player.h"
#include "Helpers.h"

#include <string>


Event::Event(EventType type, std::string description) : type{ type }, description{ description }
{}

Event::Event(Event::EventType type, Character *attacker, Character *defender, bool hit, int damage) 
	: type{ type }
{
	if (defender->GetHealth() <= 0)
	{
		description = "The " + attacker->GetName() + " killed " + "the " + defender->GetName() + ".";
	}
	else
	{
		if (hit)
		{
			description = "The " + attacker->GetName() + " dealt " + std::to_string(damage) + " to the " + defender->GetName()
				+ " (" + std::to_string(defender->GetHealth()) + "/" + std::to_string(defender->GetStartingHealth()) + ").";
		}
		else
		{
			description = "The " + attacker->GetName() + " missed the " + defender->GetName()
				+ " (" + std::to_string(defender->GetHealth()) + "/" + std::to_string(defender->GetStartingHealth()) + ").";
		}
	}
}

Event::Event(EventType type, Player player, PotionEffects effect)
	: type{type}
{
	std::string effects{};
	if (effect.AtkEffect != 0)
		effects += "Atk: " + std::to_string(effect.AtkEffect);
	if (effect.DefEffect != 0)
		effects += "Def: " + std::to_string(effect.DefEffect);
	if (effect.HealthEffect != 0)
		effects += "Hp: " + std::to_string(effect.HealthEffect);
	description = player.GetName() + " drank " + effect.Description + " " + effects + ".";
}

Event::Event(EventType type, Player *player)
	: type{type}
{
	switch (type)
	{
	case Event::EventType::Battle:
		break;
	case Event::EventType::EndLevel:
		description = "The player reached the stairs. Level Complete!";
		break;
	case Event::EventType::GetPotion:
		break;
	case Event::EventType::GetTreasure:
		break;
	case Event::EventType::See:
		break;
	case Event::EventType::Move:
		break;
	case Event::EventType::Won:
		description = "The awesome player won! Score: " + player->GetScore();
		break;
	case Event::EventType::Quit:
		description = "The player quit, what a whimp! Score: " + player->GetScore();
		break;
	case Event::EventType::Died:
		description = "The player died! Score: " + player->GetScore();
		break;
	case Event::EventType::None:
		break;
	default:
		break;
	}
}

Event::Event(EventType type, Sprite *sprite, Direction direction)
	:type{type}
{
	switch (type)
	{
	case Event::EventType::Battle:
		break;
	case Event::EventType::EndLevel:
		break;
	case Event::EventType::GetPotion:
		break;
	case Event::EventType::GetTreasure:
		break;
	case Event::EventType::See:
		this->description = "You see a " + sprite->GetName() + " " + Helpers::directionToStr(direction) + ".";
		break;
	case Event::EventType::Move:
		this->description = sprite->GetName() + " moved " + Helpers::directionToStr(direction) + ".";
		break;
	case Event::EventType::Died:
		break;
	case Event::EventType::Won:
		break;
	case Event::EventType::Quit:
		break;
	case Event::EventType::None:
		break;
	default:
		break;
	}
	
}





Event::~Event()
{
}

std::string Event::GetDescription() const
{
	return description;
}

Event::EventType Event::GetType() const
{
	return type;
}

std::ostream &operator<<(std::ostream &out, const Event &event)
{
	out << event.GetDescription();
	return out;
}

