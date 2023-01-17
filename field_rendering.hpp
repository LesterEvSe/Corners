#ifndef FIELD_RENDERING_HPP
#define FIELD_RENDERING_HPP

#include <vector>
#include "field_logic.hpp"
#include "general_set.hpp"

class FieldRendering
{
private:
    const int m_width;
    FieldLogic& m_field_logic;

    std::vector<std::vector<RectangleShape>> m_board_fill; // field squares
    std::vector<std::vector<Sprite>> m_checkers_sprite; // checkers picture on the field

    void draw_field();
    void draw_checkers();
    void rendering();

public:
    int get_width();

    FieldRendering(FieldLogic &logic);
};

#endif