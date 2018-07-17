#pragma once
#include <map>

class CharacterStats;
class PotionEffects;
class TreasureStats;

struct GameConfig
{
	std::map<std::string, CharacterStats> Characters;
	std::map<std::string, PotionEffects> Potions;
	std::map<std::string, TreasureStats> Treasures;
};

