#ifndef POTIONEFFECTS_H
#define POTIONEFFECTS_H
#include <string>
#include <istream>

struct PotionEffects
{
	std::string Name = "";
	std::string Description = "";
	int HealthEffect = 0;
	int AtkEffect = 0;
	int DefEffect = 0;

	// all except description
	bool operator==(const PotionEffects &other) const;
	bool operator!=(const PotionEffects &other) const;
};

std::istream &operator>>(std::istream &in, PotionEffects &effects);
#endif
