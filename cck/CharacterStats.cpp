#include "stdafx.h"
#include "CharacterStats.h"
#include "Helpers.h"


std::istream &operator>>(std::istream &in, CharacterStats stats)
{
	std::string field{};

	while (in >> field)
	{
		if (field == "Name:")
		{
			in >> stats.Name;
		}
		else if (field == "Symbol:")
		{
			in >> stats.Symbol;
		}
		else if (field == "Playable:")
		{
			std::string val{};
			in >> val;
			stats.Playable = Helpers::stringToBool(val);
		}
		else if (field == "AccessToPath:")
		{
			std::string val{};
			in >> val;
			stats.AccessToPath = Helpers::stringToBool(val);
		}
		else if (field == "HpStart:")
		{
			in >> stats.HpStart;
		}
		else if (field == "MaxHp:")
		{
			in >> stats.MaxHp;
		}
		else if (field == "HpRegain:")
		{
			in >> stats.HpRegain;
		}
		else if (field == "Atk:")
		{
			in >> stats.Atk;
		}
		else if (field == "AtkAccuracy:")
		{
			in >> stats.AtkAccuracy;
		}
		else if (field == "NumberOfAtks")
		{
			in >> stats.NumberOfAtks;
		}
		else if (field == "DifferentAtkNumber:")
		{
			std::string str{};
			int n = 0;
			in >> str;
			in >> n;
			stats.DifferentAtkNumber.emplace(str, n);
		}
		else if (field == "AtkHpGain:")
		{
			in >> stats.AtkHpGain;
		}
		else if (field == "AllergicTo:")
		{
			std::string name{};
			in >> name;
			stats.AllgergicTo.emplace_back(name);
		}
		else if (field == "Def:")
		{
			in >> stats.Def;
		}
		else if (field == "DodgeAccuracy:")
		{
			in >> stats.DodgeAccuracy;
		}
		else if (field == "PotionEffect:")
		{
			in >> stats.PotionEffect;
		}
		else if (field == "GoldForKill:")
		{
			in >> stats.GoldForKill;
		}
		else if (field == "GoldDrop")
		{
			in >> stats.GoldDrop;
		}
	}
	return in;
}

bool stringToBool(std::string str)
{
	if (str == "true") return true;
	else if (str == "false") return false;
	else throw std::runtime_error("Expected true or false");
}