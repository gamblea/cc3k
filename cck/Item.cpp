#include "stdafx.h"
#include "Item.h"


Item::Item(char symbol, Position position, Item::PickupMethod method, bool toBeGuarded, std::string guardName)
	: Sprite{ symbol, position }, method{ method }, toBeGuarded{ toBeGuarded }, guardName{guardName} 
{

}

Item::Item(char symbol, Position position, Item::PickupMethod method)
	: Sprite{ symbol, position }, method{ method }, toBeGuarded{ false }
{
}

Item::~Item()
{
}

Item::PickupMethod Item::GetPickupMethod()
{
	return method;
}

std::string Item::GetGuardName() const
{
	return guardName;
}

bool Item::ToBeGuarded() const
{
	return toBeGuarded;
}

void Item::SetGuarded(bool value)
{
	guarded = value;
}

bool Item::GetGuarded() const
{
	return guarded;
}




	

