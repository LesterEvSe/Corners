#ifndef FIELD_LOGIC_HPP
#define FIELD_LOGIC_HPP

#include "general.hpp"
#include "field_rendering.hpp"

class FieldLogic
{
private:
    friend class FieldRendering;

    FieldRendering m_field_rendering;
	static const int m_dimension = 8;
	std::vector<std::vector<Checkers>> m_logic; // checkers that determine what stands in a certain cell

	std::pair<int, int> m_start;
	Checkers m_player_move;
	bool m_move_made;
	bool m_move;
	int  m_winner;

	void choose_cell(const Event&, int str, int col);
	void cancel();
	void next_move();
	void check_winner();

public:
	int get_width();
	int get_winner();

	FieldLogic();
	void move(const Event&, int str, int col);
};

#endif