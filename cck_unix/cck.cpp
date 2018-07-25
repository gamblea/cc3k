// cck.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include <sstream>
#include <string>


int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		
	}
	else if (argc == 3)
	{
			
	}
	else
	{
		Game game{ "Characters","Potions","Treasures" };
		game.Start();
	}
}

