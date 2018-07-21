#pragma once
#include <string>
#include <map>
#include <vector>
#include <istream>
#include <string>

struct CharacterStats
{
	std::string Name;
	char Symbol;
	bool Playable = false;

	bool AccessToPath = false;

	int HpStart; // starting Hp
	bool MaxHp; //if the player has a max Hp
	int HpRegain; //Amount gained at the start of tern

	int Atk;
	int AtkAccuracy; // out of a 100

	int NumberOfAtks = 1;
	std::map<std::string, int> DifferentAtkNumber;

	int AtkHpGain = 0; //Amount of HP gained for successful attack
	std::vector<std::string> AllgergicTo;


	int Def;
	int DodgeAccuracy = 0; // out of a 100

	int PotionEffect = 100; // out of a 100 
	int GoldForKill = 0; // amount gold gets per kill
	int GoldDrop; // amount dropOnDeath
};


std::istream &operator>>(std::istream &in, CharacterStats stats);
