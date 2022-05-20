#pragma once

#include "SFML/Graphics.hpp"

class Painter {
private:
	sf::RenderWindow* window;
public:
	Painter(sf::RenderWindow* _window);
	void DrawRectangle(const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Vector2f& _boderThick, const sf::Color& _boderColor = sf::Color::Black, const sf::Color& _fillColor = sf::Color::White);
	void DrawText(sf::Font _font, std::string _title, const sf::Vector2f& _position, int _size, const sf::Color& _color = sf::Color::Black, bool _bold = false);
	void DrawO(const sf::Vector2f& _pos, float _radius, float _thick, const sf::Color& _boderColor = sf::Color::Black, const sf::Color& _fillColor = sf::Color::White);
	void DrawX(const sf::Vector2f& _pos, const sf::Vector2f& _lineSize, const sf::Color& _color = sf::Color::Black);
	void DrawTexture(const sf::Texture& _texture, const sf::Vector2f& _position = sf::Vector2f(0.0f, 0.0f));
};