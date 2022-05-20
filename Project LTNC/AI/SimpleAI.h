#pragma once

#include "../CommonClass/Map.h"

class SimpleAI {
private:
	Map* map;
	int** playerArray;
	int** aiArray;
public:
	SimpleAI(Map* _map);
	~SimpleAI();
	Coordinate choosePosition(Coordinate _playerLastPos, Coordinate _aiLastPos);
	Coordinate RandomPos(Coordinate _lastPos);
	int CheckHave4LengthInArray(int* _arr);
	int CheckHave3LengthInArray(int* _arr);
	Coordinate CheckHave4LengthInPos(Coordinate _lastPos, int** arr);
	Coordinate CheckHave3LengthInPos(Coordinate _lastPos, int** arr);
	void UpdateArray(Coordinate _position, int** arr);
};