#pragma once
#include "Direction.h"
#include "Errors.h"
#include <istream>
#include <string>

struct Command
{
	enum class Action { None, Move, Attack, Use, Quit};

	Action action = Action::None;
	Direction direction = Direction::None;
};


std::istream &operator>>(std::istream &in, Command::Action &action)
{
	std::string actionStr{};

	if (in >> actionStr)
	{
		if (actionStr == "move" || actionStr == "m")
		{
			action = Command::Action::Move;
		}
		else if (actionStr == "attack" || actionStr == "a")
		{
			action = Command::Action::Attack;
		}
		else if (actionStr == "use" || actionStr == "u")
		{
			action = Command::Action::Use;
		}
		else if (actionStr == "quit" || actionStr == "q")
		{
			action = Command::Action::Quit;
		}
		in.setstate(std::ios_base::failbit);
	}
	else
		in.setstate(std::ios_base::failbit);
	

	return in;
}

std::istream &operator>>(std::istream &in, Command &command)
{
	if (in >> command.action)
	{
		if (command.action != Command::Action::Quit && command.action != Command::Action::None)
			in >> command.direction;
	}
	return in;
}
