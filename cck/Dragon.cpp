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

		int dodgeChance = Helpers::getRandom(0, 100);
		int attackChange = Helpers::getRandom(0, 100);
		bool success = true;
		
		if (r > stats.AtkAccuray) {
			success = false;
		} else if {
			(r > enemy->stats.dodgeAccuracy)success = false;
		}
		
		if (success) {
			health += stats.AtkHpGain;
		}
		
		if(stats.MaxHp && health > stats.HpStart) {
			health = stats.HpStart;
		}

		int damage = std::ceil((100/(100+enemy->stats.Def))*stats.Atk);
		enemy->DecrementHealth(damage);
		std::shared_ptr<Event> event = std::make_shared<Event>(Event::EventType::Battle, std::make_shared<Character>(this), enemy, success, damage);
		
		return event; 
	} else {
		return std::make_shared<Event>(Event::EventType::None, "");
	}
}

Dragon::~Dragon() {
	itemToProtect->guarded = false;
}