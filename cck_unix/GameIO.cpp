#include "stdafx.h"
#include "GameIO.h"
#include "CharacterStats.h"
#include "Map.h"
#include "Sprite.h"
#include "Player.h"
#include "Level.h"
#include "Event.h"
#include "Character.h"

#include <string>



GameIO::GameIO(std::istream &in, std::ostream &out)
	: in{in}, out{out}
{
}


GameIO::~GameIO()
{
}

Command GameIO::GetCommand()
{
	bool validCommand = false;
	Command command{};
	while (!validCommand)
	{
		out << "Command: " << std::endl;
		if (in >> command)
			validCommand = true;
		else
		{
			if(in.eof()) 
				exit(0);
			out << "Invalid!" << std::endl;
			in.clear();
			in.ignore(100000, '\n');
		}
	}

	return command;
}

CharacterStats GameIO::GetPlayerRace(const std::map<std::string, CharacterStats> &races)
{
	bool selected = false;
	std::string raceName;
	CharacterStats stats;

	while (!selected)
	{
		out << " Select a Race: Shade(S), Drow(D), Vampire(V), Troll(T), Goblin(G)" << std::endl;
		if (in >> raceName)
		{
			if(raceName == "S" || raceName == "s") raceName = "Shade";
			else if(raceName == "D" || raceName == "d") raceName = "Drow";
			else if(raceName == "V" || raceName == "v") raceName = "Vampire";
			else if(raceName == "T" || raceName == "t") raceName = "Troll";
			else if(raceName == "G" || raceName == "g") raceName = "Goblin";
			if (races.find(raceName) != races.end() && races.find(raceName)->second.Playable == true)
			{
				selected = true;
				stats = races.find(raceName)->second;
			}
				
		}
		else
		{
			out << "Invalid!" << std::endl;
			in.clear();
			in.ignore(100000, '\n');
		}
	}
	return stats;
}

void GameIO::UpdateBoard()
{
	const Map& map = level->GetMap();
	if (height < 1 || height != map.GetHeight() || width < 1 || width != map.GetWidth())
	{
		board.clear();
		width = map.GetWidth();
		height = map.GetHeight();

		int i = 0;
		for (const Map::Cell& cell : map.GetCells())
		{
			if (i == width) i = 0;
			if (i == 0)
			{
				board.emplace_back(std::vector<char>{});
			}
			char c = '0';
			cell >> c;
			board.back().emplace_back(c);
			i++;
		}
		if (height != board.size()) throw std::runtime_error("Update of Board failed!");
	}
	else if (width == map.GetWidth() && height == map.GetHeight())
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				const Map::Cell &cell = map.GetCell(x, y);
				char c = 0;
				cell >> c;
				board.at(y).at(x) = c;
			}
		}
	}
	else throw std::runtime_error("Update of Board failed!");

	for (const std::shared_ptr<const Sprite> sprite : level->GetSprites())
	{
		char &element = getBoardAt(sprite->GetPosition());
		element = sprite->GetSymbol();
	}

	// draws player over everything
	char &element = getBoardAt((level->GetPlayer())->GetPosition());
	element = level->GetPlayer()->GetSymbol();
}

char & GameIO::getBoardAt(Position pos)
{
	return board.at(pos.y).at(pos.x);
}


void GameIO::DrawBoard()
{
	out << board;
}

void GameIO::DrawDetails()
{
	const Map& map = level->GetMap();
	const std::shared_ptr<Player> player = level->GetPlayer();
	int width = board.back().size();
	std::string playerRaceAndGold = "Race: " + player->GetRace() + " Gold: "  + std::to_string(player->GetGold());
	std::string levelName = "Level " + std::to_string(level->GetLevelNum());
	PrintBothEnds(playerRaceAndGold, levelName);
	out << "HP: " << player->GetHealth() << "/" << player->GetStartingHealth() << std::endl;
	out << "Atk: " << player->GetAttack() << std::endl;
	out << "Def: " << player->GetDefense() << std::endl;
	int outputed = 0;
	for (const std::shared_ptr<const Event> event : level->GetEvents())
	{
		out << *event;
		outputed++;
		if (outputed == 2)
		{
			outputed = 0;
			out << std::endl;
		}
	}
	if (outputed != 0)
		out << std::endl;
}

void GameIO::LevelCompleted()
{
	out << "Level Completed!" << std::endl;
}

void GameIO::InvalidCommand(const std::string &msg) const 
{
	out << "Invalid: " << msg << std::endl;
}

void GameIO::QuitGame()
{
	out << "Game over! You gave up :(" << std::endl;
}

void GameIO::AttachLevel(std::shared_ptr<Level> level)
{
	this->level = level;
}



bool GameIO::PlayAgain()
{
	bool valid = false;
	while (!valid)
	{
		out << "Play Again? Enter (y/n): " << std::endl;
		std::string input{};
		in >> input;
		if (input == "y")
		{
			valid = true;
			return true;
		}
		else if (input == "n")
		{
			valid = true;
			return false;
		}
	}
}



void GameIO::EndGame(Player player, bool won)
{
	out << std::endl;
	if (won) out << "You win! Score: " << player.GetScore();
	else out << "You lose! Score: " << player.GetScore();
	out << std::endl;
}



void GameIO::PrintBothEnds(const std::string &front, const std::string &back) const
{
	out << front;
	int spaces = width - front.length() - back.length();
	if (spaces < 0) throw std::runtime_error("Spaces is less than 0");
	out << std::string(spaces, ' ');
	out << back << std::endl;
}

std::ostream &operator<< (std::ostream &out, const std::vector<std::vector<char>> &dVector)
{
	for (const std::vector<char> &row : dVector)
	{
		for (const char &c : row)
		{
			out << c;
		}
		out << std::endl;
	}
	return out;
}

bool stringToBool(std::string str)
{
	if (str == "true") return true;
	else if (str == "false") return false;
	else throw std::runtime_error("Expected true or false");
}
