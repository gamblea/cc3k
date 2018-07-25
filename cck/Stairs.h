#ifndef STAIRS_H
#define STAIRS_H
#include "Item.h"
class Stairs : public Item
{
private:
	virtual bool isEqual(const Sprite& other) const;
public:
	Stairs(Position position);
	virtual ~Stairs();

	std::shared_ptr<Event> GetPickedUpBy(std::shared_ptr<Player> player) override;
};
#endif
