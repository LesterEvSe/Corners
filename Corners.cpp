#include "Field.hpp"

using namespace sf;
RenderWindow window(VideoMode(800, 800), "Corners"); // main window of the game

int main()
{
	// start menu and victory picture 
	Texture start_menu, white_win, black_win, tie;
	start_menu.loadFromFile("../images/start_menu.png");
	white_win.loadFromFile("../images/white_win.png");
	black_win.loadFromFile("../images/black_win.jpg");
	tie.loadFromFile("../images/tie.jpg");

	window.draw(Sprite(start_menu));
	window.display();
	Event event{};

	while (true)
	{
		window.pollEvent(event);
		if (event.type == Event::Closed) { window.close(); break; }
		if (event.key.code == Keyboard::Enter)	break;
	}

	// create the chessboard
	Field field;

	// main game cycle, is executed while the window is open
	while (window.isOpen())
	{
		// reads the coordinates of the pressed key on the mouse
		Vector2i pos = Mouse::getPosition(window);
		int col = pos.x / field.get_width();
		int str = pos.y / field.get_width();

		// the queue of events in the loop is processed
		Event inner_event{};
		while (window.pollEvent(inner_event))
		{
			// clicked on the cross?
			if (inner_event.type == Event::Closed) window.close();

			// was the mouse button pressed?
			if (inner_event.type == Event::MouseButtonPressed) field.move(inner_event, str, col);
		}

		if (field.get_winner() == -1) continue;
		else if (field.get_winner() == 0) window.draw(Sprite(tie));
		else if (field.get_winner() == 1) window.draw(Sprite(white_win));
		else window.draw(Sprite(black_win));

		window.display();
        while (window.pollEvent(inner_event)) { if (inner_event.type == Event::Closed) window.close(); }
	}

	return 0;
}