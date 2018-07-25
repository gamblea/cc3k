#ifndef COMMAND_H
#define COMMAND_H
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


std::istream &operator>>(std::istream &in, Command::Action &action);

std::istream &operator>>(std::istream &in, Command &command);

#endif
