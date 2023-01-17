#include "field_logic.hpp"
#include "field_rendering.hpp"

extern RenderWindow window;
extern Texture white, black; // Можно попробовать сделать static

FieldRendering::FieldRendering(FieldLogic& logic) :
    m_width(100),
    m_field_logic(logic),

    m_board_fill(m_field_logic.m_dimension, std::vector<RectangleShape>(m_field_logic.m_dimension)),
    m_checkers_sprite(m_field_logic.m_dimension, std::vector<Sprite>(m_field_logic.m_dimension))
{
    white.loadFromFile("../images/white.png");
    black.loadFromFile("../images/black.png");

    for (int i = 0; i < m_field_logic.m_dimension; ++i)
        for (int j = 0; j < m_field_logic.m_dimension; ++j)
        {
            m_board_fill[i][j] = RectangleShape(Vector2f(m_width, m_width));
            m_board_fill[i][j].move(j * m_width, i * m_width);

            if ((i + j) % 2) m_board_fill[i][j].setFillColor(Color::Black);
            else m_board_fill[i][j].setFillColor(Color::White);

            window.draw(m_board_fill[i][j]);
        }

    for (int i = 0; i < m_field_logic.m_dimension-5; ++i)
        for (int j = 0; j < m_field_logic.m_dimension-5; ++j)
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

void FieldRendering::draw_field()
{
    for (int i = 0; i < m_field_logic.m_dimension; ++i)
        for (int j = 0; j < m_field_logic.m_dimension; ++j)
            window.draw(m_board_fill[i][j]);
}
void FieldRendering::draw_checkers()
{
    for (int i = 0; i < m_field_logic.m_dimension; ++i)
        for (int j = 0; j < m_field_logic.m_dimension; ++j)
            if (m_field_logic.m_logic[i][j]) window.draw(m_checkers_sprite[i][j]);
}
void FieldRendering::rendering()
{
    window.clear(Color::White); // clear the window and redraws it in white
    draw_field();
    draw_checkers();
    window.display();
}

int FieldRendering::get_width()  { return m_width;  }