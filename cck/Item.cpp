#include "stdafx.h"
#include "Item.h"


Item::Item(char symbol, Position position, Item::PickupMethod method) 
	: Sprite{ symbol, position }, method{ method }
{
}


Item::~Item()
{
}

Item::PickupMethod Item::GetPickupMethod()
{
	return method;
}
