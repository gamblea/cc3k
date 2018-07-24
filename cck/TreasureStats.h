#pragma once
#include <istream>

struct TreasureStats
{
	std::string Name = "";
	int Value = 0;
	bool CanBePickedUp = false; //can get rid of 
	int Probability = 0;

	bool ToBeGuarded = false;
	std::string GuardName = "";

	bool operator==(const TreasureStats &other) const;
	bool operator!=(const TreasureStats &other) const;
};

std::istream &operator>>(std::istream &in, TreasureStats &stats); 

