#include "stdafx.h"
#include "Event.h"
#include "Character.h"
#include "Player.h"
#include "Helpers.h"

#include <string>


Event::Event(EventType type, std::string description) : type{ type }, description{ description }
{}

Event::Event(EventType type, std::shared_ptr<Character> character, Direction direction)
{
	description = character->GetName() + " moved " + Helpers::directionToStr(direction) + ".";
}

Event::Event(EventType type, std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, bool hit, int damage) : type{ type }
{
	if (defender->GetHealth() <= 0)
	{
		description = "The " + attacker->GetName() + " killed " + " the " + defender->GetName() + ".";
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

Event::Event(EventType type, std::shared_ptr<Player> player, PotionEffects effect) 
	: type{type}
{
	std::string effects{};
	if (effect.AtkEffect != 0)
		effects += "Atk: " + std::to_string(effect.AtkEffect);
	if (effect.DefEffect != 0)
		effects += "Def: " + std::to_string(effect.DefEffect);
	if (effect.HealthEffect != 0)
		effects += "Hp: " + std::to_string(effect.HealthEffect);
	description = player->GetName() + " drank " + effect.Description + effects;
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

std::ostream &operator<<(std::ostream &out, std::shared_ptr<Event> event)
{
	out << event->GetDescription();
	return out;
}

