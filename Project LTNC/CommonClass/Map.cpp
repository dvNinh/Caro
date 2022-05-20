#include "Map.h"

Map::Map(int _width, int _height) : width(_width), height(_height) {
	this->map = new int* [height];
	for (int i = 0; i < height; i++) {
		this->map[i] = new int[width];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			this->map[i][j] = TYPE::EMPTY;
		}
	}
}
Map::~Map() {
	for (int i = 0; i < this->height; i++) {
		delete[] this->map[i];
	}
	delete[] this->map;
}
void Map::SetCell(int _x, int _y, int _c) {
	this->map[_x][_y] = _c;
}
char Map::GetCell(int _x, int _y) {
	return this->map[_x][_y];
}
int Map::GetWidth() {
	return this->width;
}
int Map::GetHeight() {
	return this->height;
}
void Map::Clear() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			this->map[i][j] = TYPE::EMPTY;
		}
	}
}