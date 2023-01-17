#ifndef FIELD_LOGIC_HPP
#define FIELD_LOGIC_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib> // for std::swap
#include <utility> // for std::make_pair
#include <vector> // for constant dimensions of boards
//#include "field_rendering.hpp"

using namespace sf;

enum Checkers
{
    NONE = 0,
    WHITE = 1,
    BLACK = 2
};

class FieldLogic
{
private:
    friend class FieldRendering;
	const int m_width;
	const int m_dimension;

	std::vector<std::vector<Checkers>> m_logic; // checkers that determine what stands in a certain cell

	std::vector<std::vector<RectangleShape>> m_board_fill; // field squares
	std::vector<std::vector<Sprite>> m_checkers_sprite; // checkers picture on the field

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

	FieldLogic();
	void move(const Event&, int str, int col);
};

#endif