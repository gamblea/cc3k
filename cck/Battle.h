#pragma once
#include "Character.h"
#include "Event.h"

#include <memory>

class Battle : public Event
{
private:
	std::shared_ptr<Character> attacker;
	std::shared_ptr<Character> defender;
	const bool hit;
	const int damage;

public:
	Battle(std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, bool hit, int damange);
	virtual std::string GetDescription() const override ;


	~Battle();
};

