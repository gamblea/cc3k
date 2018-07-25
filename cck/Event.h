#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <memory>
#include "Direction.h"

class Character;
class Player;
struct PotionEffects;

class Event
{
public:
	enum class EventType {Battle, EndLevel, GetPotion, GetTreasure, See, Move, Died, Won, Quit, None};
private:
	std::string description;
	EventType type;
public:
	Event(EventType type, std::string description);
	Event(EventType type, Character character, Direction direction);
	Event(EventType type, Character &attacker, Character &defender, bool hit, int damage);
	Event(EventType type, Player player, PotionEffects effect);
	Event(EventType type, Player player);

	virtual ~Event();
	virtual std::string GetDescription() const;
	EventType GetType() const;
};

std::ostream &operator<<(std::ostream &out, const Event &event);

#endif
