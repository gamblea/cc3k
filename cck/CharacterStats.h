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
	int Probability = 0; // int / 18

	bool AccessToPath = false;

	int HpStart; // starting Hp
	bool MaxHp; //if the player has a max Hp
	int HpRegain; //Amount gained at the start of tern

	int Atk;
	int AtkAccuracy; // out of a 100

	int NumberOfAtks = 1;
	std::map<std::string, int> DifferentAtkNumber;
	std::map<std::string, int> DamageEffect; // out of 100

	int AtkHpGain = 0; //Amount of HP gained for successful attack
	std::vector<std::string> AllergicTo;


	int Def;
	int DodgeAccuracy = 0; // out of a 100

	int PotionEffect = 100; // out of a 100 
	int GoldForKill = 0; // amount gold gets per kill
	int NumPiles = 0; // number of piles of gold dropped
	int GoldDrop = 0; // value of Gold dropped

	// only checks if names are equal right now!
	bool operator==(const CharacterStats &other) const;
	bool operator!=(const CharacterStats &other) const;
};


std::istream &operator>>(std::istream &in, CharacterStats &stats);
