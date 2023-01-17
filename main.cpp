#include "field_logic.hpp"
#include "field_rendering.hpp"

RenderWindow window(VideoMode(800, 800), "Corners", Style::Close); // main window of the game

void preparation_phase(Texture& start_menu, Texture& white_win,
                       Texture& black_win, Texture& tie)
{
    window.setFramerateLimit(10);
    window.setPosition(Vector2i((1920-800)/2, (1080-800)/2)); // screen center

    // start menu and victory picture
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
        if (event.type == Event::Closed) {
            window.close();
            break;
        }
        if (event.key.code == Keyboard::Enter)
            break;
    }
}

int main()
{
    Texture start_menu, white_win, black_win, tie;
    preparation_phase(start_menu, white_win, black_win, tie);

	// create the chessboard
	FieldLogic field_logic;
    FieldRendering field_rendering(field_logic);

	// main game cycle, is executed while the window is open
	while (window.isOpen())
	{
		// reads the coordinates of the pressed key on the mouse
		Vector2i pos = Mouse::getPosition(window);
		int col = pos.x / field_logic.get_width();
		int str = pos.y / field_logic.get_width();

		// the queue of events in the loop is processed
		Event inner_event{};
		while (window.pollEvent(inner_event))
		{
			// clicked on the cross?
			if (inner_event.type == Event::Closed)
                window.close();

			// was the mouse button pressed?
			if (inner_event.type == Event::MouseButtonPressed)
                field_logic.move(inner_event, str, col);
		}

		if      (field_logic.get_winner() == -1)  continue;
		else if (field_logic.get_winner() == 0 )  window.draw(Sprite(tie));
		else if (field_logic.get_winner() == 1 )  window.draw(Sprite(white_win));
		else                                window.draw(Sprite(black_win));

		window.display();
        while (window.pollEvent(inner_event)) {
            if (inner_event.type == Event::Closed)
                window.close();
        }
	}

	return 0;
}