#pragma once
#include <QColor>
#include <cstdlib>

struct Line_Rendering_Data
{
    unsigned int VAO;
    std::size_t number_of_points;
    QColor color;
};
