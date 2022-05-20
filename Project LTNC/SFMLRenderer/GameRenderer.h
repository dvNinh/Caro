#pragma once

#include "../CommonClass/Map.h"
#include "Painter.h"

const int BOX_LENGTH = 32;
const int BORDER_THICK = 2;

class GameRenderer {
private:
	sf::RenderWindow* window;
	Painter* painter;
public:
	GameRenderer(sf::RenderWindow* _window);
	~GameRenderer();

	void RenderMap(Map* _map);
};