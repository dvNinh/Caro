#pragma once

#include "Coordinate.h"

enum TYPE {
	EMPTY,
	X,
	O,
};

class Map {
private:
	int width, height;
	int** map;
public:
	Map(int _width, int _height);
	~Map();
	void SetCell(int _x, int _y, int _c);
	char GetCell(int _x, int _y);
	int GetWidth();
	int GetHeight();
	void Clear();
};