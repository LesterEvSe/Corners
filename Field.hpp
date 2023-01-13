#ifndef FIELD_HPP
#define FIELD_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib> // for std::swap
#include <array> // for constant dimensions of boards

using namespace sf;

enum Checkers
{
    NONE = 0,
    WHITE = 1,
    BLACK = 2
};

class Field
{
private:
	const int m_width;
	const int m_dimension;

	std::array<std::array<int, 8>, 8> m_logic;

	std::array<std::array<RectangleShape, 8>, 8> m_board;
	std::array<std::array<Sprite, 8>, 8> m_checkers;

	std::pair<int, int> m_start;
	int  m_player_move;
	bool m_move_made;
	bool m_move;
	int  m_winner;

	void choose_cell(const Event&, int str, int col);
	void cancel();
	void next_move();
	void check_winner();

	void draw_field();
	void draw_checkers();
	void rendering();

public:
	int get_width();
	int get_winner();

	Field();
	void move(const Event&, int str, int col);
};

#endif