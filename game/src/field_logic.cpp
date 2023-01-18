#include <cstdlib> // for std::swap
#include <utility> // for std::make_pair
#include "field_logic.hpp"

FieldLogic::FieldLogic() :
    m_field_rendering(FieldRendering{}),
    m_logic(m_dimension, std::vector<Checkers>(m_dimension)),

    m_start(std::make_pair(-1, -1)),
    m_player_move(Checkers::WHITE),
    m_move_made(false),
    m_move(false),
    m_winner(-1)
{
    for (int i = 0; i < m_dimension-5; ++i)
        for (int j = 0; j < m_dimension-5; ++j)
        {
            m_logic[i][j] = Checkers::WHITE;
            m_logic[i + 5][j + 5] = Checkers::BLACK;
        }
}

int FieldLogic::get_width()  const  { return m_field_rendering.m_width;  }
int FieldLogic::get_winner() const  { return m_winner; }

void FieldLogic::check_winner()
{
    if (m_player_move != Checkers::WHITE) return;
    bool white_win = true;
    bool black_win = true;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            if (m_logic[i][j] != Checkers::BLACK)         black_win = false;
            if (m_logic[i + 5][j + 5] != Checkers::WHITE) white_win = false;

            if (!black_win && !white_win) {
                m_winner = -1;
                return;
            }
        }
    if (black_win && white_win) { m_winner = 0; return; }
    if (white_win)				{ m_winner = 1; return; }
    if (black_win)				{ m_winner = 2; return; }
}

void FieldLogic::cancel()
{
	if (m_start.first != -1)
	{
		if ((m_start.first + m_start.second) % 2) m_field_rendering.fill_cell_with_color(m_start.first, m_start.second, Color::Black);
		else m_field_rendering.fill_cell_with_color(m_start.first, m_start.second, Color::White);
		m_start.first = -1;
	}
    m_field_rendering.rendering(m_logic);
}
void FieldLogic::next_move()
{
	// You can walk only when you make a move
	if (m_move_made)
	{
		cancel();
		m_player_move = (m_player_move == Checkers::WHITE) ? Checkers::BLACK : Checkers::WHITE;
		m_move_made = false;
		m_move = false;
		check_winner();
	}
    m_field_rendering.rendering(m_logic);
}
void FieldLogic::choose_cell(const Event& event, int str, int col)
{
    if (static_cast<int>(event.key.code) == Mouse::Left && m_logic[str][col] == m_player_move)
    {
        m_field_rendering.fill_cell_with_color(str, col, Color::Green);

        m_start = std::make_pair(str, col);
        m_move = true;
    }
    m_field_rendering.rendering(m_logic);
}

void FieldLogic::move(const Event& event, int str, int col)
{
	if (!m_move){
        choose_cell(event, str, col);
        return;
    }
    // here str, col - current coordinates where we want to go, m_start - coordinates from where we want to go
    if (static_cast<int>(event.key.code) == Mouse::Right)
    {
        next_move();
        cancel();
        m_move = false;
        return;
    }
    if (static_cast<int>(event.key.code) != Mouse::Left || m_logic[str][col] != Checkers::NONE) return;

    // If the checker has moved one and the move has not yet been made
    if (abs(m_start.first - str) < 2 && abs(m_start.second - col) < 2)
    {
        if (m_move_made) return;
        std::swap(m_logic[m_start.first][m_start.second], m_logic[str][col]);
        m_field_rendering.fill_cell_with_sprite(str, col, m_player_move);

        m_move_made = true;
        next_move();
        return;
    }

    bool limit = abs(m_start.first - str) <= 2 && abs(m_start.second - col) <= 2;
    bool can_jump = !((abs(m_start.first - str) + abs(m_start.second - col)) % 2);
    bool can_move = m_logic[(m_start.first + str) / 2][(m_start.second + col) / 2];
    if (limit && can_jump && can_move)
    {
        std::swap(m_logic[m_start.first][m_start.second], m_logic[str][col]);
        m_field_rendering.fill_cell_with_sprite(str, col, m_player_move);

        m_move_made = true;
        cancel();
        choose_cell(event, str, col);
    }
}