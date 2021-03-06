#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <memory>
#include "Direction.h"
#include "Sprite.h"

class Character;
class Player;
struct PotionEffects;
	
typedef std::shared_ptr<Character> PCharacter;

class Event
{
public:
	enum class EventType {Battle, EndLevel, GetPotion, GetTreasure, See, Move, Died, Won, Quit, None};
private:
	std::string description;
	EventType type;
public:
	Event(EventType type, std::string description);
	Event(EventType type, Character *attacker, Character *defender, bool hit, int damage);
	Event(EventType type, Player player, PotionEffects effect);
	Event(EventType type, Player *player);
	Event(EventType type, Sprite *sprite, Direction direction);

	virtual ~Event();
	virtual std::string GetDescription() const;
	EventType GetType() const;
};

std::ostream &operator<<(std::ostream &out, const Event &event);

#endif
