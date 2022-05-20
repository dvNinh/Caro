#include "GameEngine.h"

#include <math.h>

GameEngine::GameEngine(int _boardWidth, int _boardHeight, int _gameMode) {
	gameMode = _gameMode;

	width = _boardWidth;
	height = _boardHeight;
	map = new Map(width, height);
	status = STATUS::RUNNING;

	if (_gameMode == 1) {
		p1 = new Player(false);
		p1->SetName("Player");
		p2 = new Player(true);
		p2->SetName("Computer");
	}
	else if (_gameMode == 2) {
		p1 = new Player(false);
		p1->SetName("Player 1");
		p2 = new Player(false);
		p2->SetName("Player 2");
	}
	p1->SetType(TYPE::X);
	p2->SetType(TYPE::O);

	p1->SetTurn(true);
	winner = p1;

	mousePosition = Coordinate{ 0, 0 };
}
GameEngine::~GameEngine() {
	delete winner;
	delete p1;
	delete p2;
	delete map;
}
void GameEngine::Step(int _key) {
	if (p1->GetTurn()) {
		if (_key == KEY::MOUSE_LEFT_RELEASED) {
			if (ValidPos(mousePosition.x, mousePosition.y)) {
				p1->SetLastPosition(mousePosition);
				PlayerTurn(p1, p2);
			}
		}
	}
	else if (p2->GetTurn()) {
		if (p2->IsComputer()) {
			SimpleAI ai(map);
			Coordinate aiChoice;
			do {
				aiChoice = ai.choosePosition(p1->GetLastPosition(), p2->GetLastPosition());
			} while (!ValidPos(aiChoice.x, aiChoice.y));
			p2->SetLastPosition(aiChoice);
			PlayerTurn(p2, p1);
		}
		else {
			if (_key == KEY::MOUSE_LEFT_RELEASED) {
				if (ValidPos(mousePosition.x, mousePosition.y)) {
					p2->SetLastPosition(mousePosition);
					PlayerTurn(p2, p1);
				}
			}
		}
	}

	if (_key == KEY::KEY_ESCAPE) SetStatus(STATUS::PAUSE);
	if (_key == KEY::KEY_EXIT) SetStatus(STATUS::EXIT);
}
void GameEngine::PlayerTurn(Player* _player, Player* _other) {
	map->SetCell(_player->GetLastPosition().x, _player->GetLastPosition().y, _player->GetType());
	sound.PlaySwitchSound();

	if (CheckWin(_player->GetLastPosition())) {
		winner = _player;
		winner->SetScore(winner->GetScore() + 1);
		status = STATUS::RESULT;
		sound.PlayResultSound();
	}
	else {
		_player->SetTurn(false);
		_other->SetTurn(true);
	}
}
bool GameEngine::ValidPos(int _x, int _y) {
	if (_x < 0 || height - 1 < _x) return false;
	if (_y < 0 || width - 1 < _y) return false;
	if (map->GetCell(_x, _y) != TYPE::EMPTY) return false;
	return true;
}
bool GameEngine::CheckWin(Coordinate _lastPos) {
	int arr1[9] = {
		(_lastPos.x >= 4 ? map->GetCell(_lastPos.x - 4, _lastPos.y) : -1),
		(_lastPos.x >= 3 ? map->GetCell(_lastPos.x - 3, _lastPos.y) : -1),
		(_lastPos.x >= 2 ? map->GetCell(_lastPos.x - 2, _lastPos.y) : -1),
		(_lastPos.x >= 1 ? map->GetCell(_lastPos.x - 1, _lastPos.y) : -1),
		map->GetCell(_lastPos.x, _lastPos.y),
		(_lastPos.x < height - 1 ? map->GetCell(_lastPos.x + 1, _lastPos.y) : -1),
		(_lastPos.x < height - 2 ? map->GetCell(_lastPos.x + 2, _lastPos.y) : -1),
		(_lastPos.x < height - 3 ? map->GetCell(_lastPos.x + 3, _lastPos.y) : -1),
		(_lastPos.x < height - 4 ? map->GetCell(_lastPos.x + 4, _lastPos.y) : -1),
	};
	if (CheckHave5Length(arr1))  return true;

	int arr2[9] = {
		(_lastPos.y >= 4 ? map->GetCell(_lastPos.x, _lastPos.y - 4) : -1),
		(_lastPos.y >= 3 ? map->GetCell(_lastPos.x, _lastPos.y - 3) : -1),
		(_lastPos.y >= 2 ? map->GetCell(_lastPos.x, _lastPos.y - 2) : -1),
		(_lastPos.y >= 1 ? map->GetCell(_lastPos.x, _lastPos.y - 1) : -1),
		map->GetCell(_lastPos.x, _lastPos.y),
		(_lastPos.y < width - 1 ? map->GetCell(_lastPos.x, _lastPos.y + 1) : -1),
		(_lastPos.y < width - 2 ? map->GetCell(_lastPos.x, _lastPos.y + 2) : -1),
		(_lastPos.y < width - 3 ? map->GetCell(_lastPos.x, _lastPos.y + 3) : -1),
		(_lastPos.y < width - 4 ? map->GetCell(_lastPos.x, _lastPos.y + 4) : -1),
	};
	if (CheckHave5Length(arr2)) return true;

	int arr3[9] = {
		(_lastPos.x >= 4 && _lastPos.y >= 4 ? map->GetCell(_lastPos.x - 4, _lastPos.y - 4) : -1),
		(_lastPos.x >= 3 && _lastPos.y >= 3 ? map->GetCell(_lastPos.x - 3, _lastPos.y - 3) : -1),
		(_lastPos.x >= 2 && _lastPos.y >= 2 ? map->GetCell(_lastPos.x - 2, _lastPos.y - 2) : -1),
		(_lastPos.x >= 1 && _lastPos.y >= 1 ? map->GetCell(_lastPos.x - 1, _lastPos.y - 1) : -1),
		map->GetCell(_lastPos.x, _lastPos.y),
		(_lastPos.x < height - 1 && _lastPos.y < width - 1 ? map->GetCell(_lastPos.x + 1, _lastPos.y + 1) : -1),
		(_lastPos.x < height - 2 && _lastPos.y < width - 2 ? map->GetCell(_lastPos.x + 2, _lastPos.y + 2) : -1),
		(_lastPos.x < height - 3 && _lastPos.y < width - 3 ? map->GetCell(_lastPos.x + 3, _lastPos.y + 3) : -1),
		(_lastPos.x < height - 4 && _lastPos.y < width - 4 ? map->GetCell(_lastPos.x + 4, _lastPos.y + 4) : -1),
	};
	if (CheckHave5Length(arr3)) return true;

	int arr4[9] = {
		(_lastPos.x >= 4 && _lastPos.y < width - 4 ? map->GetCell(_lastPos.x - 4, _lastPos.y + 4) : -1),
		(_lastPos.x >= 3 && _lastPos.y < width - 3 ? map->GetCell(_lastPos.x - 3, _lastPos.y + 3) : -1),
		(_lastPos.x >= 2 && _lastPos.y < width - 2 ? map->GetCell(_lastPos.x - 2, _lastPos.y + 2) : -1),
		(_lastPos.x >= 1 && _lastPos.y < width - 1 ? map->GetCell(_lastPos.x - 1, _lastPos.y + 1) : -1),
		map->GetCell(_lastPos.x, _lastPos.y),
		(_lastPos.x < height - 1 && _lastPos.y >= 1 ? map->GetCell(_lastPos.x + 1, _lastPos.y - 1) : -1),
		(_lastPos.x < height - 2 && _lastPos.y >= 2 ? map->GetCell(_lastPos.x + 2, _lastPos.y - 2) : -1),
		(_lastPos.x < height - 3 && _lastPos.y >= 3 ? map->GetCell(_lastPos.x + 3, _lastPos.y - 3) : -1),
		(_lastPos.x < height - 4 && _lastPos.y >= 4 ? map->GetCell(_lastPos.x + 4, _lastPos.y - 4) : -1),
	};
	if (CheckHave5Length(arr4)) return true;

	return false;
}
bool GameEngine::CheckHave5Length(int _arr[]) {
	for (int i = 0; i < 5; i++) {
		if (_arr[i] != -1 && _arr[i] == _arr[4] && _arr[i + 1] == _arr[4] && _arr[i + 2] == _arr[4] && _arr[i + 3] == _arr[4] && _arr[i + 4] == _arr[4]) {
			return true;
		}
	}
	return false;
}
void GameEngine::Restart() {
	srand(time(0));
	map->Clear();

	p1->SetTurn(true);
	p2->SetTurn(false);
	winner = p1;
	p1->SetLastPosition(Coordinate{ -1, -1 });
	p2->SetLastPosition(Coordinate{ -1, -1 });

	status = STATUS::RUNNING;
}