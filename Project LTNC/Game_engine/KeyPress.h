#pragma once

#include "SFML/Graphics.hpp"

enum KEY {
	NO_KEY,
	MOUSE_LEFT_PRESSED,
	MOUSE_LEFT_RELEASED,
	KEY_ESCAPE,
	KEY_EXIT,
};

class KeyPress {
private:
	sf::RenderWindow* window;
	int key;
public:
	KeyPress(sf::RenderWindow* _window);
	void UpdateKey();
	int GetKey() { return key; }
};