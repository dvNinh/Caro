#pragma once

#include "SFML/Graphics.hpp"

class Texture {
private:
	sf::Texture MENU_TEXTURE;
	sf::Texture BACKGROUND_TEXTURE;
	sf::Texture RULE_TEXTURE;
public:
	Texture() {
		MENU_TEXTURE.loadFromFile("./assets/img/menu.png");
		BACKGROUND_TEXTURE.loadFromFile("./assets/img/bg.png");
		RULE_TEXTURE.loadFromFile("./assets/img/Rule.png");
	}
	sf::Texture GetMenuTexture() {
		return MENU_TEXTURE;
	}
	sf::Texture GetBackgroundTexture() {
		return BACKGROUND_TEXTURE;
	}
	sf::Texture GetRuleTexture() {
		return RULE_TEXTURE;
	}
};