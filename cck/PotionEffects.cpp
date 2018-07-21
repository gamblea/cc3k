#include "stdafx.h"
#include "PotionEffects.h"

std::istream &operator>>(std::istream &in, PotionEffects effects)
{
	std::string field{};

	while (in >> field)
	{
		if (field == "Name:")
		{
			in >> effects.Name;
		}
		else if (field == "Description:")
		{
			in >> effects.Description;
		}
		else if (field == "HealthEffect:")
		{
			in >> effects.HealthEffect;
		}
		else if (field == "AtkEffect:")
		{
			in >> effects.AtkEffect;
		}
		else if (field == "DefEffect")
		{
			in >> effects.HealthEffect;
		}
	}

	return in;
}