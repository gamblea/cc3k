#pragma once
#include <string>
#include <memory>

class Character;
class Player;
struct PotionEffects;

class Event
{
public:
	enum class EventType {Battle, EndLevel, GetPotion, GetTreasure, See, Move, None};
private:
	std::string description;
	EventType type;
public:
	Event(EventType type, std::string description);
	Event(EventType type, std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, bool hit, int damage);
	Event(EventType type, std::shared_ptr<Player> player, PotionEffects effect);

	virtual ~Event();

	virtual std::string GetDescription() const;
	EventType GetType() const;
};

std::ostream &operator<<(std::ostream &out, std::shared_ptr<Event> event);
