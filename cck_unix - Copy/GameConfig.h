#ifndef GAMECONFIG_H
#define GAMECONFIG_H
#include <map>
#include <string>

struct CharacterStats;
struct PotionEffects;
struct TreasureStats;

struct GameConfig
{
	std::map<std::string, CharacterStats> Characters;
	std::map<std::string, PotionEffects> Potions;
	std::map<std::string, TreasureStats> Treasures;
	std::string floorFile = "floor.map";
};
#endif
