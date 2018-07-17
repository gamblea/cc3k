#include "stdafx.h"
#include "Battle.h"

Battle::Battle(std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, bool hit, int damange)
	: attacker{attacker}, defender{defender}, hit{hit}, damage{damage}
{
}


Battle::~Battle()
{
}

std::string Battle::GetDescription() const
{
	if (hit)
	{
		return "The " + attacker->GetName() + " dealt " + std::to_string(damage)  + " to the " + defender->GetName() 
			+ " (" + std::to_string(defender->GetHealth()) + "/" + std::to_string(defender->GetStartingHealth()) + ").";
	}
	else
	{
		return "The " + attacker->GetName() + " missed the " + defender->GetName()
			+ " (" + std::to_string(defender->GetHealth()) + "/" + std::to_string(defender->GetStartingHealth()) + ").";
	}
	
}