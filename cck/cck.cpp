// cck.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Map.h"


int main()
{
	Map map{ 79, 25 };
	map.ReadMap("floor.txt");
	map.BuildRooms();
	std::cout << map;
}

