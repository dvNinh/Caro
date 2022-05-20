#include "Button.h"

Button::Button() {
	type = 0;
	position = sf::Vector2f(0.0f, 0.0f);
	size = sf::Vector2f(100.0f, 100.0f);
	borderThick = sf::Vector2f(0.0f, 0.0f);
	borderColor = sf::Color::Black;
	fillColor = sf::Color::White;
	textColor = sf::Color::Black;
	title = "Title";
	textSize = 20;
}
void Button::Draw(sf::RenderWindow* _window, sf::Font _font) {
	Painter* painter = new Painter(_window);
	painter->DrawRectangle(position, size, borderThick, borderColor, fillColor);
	painter->DrawText(_font, title, position, textSize, textColor, 1);
	delete painter;
}
bool Button::IsMouseOn(sf::Vector2i& _mousePos) {
	if (_mousePos.x < position.x - size.x / 2.0f) return false;
	if (_mousePos.x > position.x + size.x / 2.0f) return false;
	if (_mousePos.y < position.y - size.y / 2.0f) return false;
	if (_mousePos.y > position.y + size.y / 2.0f) return false;
	return true;
}
void Button::Blur() {
	SetBorderColor(sf::Color(50, 50, 50, 255));
	SetFillColor(sf::Color(205, 205, 205, 255));
	SetTextColor(sf::Color(50, 50, 50, 255));
}