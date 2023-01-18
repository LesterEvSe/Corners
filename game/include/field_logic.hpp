#ifndef FIELD_LOGIC_HPP
#define FIELD_LOGIC_HPP

#include "general.hpp"
#include "field_rendering.hpp"

class FieldLogic
{
public:
    static const int m_dimension = 8;

private:
    FieldRendering m_field_rendering;
	std::vector<std::vector<Checkers>> m_logic; // checkers that determine what stands in a certain cell

	std::pair<int, int> m_start;
	Checkers m_player_move;
	bool m_move_made;
	bool m_move;
	int  m_winner;

    void check_winner();
	void cancel();
	void next_move();
    void choose_cell(const Event&, int str, int col);

public:
    FieldLogic();

    int get_width()  const;
	int get_winner() const;

	void move(const Event&, int str, int col);
};

#endif