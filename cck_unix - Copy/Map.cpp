
#include "Map.h"

#include <fstream>
#include <string>
#include <vector>
#include "Position.h"
#include "Room.h"
#include "Helpers.h"

Map::Map(std::string fileName) :fileName{fileName}
{
	ReadMap(fileName);
	BuildRooms();
}

void Map::ReadMap(std::string fileName) 
{
	std::ifstream file{ fileName };
	std::vector<Cell> tempCells;
	std::string line = "";

	for (int i = 0; i < height; i++)
	{
		std::getline(file, line);
		if ((int)line.length() == width)
		{	
			int col = 0;
			for (char c : line)
			{
				if (c >= '0' && c <= '9') {
					tempCells.emplace_back(Cell::Floor);
					existingItems.emplace(c, Position{ col, i });

				} else {
					switch (c)
					{
					case '.':
						tempCells.emplace_back(Cell::Floor);
						break;

					case '-':
						tempCells.emplace_back(Cell::WallHorz);
						break;

					case '|':
						tempCells.emplace_back(Cell::WallVert);
						break;

					case '#':
						tempCells.emplace_back(Cell::Passage);
						break;

					case '+':
						tempCells.emplace_back(Cell::Doorway);
						break;

					case ' ':
						tempCells.emplace_back(Cell::Nothing);
						break;

					default:
						throw std::runtime_error("Invalid char read from file!");
						break;

					}
				}
				++col;
			}
		}
		//else
		//	throw std::runtime_error("Invalid width of map while reading: " + width);
	}

	if ((int)tempCells.size() == width * height)
		cells = tempCells;
	 else 
	    throw std::runtime_error("Invalid read of Cells");

}

char Map::cellToChar(Cell cell)
{
	switch (cell)
	{
	case Cell::Floor:
		return '.';
		break;
	case Cell::Nothing:
		return ' ';
		break;
	case Cell::Doorway:
		return '+';
		break;
	case Cell::Passage:
		return '#';
		break;
	case Cell::WallHorz:
		return '-';
		break;
	case Cell::WallVert:
		return '|';
		break;
	default:
		throw std::runtime_error("Should be one type of Cell!");
	}
}
Map::Cell Map::charToCell(char c)
{
	switch (c)
	{
	case '.':
		return Cell::Floor;
		break;

	case '-':
		return Cell::WallHorz;
		break;

	case '|':
		return Cell::WallVert;
		break;

	case '#':
		return Cell::Passage;
		break;

	case '+':
		return Cell::Doorway;
		break;

	case ' ':
		return Cell::Nothing;
		break;

	default:
		throw std::runtime_error(c + " is not defined as a type of Cell");
		break;
	}
}

const Map::Cell& Map::GetCell(int x, int y) const
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		throw std::runtime_error("invalid index!");
	else
		return cells.at(x + y * width);
}

const Map::Cell& Map::GetCell(const Position &pos) const
{
	return GetCell(pos.x, pos.y);
}

int Map::GetWidth() const
{
	return width;
}

int Map::GetHeight() const
{
	return height;
}


std::ostream &operator<<(std::ostream &os, Map &map)
{
	for (int y = 0; y < map.height; y++)
	{
		for (int x = 0; x < map.width; x++)
		{
			os << map.cellToChar(map.GetCell(x, y));
		}
		os << std::endl;
	}

	for (auto room : map.rooms)
	{
		os << room;
	}

	return os;
}


bool Map::ContainedInARoom(Position pos)
{
	for (Room &room : rooms)
	{
		if (room.ContainsPosition(pos)) 
			return true;
	}
	return false;
}

void Map::AddAttachedToRoom(Room &room, Position current)
{
	if (current.x >= 0 && current.x < width && current.y >= 0 && current.y < height)
	{
		if (GetCell(current.x, current.y) == Cell::Floor && !ContainedInARoom(current))
		{
			room.AddPosition(current);
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (!(i == 0 && j == 0))
						AddAttachedToRoom(room, Position{ current.x + i, current.y + j });
				}
			}

		}
	}
}

void Map::BuildRooms()
{
	rooms.clear();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (GetCell(x, y) == Cell::Floor && !ContainedInARoom(Position{ x, y }))
			{
				rooms.emplace_back(Room{});
				AddAttachedToRoom(rooms.back(), Position{ x,y });
			}
		}
	}
}

const std::vector<Map::Cell>& Map::GetCells() const
{
	return cells;
}


Map::~Map()
{

}

char operator>>(Map::Cell cell, char &c)
{
	char newC = 0;
	switch (cell)
	{
	case Map::Cell::Floor:
		c = '.';
		break;
	case Map::Cell::Nothing:
		c = ' ';
		break;
	case Map::Cell::Doorway:
		c = '+';
		break;
	case Map::Cell::Passage:
		c = '#';
		break;
	case Map::Cell::WallHorz:
		c = '-';
		break;
	case Map::Cell::WallVert:
		c =  '|';
		break;
	default:
		throw std::runtime_error("Should be one type of Cell!");
	}
	return c;
}

std::string Map::GetName() const
{
	return fileName;
}

const std::vector<Room>& Map::GetRooms()
{
	return rooms;
}

const Room &Map::GetRandomRoom() const
{
	int size = rooms.size();
	int index = Helpers::getRandom(0, size - 1);
	return rooms.at(index);
}

Position Map::GetRandomPosition() const
{
	return GetRandomRoom().GetRandomPositionInRoom();
}

int Map::GetNumRooms() const
{
	return rooms.size();
}

Position Map::GetPositionFromRoom(int room) const
{
	return rooms.at(room).GetRandomPositionInRoom();
}

const std::map<char, Position> &Map::GetExistingItems()
{
	return existingItems;
}
