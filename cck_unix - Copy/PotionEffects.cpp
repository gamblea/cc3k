
#include "PotionEffects.h"

std::istream &operator>>(std::istream &in, PotionEffects &effects)
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
		else if (field == "DefEffect:")
		{
			in >> effects.DefEffect;
		}
	}

	return in;
}

bool PotionEffects::operator==(const PotionEffects & other) const
{
	return Name == other.Name && HealthEffect == other.HealthEffect && AtkEffect == other.AtkEffect
		&& DefEffect == other.DefEffect;
}

bool PotionEffects::operator!=(const PotionEffects & other) const
{
	return !(*this == other);
}
