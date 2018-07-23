#include "stdafx.h"
#include "TreasureStats.h"
#include <string>
#include "Helpers.h"


std::istream &operator>>(std::istream &in, TreasureStats stats)
{
	std::string field = "";
	bool valueSet = false;
	bool pickedUpSet = false;
	bool nameSet = false;

	while (in >> field)
	{

		if (field == "Name:")
		{
			in >> stats.Name;
			nameSet = true;
		}
		else if (field == "Value:")
		{
			in >> stats.Value;
			valueSet = true;
		}
		else if (field == "CanBePickedUp:")
		{
			std::string s{};
			in >> s;
			stats.CanBePickedUp = Helpers::stringToBool(s);
			pickedUpSet = true;
		}
		else if (field == "GuardName:")
		{
			stats.ToBeGuarded = true;
			in >> stats.GuardName;
		}
	}
	if (!valueSet || !pickedUpSet || !nameSet) throw std::runtime_error("TreasureStats cannot be fully read in!");

	return in;
}

bool TreasureStats::operator==(const TreasureStats & other) const
{
	return Name == other.Name && Value == other.Value;
}

bool TreasureStats::operator!=(const TreasureStats & other) const
{
	return !(*this == other);
}
