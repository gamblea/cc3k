Dragon::Dragon(CharacterStats stats, Position start, Item itemToProtect):
	Character{stats, start}, itemToProtect{itemToProtect}
	{}

std::shared_ptr<Event> Dragon::getItem() {
	return itemToProtect;
}

std::shared_ptr<Event> Dragon::Attack(std::shared_ptr<Character> enemy) {
	myPosition = getPosition();
	protectedPosition = itemToProtect->getPostion();
	enemyPosition = enemy->getPostion();
	
	myDiffX = myPosition.x - enemyPosition.x;
	myDiffY = myPosition.y - enemyPosition.y;

	protectedDiffX = myPosition.x - protectedPosition.x;
	protectedDiffY = myPosition.y - protectedPosition.y;

	if ((myDiffX <= 1 && myDiffY <= 1)
		|| (protectedDiffX <= 1 && protectedDiffY <= 1)) {
	
	} 
}

Dragon::~Dragon() {}