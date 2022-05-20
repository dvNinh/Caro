#include "SimpleAI.h"

#include <vector>
#include <cstdlib>
#include <ctime>

SimpleAI::SimpleAI(Map* _map) {
	map = _map;
	playerArray = new int* [4];
	aiArray = new int* [4];
	for (int i = 0; i < 4; i++) {
		playerArray[i] = new int[9];
		aiArray[i] = new int[9];
	}
}
SimpleAI::~SimpleAI() {
	for (int i = 0; i < 4; i++) {
		delete playerArray[i];
		delete aiArray[i];
	}
	delete [] playerArray;
	delete [] aiArray;
}
Coordinate SimpleAI::choosePosition(Coordinate _playerLastPos, Coordinate _aiLastPos) {
	if (_aiLastPos == Coordinate{ -1, -1 }) return RandomPos(_playerLastPos);

	if (CheckHave4LengthInPos(_aiLastPos, aiArray) != Coordinate{ -1, -1 }) return CheckHave4LengthInPos(_aiLastPos, aiArray);
	if (CheckHave4LengthInPos(_playerLastPos, playerArray) != Coordinate{ -1, -1 }) return CheckHave4LengthInPos(_playerLastPos, playerArray);
	if (CheckHave3LengthInPos(_aiLastPos, aiArray) != Coordinate{ -1, -1 }) return CheckHave3LengthInPos(_aiLastPos, aiArray);
	if (CheckHave3LengthInPos(_playerLastPos, playerArray) != Coordinate{ -1, -1 }) return CheckHave3LengthInPos(_playerLastPos, playerArray);
	
	return RandomPos(_playerLastPos);
}
Coordinate SimpleAI::RandomPos( Coordinate _lastPos) {
	std::vector<Coordinate> v;
	if (_lastPos.x >= 1) {
		if (map->GetCell(_lastPos.x - 1, _lastPos.y) == TYPE::EMPTY)
			v.push_back(Coordinate{ _lastPos.x - 1, _lastPos.y });
		if (_lastPos.y >= 1 && map->GetCell(_lastPos.x - 1, _lastPos.y - 1) == TYPE::EMPTY)
			v.push_back(Coordinate{ _lastPos.x - 1, _lastPos.y - 1 });
		if (_lastPos.y < map->GetWidth() - 1 && map->GetCell(_lastPos.x - 1, _lastPos.y + 1) == TYPE::EMPTY)
			v.push_back(Coordinate{ _lastPos.x - 1, _lastPos.y + 1 });
	}
	if (_lastPos.x < map->GetHeight() - 1) {
		if (map->GetCell(_lastPos.x + 1, _lastPos.y) == TYPE::EMPTY)
			v.push_back(Coordinate{ _lastPos.x + 1, _lastPos.y });
		if (_lastPos.y >= 1 && map->GetCell(_lastPos.x + 1, _lastPos.y - 1) == TYPE::EMPTY)
			v.push_back(Coordinate{ _lastPos.x + 1, _lastPos.y - 1 });
		if (_lastPos.y < map->GetWidth() - 1 && map->GetCell(_lastPos.x + 1, _lastPos.y + 1) == TYPE::EMPTY)
			v.push_back(Coordinate{ _lastPos.x + 1, _lastPos.y + 1 });
	}
	if (_lastPos.y >= 1 && map->GetCell(_lastPos.x, _lastPos.y - 1) == TYPE::EMPTY)
		v.push_back(Coordinate{ _lastPos.x, _lastPos.y - 1 });
	if (_lastPos.y < map->GetWidth() - 1 && map->GetCell(_lastPos.x, _lastPos.y + 1) == TYPE::EMPTY)
		v.push_back(Coordinate{ _lastPos.x, _lastPos.y + 1 });

	if (v.size() == 0) {
		int x = rand() % map->GetWidth();
		int y = rand() % map->GetHeight();
		return Coordinate{ x, y };
	}
	else {
		int rd = rand() % v.size();
		return v[rd];
	}
}
int SimpleAI::CheckHave4LengthInArray(int* _arr) {
	for (int i = 0; i < 5; i++) {
		if (_arr[i] != -1 && _arr[i] == _arr[4] && _arr[i + 1] == _arr[4] && _arr[i + 2] == _arr[4] && _arr[i + 3] == _arr[4]) {
			if (_arr[i - 1] == TYPE::EMPTY) return i - 1;
			if (_arr[i + 4] == TYPE::EMPTY) return i + 4;
		}
		if (_arr[i] != -1 && _arr[i] == _arr[4] && _arr[i + 2] == _arr[4] && _arr[i + 3] == _arr[4] && _arr[i + 4] == _arr[4]) {
			if (_arr[i + 1] == TYPE::EMPTY) return i + 1;
		}
		if (_arr[i] != -1 && _arr[i] == _arr[4] && _arr[i + 1] == _arr[4] && _arr[i + 3] == _arr[4] && _arr[i + 4] == _arr[4]) {
			if (_arr[i + 2] == TYPE::EMPTY) return i + 2;
		}
		if (_arr[i] != -1 && _arr[i] == _arr[4] && _arr[i + 1] == _arr[4] && _arr[i + 2] == _arr[4] && _arr[i + 4] == _arr[4]) {
			if (_arr[i + 3] == TYPE::EMPTY) return i + 3;
		}
	}
	return -1;
}
int SimpleAI::CheckHave3LengthInArray(int* _arr) {
	for (int i = 1; i < 5; i++) {
		if (_arr[i] != -1 && _arr[i - 1] == TYPE::EMPTY && _arr[i] == _arr[4] && _arr[i + 1] == _arr[4] && _arr[i + 2] == _arr[4] && _arr[i + 3] == TYPE::EMPTY) {
			if (_arr[i - 2] == TYPE::EMPTY) return i - 1;
			if (_arr[i + 4] == TYPE::EMPTY) return i + 3;
		}
		if (_arr[i] != -1 && _arr[i - 1] == TYPE::EMPTY && _arr[i] == _arr[4] && _arr[i + 1] == TYPE::EMPTY && _arr[i + 2] == _arr[4] && _arr[i + 3] == _arr[4] && _arr[i + 4] == TYPE::EMPTY) {
			return i + 1;
		}
		if (_arr[i] != -1 && _arr[i - 1] == TYPE::EMPTY && _arr[i] == _arr[4] && _arr[i + 1] == _arr[4] && _arr[i + 2] == TYPE::EMPTY && _arr[i + 3] == _arr[4] && _arr[i + 4] == TYPE::EMPTY) {
			return i + 2;
		}
	}
	return -1;
}
Coordinate SimpleAI::CheckHave4LengthInPos(Coordinate _lastPos, int** _arr) {
	UpdateArray(_lastPos, _arr);

	if (CheckHave4LengthInArray(_arr[0]) != -1)
		return _lastPos - Coordinate{ 4, 0 } + Coordinate{ CheckHave4LengthInArray(_arr[0]), 0 };
	if (CheckHave4LengthInArray(_arr[1]) != -1)
		return _lastPos - Coordinate{ 0, 4 } + Coordinate{ 0, CheckHave4LengthInArray(_arr[1]) };
	if (CheckHave4LengthInArray(_arr[2]) != -1)
		return _lastPos - Coordinate{ 4, 4 } + Coordinate{ CheckHave4LengthInArray(_arr[2]), CheckHave4LengthInArray(_arr[2]) };
	if (CheckHave4LengthInArray(_arr[3]) != -1)
		return _lastPos - Coordinate{ 4, -4 } + Coordinate{ CheckHave4LengthInArray(_arr[3]), -CheckHave4LengthInArray(_arr[3]) };

	return Coordinate{ -1, -1 };
}
Coordinate SimpleAI::CheckHave3LengthInPos(Coordinate _lastPos, int** _arr) {
	UpdateArray(_lastPos, _arr);

	if (CheckHave3LengthInArray(_arr[0]) != -1)
		return _lastPos - Coordinate{ 4, 0 } + Coordinate{ CheckHave3LengthInArray(_arr[0]), 0 };
	if (CheckHave3LengthInArray(_arr[1]) != -1)
		return _lastPos - Coordinate{ 0, 4 } + Coordinate{ 0, CheckHave3LengthInArray(_arr[1]) };
	if (CheckHave3LengthInArray(_arr[2]) != -1)
		return _lastPos - Coordinate{ 4, 4 } + Coordinate{ CheckHave3LengthInArray(_arr[2]), CheckHave3LengthInArray(_arr[2]) };
	if (CheckHave3LengthInArray(_arr[3]) != -1)
		return _lastPos - Coordinate{ 4, -4 } + Coordinate{ CheckHave3LengthInArray(_arr[3]), -CheckHave3LengthInArray(_arr[3]) };

	return Coordinate{ -1, -1 };
}
void SimpleAI::UpdateArray(Coordinate _position, int** arr) {
	arr[0][0] = (_position.x >= 4 ? map->GetCell(_position.x - 4, _position.y) : -1);
	arr[0][1] = (_position.x >= 3 ? map->GetCell(_position.x - 3, _position.y) : -1);
	arr[0][2] = (_position.x >= 2 ? map->GetCell(_position.x - 2, _position.y) : -1);
	arr[0][3] = (_position.x >= 1 ? map->GetCell(_position.x - 1, _position.y) : -1);
	arr[0][4] = map->GetCell(_position.x, _position.y);
	arr[0][5] = (_position.x < map->GetHeight() - 1 ? map->GetCell(_position.x + 1, _position.y) : -1);
	arr[0][6] = (_position.x < map->GetHeight() - 2 ? map->GetCell(_position.x + 2, _position.y) : -1);
	arr[0][7] = (_position.x < map->GetHeight() - 3 ? map->GetCell(_position.x + 3, _position.y) : -1);
	arr[0][8] = (_position.x < map->GetHeight() - 4 ? map->GetCell(_position.x + 4, _position.y) : -1);
	
	arr[1][0] = (_position.y >= 4 ? map->GetCell(_position.x, _position.y - 4) : -1);
	arr[1][1] = (_position.y >= 3 ? map->GetCell(_position.x, _position.y - 3) : -1);
	arr[1][2] = (_position.y >= 2 ? map->GetCell(_position.x, _position.y - 2) : -1);
	arr[1][3] = (_position.y >= 1 ? map->GetCell(_position.x, _position.y - 1) : -1);
	arr[1][4] = map->GetCell(_position.x, _position.y);
	arr[1][5] = (_position.y < map->GetWidth() - 1 ? map->GetCell(_position.x, _position.y + 1) : -1);
	arr[1][6] = (_position.y < map->GetWidth() - 2 ? map->GetCell(_position.x, _position.y + 2) : -1);
	arr[1][7] = (_position.y < map->GetWidth() - 3 ? map->GetCell(_position.x, _position.y + 3) : -1);
	arr[1][8] = (_position.y < map->GetWidth() - 4 ? map->GetCell(_position.x, _position.y + 4) : -1);

	arr[2][0] = (_position.x >= 4 && _position.y >= 4 ? map->GetCell(_position.x - 4, _position.y - 4) : -1);
	arr[2][1] = (_position.x >= 3 && _position.y >= 3 ? map->GetCell(_position.x - 3, _position.y - 3) : -1);
	arr[2][2] = (_position.x >= 2 && _position.y >= 2 ? map->GetCell(_position.x - 2, _position.y - 2) : -1);
	arr[2][3] = (_position.x >= 1 && _position.y >= 1 ? map->GetCell(_position.x - 1, _position.y - 1) : -1);
	arr[2][4] = map->GetCell(_position.x, _position.y);
	arr[2][5] = (_position.x < map->GetHeight() - 1 && _position.y < map->GetWidth() - 1 ? map->GetCell(_position.x + 1, _position.y + 1) : -1);
	arr[2][6] = (_position.x < map->GetHeight() - 2 && _position.y < map->GetWidth() - 2 ? map->GetCell(_position.x + 2, _position.y + 2) : -1);
	arr[2][7] = (_position.x < map->GetHeight() - 3 && _position.y < map->GetWidth() - 3 ? map->GetCell(_position.x + 3, _position.y + 3) : -1);
	arr[2][8] = (_position.x < map->GetHeight() - 4 && _position.y < map->GetWidth() - 4 ? map->GetCell(_position.x + 4, _position.y + 4) : -1);

	arr[3][0] = (_position.x >= 4 && _position.y < map->GetWidth() - 4 ? map->GetCell(_position.x - 4, _position.y + 4) : -1);
	arr[3][1] = (_position.x >= 3 && _position.y < map->GetWidth() - 3 ? map->GetCell(_position.x - 3, _position.y + 3) : -1);
	arr[3][2] = (_position.x >= 2 && _position.y < map->GetWidth() - 2 ? map->GetCell(_position.x - 2, _position.y + 2) : -1);
	arr[3][3] = (_position.x >= 1 && _position.y < map->GetWidth() - 1 ? map->GetCell(_position.x - 1, _position.y + 1) : -1);
	arr[3][4] = map->GetCell(_position.x, _position.y);
	arr[3][5] = (_position.x < map->GetHeight() - 1 && _position.y >= 1 ? map->GetCell(_position.x + 1, _position.y - 1) : -1);
	arr[3][6] = (_position.x < map->GetHeight() - 2 && _position.y >= 2 ? map->GetCell(_position.x + 2, _position.y - 2) : -1);
	arr[3][7] = (_position.x < map->GetHeight() - 3 && _position.y >= 3 ? map->GetCell(_position.x + 3, _position.y - 3) : -1);
	arr[3][8] = (_position.x < map->GetHeight() - 4 && _position.y >= 4 ? map->GetCell(_position.x + 4, _position.y - 4) : -1);
}