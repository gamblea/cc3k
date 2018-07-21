#ifndef _DRAGON_H_
#define _DRAGON_H_
#include "Character.h"
// std::shared_ptr<type> obj = std::make_shared<type>(paramas);

class Dragon : public Character {

	std::shared_ptr<Item> itemToProtect;

public:
	Dragon(CharacterStats stats, Item itemToProtect);
	std::shared_ptr<Event> getItem();
	std::shared_ptr<Event> Attack(std::shared_ptr<Character> enemy) override;
	~Dragon();
}

#endif
