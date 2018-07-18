#pragma once
#include <istream>
#include <string>

struct TreasureStats
{
	std::string Name;
	int Value;
	bool CanBePickedUp;
};

std::istream &operator>>(std::istream &in, TreasureStats stats); 