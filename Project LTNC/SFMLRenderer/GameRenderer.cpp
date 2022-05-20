#include "GameRenderer.h"

GameRenderer::GameRenderer(sf::RenderWindow* _window) {
	window = _window;
	painter = new Painter(window);
}
GameRenderer::~GameRenderer() {
	delete painter;
}
void GameRenderer::RenderMap(Map* _map) {
	int mapWidth = _map->GetWidth();
	int mapHeight = _map->GetHeight();
	
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			sf::Vector2f position((j + 0.5f) * BOX_LENGTH, (i + 0.5f) * BOX_LENGTH);

			if (_map->GetCell(i, j) == TYPE::EMPTY) {
				painter->DrawRectangle(position, sf::Vector2f(BOX_LENGTH, BOX_LENGTH), sf::Vector2f(BORDER_THICK, BORDER_THICK));
			}
			else if (_map->GetCell(i, j) == TYPE::X) {
				painter->DrawRectangle(position, sf::Vector2f(BOX_LENGTH, BOX_LENGTH), sf::Vector2f(BORDER_THICK, BORDER_THICK));
				sf::Vector2f size((BOX_LENGTH - 4 * BORDER_THICK) * sqrt(2) - 2 * BORDER_THICK, 2 * BORDER_THICK);
				painter->DrawX(position, size, sf::Color::Red);
			}
			else if (_map->GetCell(i, j) == TYPE::O) {
				painter->DrawRectangle(position, sf::Vector2f(BOX_LENGTH, BOX_LENGTH), sf::Vector2f(BORDER_THICK, BORDER_THICK));
				painter->DrawO(position, BOX_LENGTH / 2.0f - 2.0f * BORDER_THICK, 2 * BORDER_THICK, sf::Color::Blue);
			}
		}
	}
}