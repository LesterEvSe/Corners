#include "field_logic.hpp"
#include "field_rendering.hpp"

extern RenderWindow window;
static Texture white, black;

FieldRendering::FieldRendering() :
    m_board_fill(FieldLogic::m_dimension, std::vector<RectangleShape>(FieldLogic::m_dimension)),
    m_checkers_sprite(FieldLogic::m_dimension, std::vector<Sprite>(FieldLogic::m_dimension))
{
    white.loadFromFile("../res/white.png");
    black.loadFromFile("../res/black.png");

    for (int i = 0; i < FieldLogic::m_dimension; ++i)
        for (int j = 0; j < FieldLogic::m_dimension; ++j)
        {
            m_board_fill[i][j] = RectangleShape(Vector2f(m_width, m_width));
            m_board_fill[i][j].move(j * m_width, i * m_width);

            if ((i + j) % 2) m_board_fill[i][j].setFillColor(Color::Black);
            else m_board_fill[i][j].setFillColor(Color::White);

            window.draw(m_board_fill[i][j]);
        }

    for (int i = 0; i < FieldLogic::m_dimension-5; ++i)
        for (int j = 0; j < FieldLogic::m_dimension-5; ++j)
        {
            m_checkers_sprite[i][j] = Sprite(white);
            m_checkers_sprite[i + 5][j + 5] = Sprite(black);

            m_checkers_sprite[i][j].move(j * m_width, i * m_width);
            m_checkers_sprite[i + 5][j + 5].move((j + 5) * m_width, (i + 5) * m_width);

            window.draw(m_checkers_sprite[i][j]);
            window.draw(m_checkers_sprite[i + 5][j + 5]);
        }
    window.display();
}

void FieldRendering::draw_field(const std::vector<std::vector<Checkers>>& field_logic) const
{
    for (int i = 0; i < field_logic.size(); ++i)
        for (int j = 0; j < field_logic[i].size(); ++j)
            window.draw(m_board_fill[i][j]);
}
void FieldRendering::draw_checkers(const std::vector<std::vector<Checkers>>& field_logic) const
{
    for (int i = 0; i < field_logic.size(); ++i)
        for (int j = 0; j < field_logic[i].size(); ++j)
            if (field_logic[i][j]) window.draw(m_checkers_sprite[i][j]);
}
void FieldRendering::rendering(const std::vector<std::vector<Checkers>>& field_logic) const
{
    window.clear(Color::White); // clear the window and redraws it in white
    draw_field(field_logic);
    draw_checkers(field_logic);
    window.display();
}

void FieldRendering::fill_cell_with_color(int str, int col, Color color) {
    m_board_fill[str][col].setFillColor(color);
}
void FieldRendering::fill_cell_with_sprite(int str, int col, Checkers which_checker) {
    m_checkers_sprite[str][col] = (which_checker == Checkers::WHITE) ? Sprite(white) : Sprite(black);
    m_checkers_sprite[str][col].move(col * m_width, str * m_width);
}