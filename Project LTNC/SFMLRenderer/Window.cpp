#include "Window.h"

Window::Window(int _width, int _height, std::string _title) : width(_width), height(_height) {
	window = new sf::RenderWindow(sf::VideoMode(width, height), _title, sf::Style::Close);
	painter = new Painter(window);
	mode = MODE::MODE_MENU;
	isMusicOn = true;
}
Window::~Window() {
	delete painter;
	delete window;
}
void Window::Run() {
	music.PlaySoundtrack();
	while (mode != MODE::MODE_EXIT) {
		if (mode == MODE::MODE_MENU) LoadMenu();
		else if (mode == MODE::MODE_PVE) LoadGame(1);
		else if (mode == MODE::MODE_PVP) LoadGame(2);
	}
}
void Window::LoadMenu() {
	painter->DrawTexture(texture.GetMenuTexture());

	const int numButton = 4;
	Button buttonList[numButton];
	buttonList[0].SetType(BUTTON::BUTTON_PVE);
	buttonList[1].SetType(BUTTON::BUTTON_PVP);
	buttonList[2].SetType(BUTTON::BUTTON_MUSIC);
	buttonList[3].SetType(BUTTON::BUTTON_EXIT);

	buttonList[0].SetString("vs Computer");
	buttonList[1].SetString("2 Player");
	std::string s = isMusicOn ? "On" : "Off";
	buttonList[2].SetString("Music: " + s);
	buttonList[3].SetString("Exit");

	for (int i = 0; i < numButton; i++) {
		buttonList[i].SetPosition(sf::Vector2f(335.0f, 102.0f + i * 156.0f));
		buttonList[i].SetSize(sf::Vector2f(450.0f, 110.0f));
		buttonList[i].SetThick(sf::Vector2f(0.0f, 0.0f));
		buttonList[i].SetFillColor(sf::Color(80, 175, 100, 255));
		buttonList[i].SetTextSize(50);
	}

	KeyPress key(window);
	key.UpdateKey();
	ActiveButton(nullptr, key.GetKey(), buttonList, numButton);
	window->display();
}
void Window::LoadGame(int _gameMode) {
	GameRenderer* renderer = new GameRenderer(window);
	GameEngine* gameEngine = new GameEngine(BOARD_WIDTH, BOARD_HEIGHT, _gameMode);
	KeyPress key(window);

	// Game loop
	while (gameEngine->GetStatus() != STATUS::EXIT && gameEngine->GetStatus() != STATUS::RETURN) {
		painter->DrawTexture(texture.GetBackgroundTexture());
		renderer->RenderMap(gameEngine->GetMap());
		RenderGameInfo(gameEngine);

		key.UpdateKey();
		if (gameEngine->GetStatus() == STATUS::RUNNING) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			gameEngine->SetMousePos(mousePos.y / BOX_LENGTH, mousePos.x / BOX_LENGTH);
			gameEngine->Step(key.GetKey());
		}
		else if (gameEngine->GetStatus() == STATUS::PAUSE) {
			RenderGamePause(gameEngine, key.GetKey());
		}
		else if (gameEngine->GetStatus() == STATUS::RESULT) {
			RenderGameResult(gameEngine, key.GetKey());
		}
		else if (gameEngine->GetStatus() == STATUS::RESTART) {
			gameEngine->Restart();
		}
		window->display();
	}

	if (gameEngine->GetStatus() == STATUS::RETURN) mode = MODE::MODE_MENU;
	if (gameEngine->GetStatus() == STATUS::EXIT) mode = MODE::MODE_EXIT;
}
void Window::RenderGameResult(GameEngine* _gameEngine, int _key) {
	sf::Vector2f pos(width / 2.0f, height / 2.0f);
	sf::Vector2f size = sf::Vector2f(600.0f, 300.0f);
	painter->DrawRectangle(pos, size, sf::Vector2f(0.0f, 0.0f), sf::Color::Black, sf::Color(100, 200, 100, 255));

	std::string resultStr = _gameEngine->GetWinner()->GetName() + " win";
	painter->DrawText(font.GetArialFont(), resultStr, pos - sf::Vector2f(0.0f, size.y / 5.0f), 50);

	const int numButton = 2;
	Button buttonList[numButton];
	buttonList[0].SetType(BUTTON::BUTTON_RESTART);
	buttonList[1].SetType(BUTTON::BUTTON_MENU);

	buttonList[0].SetString("Play Again");
	buttonList[1].SetString("Main Menu");

	buttonList[0].SetPosition(pos + sf::Vector2f(-size.x / 5.0f, size.y / 5.0f));
	buttonList[1].SetPosition(pos + sf::Vector2f(size.x / 5.0f, size.y / 5.0f));

	sf::Vector2f buttonSize(200.0f, 50.0f);
	for (int i = 0; i < numButton; i++) {
		buttonList[i].SetSize(buttonSize);
		buttonList[i].SetThick(sf::Vector2f(10.0f, 4.0f));
	}

	ActiveButton(_gameEngine, _key, buttonList, numButton);
}
void Window::RenderGamePause(GameEngine* _gameEngine, int _key) {
	sf::Vector2f pos(window->getSize().x / 2.0f, window->getSize().y / 2.0f);
	sf::Vector2f size(350.0f, 450.0f);
	painter->DrawRectangle(pos, size, sf::Vector2f(0.0f, 0.0f), sf::Color::Black, sf::Color(100, 100, 100, 255));

	std::string pauseStr = "PAUSE";
	int textSize = 50;
	painter->DrawText(font.GetArialFont(), pauseStr, pos - sf::Vector2f(0.0f, size.y / 2.0f - textSize), textSize, sf::Color::Black, 1);

	const int numButton = 4;
	Button buttonList[numButton];
	buttonList[0].SetType(BUTTON::BUTTON_RESUME);
	buttonList[1].SetType(BUTTON::BUTTON_RESTART);
	buttonList[2].SetType(BUTTON::BUTTON_MUSIC);
	buttonList[3].SetType(BUTTON::BUTTON_MENU);

	buttonList[0].SetString("Resume");
	buttonList[1].SetString("Restart");
	std::string s = isMusicOn ? "On" : "Off";
	buttonList[2].SetString("Music: " + s);
	buttonList[3].SetString("Main Menu");

	sf::Vector2f buttonSize = sf::Vector2f(200.0f, 50.0f);
	for (int i = 0; i < numButton; i++) {
		buttonList[i].SetSize(buttonSize);
		buttonList[i].SetThick(sf::Vector2f(10.0f, 4.0f));
		buttonList[i].SetPosition(pos + sf::Vector2f(0.0f, 65.0f * i - 25.0f));
	}

	ActiveButton(_gameEngine, _key, buttonList, numButton);
	if (_key == KEY::KEY_ESCAPE) {
		_gameEngine->SetStatus(STATUS::RUNNING);
	}
}
void Window::RenderGameInfo(GameEngine* _gameEngine) {
	sf::Vector2f size1(450.0f, 350.0f);
	sf::Vector2f pos1(window->getSize().x - size1.x / 2.0f, size1.y / 2.0f);
	painter->DrawRectangle(pos1, size1, sf::Vector2f(BORDER_THICK, BORDER_THICK));

	int textSize = 28;
	sf::Vector2f titlePos = pos1 - sf::Vector2f(0.0f, size1.y / 2.0f - textSize * 1.5f);
	if (_gameEngine->GetGameMode() == 1)
		painter->DrawText(font.GetArialFont(), "VS COMPUTER", titlePos, textSize, sf::Color::Black, 1);
	else if (_gameEngine->GetGameMode() == 2)
		painter->DrawText(font.GetArialFont(), "TWO PLAYER", titlePos, textSize, sf::Color::Black, 1);

	painter->DrawText(font.GetArialFont(), "SCORE", pos1 - sf::Vector2f(150.0f, 50.0f), textSize);
	painter->DrawText(font.GetArialFont(), "X:  ", pos1 - sf::Vector2f(150.0f, 0.0f), textSize, sf::Color::Red);
	std::string p1Score = std::to_string(_gameEngine->Player1()->GetScore());
	painter->DrawText(font.GetArialFont(), p1Score, pos1 - sf::Vector2f(125.0f, 0.0f), textSize);

	painter->DrawText(font.GetArialFont(), "O:  ", pos1 - sf::Vector2f(0.0f, 0.0f), textSize, sf::Color::Blue);
	std::string p2Score = std::to_string(_gameEngine->Player2()->GetScore());
	painter->DrawText(font.GetArialFont(), p2Score, pos1 - sf::Vector2f(-25.0f, 0.0f), textSize);

	std::string turn = "";
	sf::Color turnColor;
	if (_gameEngine->Player1()->GetTurn()) { 
		turn = "X turn";
		turnColor = sf::Color::Red;
	}
	else if (_gameEngine->Player2()->GetTurn()) {
		turn = "O turn";
		turnColor = sf::Color::Blue;
	}
	painter->DrawText(font.GetArialFont(), turn, pos1 - sf::Vector2f(157.0f, -75.0f), textSize, turnColor);

	sf::Vector2f size2(450.0f, 242.0f);
	sf::Vector2f pos2(window->getSize().x - size2.x / 2.0f, window->getSize().y - size2.y / 2.0f);
	painter->DrawRectangle(pos2, size2, sf::Vector2f(BORDER_THICK, BORDER_THICK));
	painter->DrawTexture(texture.GetRuleTexture(), pos2 - size2 / 2.0f);
}
void Window::ActiveButton(GameEngine* _gameEngine, int _key, Button _buttonList[], int _numButton) {
	if (_key == KEY::KEY_EXIT) {
		if (_gameEngine != nullptr) _gameEngine->SetStatus(STATUS::EXIT);
		mode = MODE::MODE_EXIT;
	}
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	for (int i = 0; i < _numButton; i++) {
		if (_buttonList[i].IsMouseOn(mousePos)) {
			_buttonList[i].Blur();
			if (_key == KEY::MOUSE_LEFT_RELEASED) {
				switch (_buttonList[i].GetType()) {
				case BUTTON::BUTTON_PVE:
					SetMode(MODE_PVE);
					break;
				case BUTTON::BUTTON_PVP:
					SetMode(MODE_PVP);
					break;
				case BUTTON::BUTTON_EXIT:
					SetMode(MODE_EXIT);
					break;
				case BUTTON::BUTTON_MENU:
					if (_gameEngine != nullptr) _gameEngine->SetStatus(STATUS::RETURN);
					break;
				case BUTTON::BUTTON_RESTART:
					if (_gameEngine != nullptr) _gameEngine->SetStatus(STATUS::RESTART);
					break;
				case BUTTON::BUTTON_RESUME:
					if (_gameEngine != nullptr) _gameEngine->SetStatus(STATUS::RUNNING);
					break;
				case BUTTON::BUTTON_MUSIC:
					if (isMusicOn) {
						music.StopSoundtrack();
						isMusicOn = false;
					}
					else {
						music.PlaySoundtrack();
						isMusicOn = true;
					}
					break;
				}
			}
		}
		_buttonList[i].Draw(window, font.GetArialFont());
	}
}