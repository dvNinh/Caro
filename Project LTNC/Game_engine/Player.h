#pragma once

#include <string>
#include "../CommonClass/Coordinate.h"

class Player {
private:
	std::string name;
	char type;
	int score;
	bool onTurn;
	bool isComputer;
	Coordinate lastPos;
public:
	Player(bool _isComputer) {
		isComputer = _isComputer;
		name = "";
		type = 0;
		score = 0;
		onTurn = false;
		lastPos = { -1, -1 };
	}

	Coordinate GetLastPosition() { return lastPos; }
	void SetLastPosition(Coordinate _pos) { lastPos = _pos; }
	bool GetTurn() { return onTurn; }
	void SetTurn(bool _b) { onTurn = _b; }
	int GetScore() { return score; }
	void SetScore(int _score) { score = _score; }
	int GetType() { return type; }
	void SetType(int _type) { type = _type; }
	std::string GetName() { return name; }
	void SetName(std::string _name) { name = _name; }
	bool IsComputer() { return isComputer; }
};