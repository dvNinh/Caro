#pragma once

#include "SFML/Graphics.hpp"

class Font {
private:
	sf::Font ARIAL_FONT;
public:
	Font() {
		ARIAL_FONT.loadFromFile("./assets/font/arial.ttf");
	}
	sf::Font GetArialFont() {
		return ARIAL_FONT;
	}
};