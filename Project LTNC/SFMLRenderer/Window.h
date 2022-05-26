#pragma once

#include "Button.h"

#include "GameRenderer.h"
#include "../Game_engine/GameEngine.h"
#include "../FileLoad/Font.h"
#include "../FileLoad/Texture.h"

const int BOARD_WIDTH = 25;
const int BOARD_HEIGHT = 21;

enum MODE {
	MODE_MENU,
	MODE_PVE,
	MODE_PVP,
	MODE_EXIT,
};

class Window {
private:
	sf::RenderWindow* window;
	const int width, height;
	int mode;

	Painter* painter;
	Audio music;
	Font font;
	Texture texture;

	bool isMusicOn;
public:
	Window(int _width = 500, int _height = 500, std::string _title = "Demo game");
	~Window();

	int GetMode() { return mode; }
	void SetMode(int _mode) { mode = _mode; }

	void Run();
	void LoadMenu();
	void LoadGame(int _gameMode);
	void RenderGameInfo(GameEngine* _gameEngine);
	void RenderGameResult(GameEngine* _gameEngine, int _key);
	void RenderGamePause(GameEngine* _gameEngine, int _key);

	void ActiveButton(GameEngine* _gameEngine, int _key, Button _buttonList[], int _numButton);
};