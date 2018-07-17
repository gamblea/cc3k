#include "stdafx.h"
#include "Event.h"
#include "Character.h"
#include "Player.h"

#include <string>


Event::Event(EventType type, std::string description) : type{ type }, description{ description }
{}

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

Event::Event(EventType type, std::shared_ptr<Player> player, PotionEffects effects) :type{type}
{
	description = "The " + player->GetName() + " picked up a " + effects.Description + ".";
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

