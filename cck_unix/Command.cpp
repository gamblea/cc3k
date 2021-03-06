#include "stdafx.h"
#include "Command.h"

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
		else if (actionStr == "freeze" || actionStr == "f")
		{
			action = Command::Action::Freeze;
		}
		else if (actionStr == "reset" || actionStr == "r")
		{
			action = Command::Action::Reset;
		}
		else in.setstate(std::ios_base::failbit);
	}
	else
		in.setstate(std::ios_base::failbit);


	return in;
}

std::istream &operator>>(std::istream &in, Command &command)
{
	if (in >> command.action)
	{
		if (command.action == Command::Action::Use || command.action == Command::Action::Move || command.action == Command::Action::Attack)
		{
			std::string s{};
			in >> s;
			command.direction = Helpers::strToDirection(s);
			if (command.direction == Direction::None)
			{
				in.setstate(std::ios_base::failbit);
			}
		}
	}
	return in;
}
