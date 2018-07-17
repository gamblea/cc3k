#include "stdafx.h"
#include "TreasureStats.h"
#include <string>


std::istream &operator>>(std::istream &in, TreasureStats stats)
{
	std::string field = "";
	bool valueSet = false;
	bool pickedUpSet = false;

	while (in >> field)
	{
		if (field == "Value:")
		{
			in >> stats.Value;
			valueSet = true;
		}
		else if (field == "CanBePickedUp:")
		{
			std::string s{};
			in >> s;
			stats.CanBePickedUp = stringToBool(s);
			pickedUpSet = true;
		}
	}
	if (!valueSet || !pickedUpSet) throw std::runtime_error("TreasureStats cannot be fully read in!");

	return in;
}

bool stringToBool(std::string str)
{
	if (str == "true") return true;
	else if (str == "false") return false;
	else throw std::runtime_error("Expected true or false");
}