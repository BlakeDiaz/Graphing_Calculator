#pragma once
#include "graph_window_data.hpp"

class Coordinate_Transformation_Data
{
public:
    Coordinate_Transformation_Data();
    Coordinate_Transformation_Data(const Graph_Window_Data& graph_window);
    void update(const Graph_Window_Data& graph_window);
    float get_x_offset() const;
    float get_x_scale() const;
    float get_y_offset() const;
    float get_y_scale() const;

private:
    float x_offset, x_scale, y_offset, y_scale;
    const float marker_top_normalized_coordinate = 0.1;
    const float marker_bottom_normalized_coordinate = -0.1;
};
