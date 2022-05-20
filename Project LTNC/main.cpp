#include "SFMLRenderer/Window.h"

const int WINDOW_WIDTH = 1325;
const int WINDOW_HEIGHT = 672;

int main() {
	srand(time(0));
	Window* window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Caro");
	window->Run();
	delete window;
	return 0;
}