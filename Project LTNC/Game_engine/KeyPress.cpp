#include "KeyPress.h"

KeyPress::KeyPress(sf::RenderWindow* _window) {
	window = _window;
	key = KEY::NO_KEY;
}
void KeyPress::UpdateKey() {
	sf::Event evnt;
	window->pollEvent(evnt);
	if (evnt.type == sf::Event::Closed) {
		key = KEY::KEY_EXIT;
	}
	else if (evnt.type == sf::Event::MouseButtonPressed) {
		if (evnt.mouseButton.button == sf::Mouse::Left) {
			key = KEY::MOUSE_LEFT_PRESSED;
		}
	}
	else if (evnt.type == sf::Event::MouseButtonReleased) {
		if (evnt.mouseButton.button == sf::Mouse::Left) {
			key = KEY::MOUSE_LEFT_RELEASED;
		}
	}
	else if (evnt.type == sf::Event::KeyReleased) {
		if (evnt.key.code == sf::Keyboard::Escape) {
			key = KEY::KEY_ESCAPE;
		}
	}
	else key = NO_KEY;
}