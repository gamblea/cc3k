#include "stdafx.h"
#include "Item.h"


Item::Item(char symbol, Position position, Item::PickupMethod method, bool guarded) 
	: Sprite{ symbol, position }, method{ method }, guarded{guarded}
{
}


Item::~Item()
{
}

Item::PickupMethod Item::GetPickupMethod()
{
	return method;
}

bool Item::IsGuarded() const
{
	return guarded;
}

void Item::SetGuarded(bool value)
{
	guarded = value;
}
