#pragma once
#ifndef _DRAGON_H_
#define _DRAGON_H_

#include "Character.h"
#include <memory>

class Item;
class Event;

class Dragon : public Character {

	std::shared_ptr<Item> itemToProtect;

public:
	Dragon(CharacterStats stats,Position start, std::shared_ptr<Item> itemToProtect);
	std::shared_ptr<Item> getItem();
	std::shared_ptr<Event> Attack(std::shared_ptr<Character> enemy) override;
	~Dragon();
}

#endif
