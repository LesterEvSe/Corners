#include "Field.hpp"

using namespace sf;

extern RenderWindow window;
Texture white, black;

void Field::choose_cell(const Event& event, int str, int col)
{
	if (static_cast<int>(event.key.code) == Mouse::Left && m_logic[str][col] == m_player_move)
	{
		m_board[str][col].setFillColor(Color::Green);
		m_start = std::make_pair(str, col);
		m_move = true;
	}
	rendering();
}
void Field::cancel()
{
	if (m_start.first != -1)
	{
		if ((m_start.first + m_start.second) % 2) m_board[m_start.first][m_start.second].setFillColor(Color::Black);
		else m_board[m_start.first][m_start.second].setFillColor(Color::White);
		m_start.first = -1;
	}
	rendering();
}
void Field::next_move()
{
	// You can walk only when you make a move
	if (m_move_made)
	{
		cancel();
		m_player_move = (m_player_move == 1) ? 2 : 1;
		m_move_made = false;
		m_move = false;
		check_winner();
	}
	rendering();
}
void Field::check_winner()
{
	// If now the move of player 1 (white) starts, then check if the game is not over
	if (m_player_move == 1)
	{
		bool white_win = true;
		bool black_win = true;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
			{
				if (m_logic[i][j] != Checkers::BLACK) black_win = false;
				if (m_logic[i + 5][j + 5] != Checkers::WHITE) white_win = false;

				if (!black_win && !white_win) { m_winner = -1; return; }
			}
		if (black_win && white_win) { m_winner = 0; return; }
		if (white_win)				{ m_winner = 1; return; }
		if (black_win)				{ m_winner = 2; return; }
	}
}

void Field::draw_field()
{
	for (int i = 0; i < m_dimension; ++i)
		for (int j = 0; j < m_dimension; ++j)
			window.draw(m_board[i][j]);
}
void Field::draw_checkers()
{
	for (int i = 0; i < m_dimension; ++i)
		for (int j = 0; j < m_dimension; ++j)
			if (m_logic[i][j]) window.draw(m_checkers[i][j]);
}
void Field::rendering()
{
	window.clear(Color::White); // clear the window and redraws it in white
	draw_field();
	draw_checkers();
	window.display();
}


int Field::get_width() { return m_width; }
int Field::get_winner() { return m_winner; }

Field::Field() : m_width(100), m_dimension(8), m_logic{Checkers::NONE}, m_start(std::make_pair(-1, -1)),
m_player_move(Checkers::WHITE), m_move_made(false), m_move(false), m_winner(-1)
{
	white.loadFromFile("../images/white.png");
	black.loadFromFile("../images/black.png");

	for (int i = 0; i < m_dimension; ++i)
		for (int j = 0; j < m_dimension; ++j)
		{
			m_board[i][j] = RectangleShape(Vector2f(m_width, m_width));
			m_board[i][j].move(j * m_width, i * m_width);

			if ((i + j) % 2) m_board[i][j].setFillColor(Color::Black);
			else m_board[i][j].setFillColor(Color::White);

			window.draw(m_board[i][j]);
		}

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
		{
			m_checkers[i][j] = Sprite(white);
			m_checkers[i + 5][j + 5] = Sprite(black);

			m_checkers[i][j].move(j * m_width, i * m_width);
			m_checkers[i + 5][j + 5].move((j + 5) * m_width, (i + 5) * m_width);

			m_logic[i][j] = Checkers::WHITE;
			m_logic[i + 5][j + 5] = Checkers::BLACK;

			window.draw(m_checkers[i][j]);
			window.draw(m_checkers[i + 5][j + 5]);
		}
	window.display();
}
void Field::move(const Event& event, int str, int col)
{
	if (!m_move) choose_cell(event, str, col);
	else
	{
		// here str, col - current coordinates where we want to go, m_start - coordinates from where we want to go
		if (static_cast<int>(event.key.code) == Mouse::Right)
		{
			next_move();
			cancel();
			m_move = false;
		}

		else if (static_cast<int>(event.key.code) == Mouse::Left && m_logic[str][col] == Checkers::NONE)
		{
			// If the checker has moved one and the move has not yet been made
			if (abs(m_start.first - str) < 2 && abs(m_start.second - col) < 2)
			{
				if (m_move_made) return;
				std::swap(m_logic[m_start.first][m_start.second], m_logic[str][col]);
				m_checkers[str][col] = (m_player_move == 1) ? Sprite(white) : Sprite(black);
				m_checkers[str][col].move(col * m_width, str * m_width);

				m_move_made = true;
				next_move();
			}


			// The 1st variable is whether it is possible to make a jump, the 2nd variable is whether there is a checker between the initial move and the next one
			else if (!((abs(m_start.first - str) + abs(m_start.second - col)) % 2) && m_logic[(m_start.first + str) / 2][(m_start.second + col) / 2])
			{

				std::swap(m_logic[m_start.first][m_start.second], m_logic[str][col]);
				m_checkers[str][col] = (m_player_move == 1) ? Sprite(white) : Sprite(black);
				m_checkers[str][col].move(col * m_width, str * m_width);

				m_move_made = true;
				cancel();
				choose_cell(event, str, col);
			}
		}
	}
}