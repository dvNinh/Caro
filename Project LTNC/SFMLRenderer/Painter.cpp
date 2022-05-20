#include "Painter.h"

Painter::Painter(sf::RenderWindow* _window) {
	window = _window;
}
void Painter::DrawRectangle(const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Vector2f& _boderThick, const sf::Color& _boderColor, const sf::Color& _fillColor) {
	sf::RectangleShape rec;
	rec.setPosition(_position);
	rec.setSize(_size);
	rec.setOrigin(_size / 2.0f);
	rec.setFillColor(_boderColor);
	window->draw(rec);

	rec.setSize(_size - 2.0f * _boderThick);
	rec.setOrigin(_size / 2.0f - _boderThick);
	rec.setFillColor(_fillColor);
	window->draw(rec);
}
void Painter::DrawText(sf::Font _font, std::string _title, const sf::Vector2f& _position, int _size, const sf::Color& _color, bool _bold) {
	sf::Text text(_title, _font, _size);
	text.setFillColor(_color);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(_position);
	if (_bold) text.setStyle(sf::Text::Bold);
	window->draw(text);
}
void Painter::DrawO(const sf::Vector2f& _pos, float _radius, float _thick, const sf::Color& _boderColor, const sf::Color& _fillColor) {
	sf::CircleShape circle;
	circle.setPosition(_pos);
	circle.setRadius(_radius);
	circle.setOrigin(_radius, _radius);
	circle.setFillColor(_boderColor);
	window->draw(circle);

	_radius -= _thick;
	circle.setRadius(_radius);
	circle.setOrigin(_radius, _radius);
	circle.setFillColor(_fillColor);
	window->draw(circle);
}
void Painter::DrawX(const sf::Vector2f& _pos, const sf::Vector2f& _lineSize, const sf::Color& _color) {
	sf::RectangleShape line;
	line.setSize(_lineSize);
	line.setOrigin(_lineSize / 2.0f);
	line.setPosition(_pos);
	line.setFillColor(_color);

	line.setRotation(45.0f);
	window->draw(line);

	line.setRotation(-45.0f);
	window->draw(line);
}
void Painter::DrawTexture(const sf::Texture& _texture, const sf::Vector2f& _position) {
	sf::Sprite sprite;
	sprite.setPosition(_position);
	sprite.setTexture(_texture);
	window->draw(sprite);
}