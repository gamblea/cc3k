#pragma once
#include <string>
#include <istream>

struct PotionEffects
{
	std::string Name = "";
	int HealthEffect = 0;
	int AtkEffect = 0;
	int DefEffect = 0;
};

std::istream &operator>>(std::istream &in, PotionEffects effects);