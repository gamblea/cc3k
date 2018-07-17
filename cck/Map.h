#pragma once
#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector>
#include <iostream>
#include "Position.h"

class Map
{
public:
	enum class Cell { Floor, WallVert, WallHorz, Doorway, Passage, Nothing };

private:
	const int width = 79;
	const int height = 25;
	std::vector<Cell> cells;
	std::vector<std::vector<Position>> rooms;

	void AddAttachedToRoom(std::vector<Position> &room, Position current);
	bool ContainedInARoom(int x, int y);
	char cellToChar(Cell cell);
	Cell charToCell(char c);
	std::string name;

	void ReadMap(std::string fileName); // Map name + ".map";
	void BuildRooms();

public: 
	Map(std::string name);
	
	const Cell& GetCell(int x, int y) const;
	const Cell& GetCell(const Position &pos) const
		;
	const std::vector<Cell> &GetCells() const;
	int GetWidth() const;
	int GetHeight() const;
	std::string GetName() const;
	

	friend std::ostream &operator<<(std::ostream &os, Map &map);

};

char operator>>(Map::Cell cell, char &c);

std::ostream &operator<<(std::ostream &os, Map &map);

#endif 
