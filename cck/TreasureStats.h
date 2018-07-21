#pragma once
#include <istream>

struct TreasureStats
{
	std::string Name;
	int Value;
	bool CanBePickedUp;
	int Probability;
};

std::istream &operator>>(std::istream &in, TreasureStats stats); 