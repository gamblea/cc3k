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
};

std::istream &operator>>(std::istream &in, TreasureStats stats); 

