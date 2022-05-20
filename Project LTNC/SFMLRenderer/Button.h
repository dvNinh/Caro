#pragma once

#include "Painter.h"

enum BUTTON {
	BUTTON_PVE,
	BUTTON_PVP,
	BUTTON_EXIT,
	BUTTON_MUSIC,

	BUTTON_RESUME,
	BUTTON_RESTART,
	BUTTON_MENU,
};

class Button {
private:
	int type;
	sf::Vector2f position, size, borderThick;
	sf::Color borderColor, fillColor, textColor;
	std::string title;
	int textSize;
public:
	Button();
	~Button() {}
	void Draw(sf::RenderWindow* _window, sf::Font _font);
	void Blur();
	bool IsMouseOn(sf::Vector2i& _mousePos);

	void SetType(int _mode) { type = _mode; }
	int GetType() { return type; }

	void SetPosition(sf::Vector2f _pos) { position = _pos; }
	void SetSize(sf::Vector2f _size) { size = _size; }
	void SetThick(sf::Vector2f _thick) { borderThick = _thick; }
	void SetBorderColor(sf::Color _color) { borderColor = _color; }
	void SetFillColor(sf::Color _color) { fillColor = _color; }
	void SetTextColor(sf::Color _color) { textColor = _color; }
	void SetString(std::string _s) { title = _s; }
	void SetTextSize(int _textSize) { textSize = _textSize; }
};