#pragma once
#include <istream>

struct TreasureStats
{
	std::string Name;
	int Value;
	bool CanBePickedUp;
	int Probability;

	bool ToBeGuarded = false;
	std::string GuardName = "";

	bool operator==(const TreasureStats &other) const;
	bool operator!=(const TreasureStats &other) const;
};

std::istream &operator>>(std::istream &in, TreasureStats stats); 

