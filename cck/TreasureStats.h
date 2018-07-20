#pragma once
#include <istream>

struct TreasureStats
{
	int Value;
	bool CanBePickedUp;
};

std::istream &operator>>(std::istream &in, TreasureStats stats); 