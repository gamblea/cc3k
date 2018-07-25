#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "Position.h"

class Room;

class Map
{
public:
	enum class Cell { Floor, WallVert, WallHorz, Doorway, Passage, Nothing };

private:
	const int width = 79;
	const int height = 25;
	std::vector<Cell> cells;

	std::vector<Room> rooms;

	// find numbers that are from 0 - 9
	std::map<char, Position> existingItems;

	void AddAttachedToRoom(Room &room, Position current);
	bool ContainedInARoom(Position pos);
	char cellToChar(Cell cell);
	Cell charToCell(char c);
	std::string fileName;

	void ReadMap(std::string fileName); // Map name + ".map";
	void BuildRooms();


public: 
	Map(std::string name);
	~Map();
	
	const Cell& GetCell(int x, int y) const;
	const Cell& GetCell(const Position &pos) const;
	const std::vector<Cell> &GetCells() const;
	int GetWidth() const;
	int GetHeight() const;
	std::string GetName() const;

	const std::vector<Room>& GetRooms();
	const Room& GetRandomRoom() const;
	Position GetRandomPosition() const;

	int GetNumRooms() const;

	Position GetPositionFromRoom(int room) const;

	const std::map<char, Position> &GetExistingItems();

	friend std::ostream &operator<<(std::ostream &os, Map &map);

};

char operator>>(Map::Cell cell, char &c);

std::ostream &operator<<(std::ostream &os, Map &map);

#endif 
