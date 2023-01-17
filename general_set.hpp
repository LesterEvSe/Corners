#ifndef GENERAL_SET_HPP
#define GENERAL_SET_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

enum Checkers
{
    NONE = 0,
    WHITE = 1,
    BLACK = 2
};

struct RenderingInstructionsCell
{
    Color cell_fill;
    Checkers checker;
};

#endif