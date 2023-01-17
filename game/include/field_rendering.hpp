#ifndef FIELD_RENDERING_HPP
#define FIELD_RENDERING_HPP

#include "general.hpp"

class FieldRendering
{
private:
    friend class FieldLogic;
    const int m_width;

    std::vector<std::vector<RectangleShape>> m_board_fill; // field squares
    std::vector<std::vector<Sprite>> m_checkers_sprite; // checkers picture on the field

    void draw_field     (const std::vector<std::vector<Checkers>>& field_logic);
    void draw_checkers  (const std::vector<std::vector<Checkers>>& field_logic);
    void rendering      (const std::vector<std::vector<Checkers>>& field_logic);

    void fill_cell_with_color (int str, int col, Color color);
    void fill_cell_with_sprite(int str, int col, Checkers which_checker);

public:
    explicit FieldRendering();
};

#endif