#include "stdafx.h"
#include "CharacterStats.h"
#include "Helpers.h"


std::istream &operator>>(std::istream &in, CharacterStats &stats)
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
			std::string val{};
			in >> val;
			stats.MaxHp = Helpers::stringToBool(val);
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
			stats.AllergicTo.emplace_back(name);
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
		else if (field == "GoldDrop:")
		{
			in >> stats.GoldDrop;
		}
		else if (field == "Probability:") 
		{
			in >> stats.Probability;
		}
		else if (field == "DamageEffect:") 
		{
			std::string name{};
			int n;
			in >> name;
			in >> n;
			stats.DamageEffect.emplace(name, n);
		}
		else if (field == "NumPiles:") 
		{
			in >> stats.NumPiles;
		}
		else if (field == "Neutral:")
		{
			std::string strBool{};
			in >> strBool;
			stats.Neutral = Helpers::stringToBool(strBool);
		}
		else if (field == "ScoreBonus:")
		{
			in >> stats.ScoreBonus;
		}
	}
	return in;
}


bool CharacterStats::operator==(const CharacterStats & other) const
{
	return Name == other.Name;
}

bool CharacterStats::operator!=(const CharacterStats & other) const
{
	return !(*this == other);
}
