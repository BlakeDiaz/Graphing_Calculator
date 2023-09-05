#include "coordinate_transformation_data.hpp"

Coordinate_Transformation_Data::Coordinate_Transformation_Data()
{
    x_offset = y_offset = 0;
    x_scale = y_scale = 1.0f;
}

Coordinate_Transformation_Data::Coordinate_Transformation_Data(const Graph_Window_Data& graph_window)
{
    x_offset = -1 * graph_window.get_x_midpoint();
    x_scale = 1.0f / (graph_window.get_total_x_length() / 2);
    y_offset = -1 * graph_window.get_y_midpoint();
    y_scale = 1.0f / (graph_window.get_total_y_length() / 2);
}

void Coordinate_Transformation_Data::update(const Graph_Window_Data& graph_window)
{
    x_offset = -1 * graph_window.get_x_midpoint();
    x_scale = 1.0f / (graph_window.get_total_x_length() / 2);
    y_offset = -1 * graph_window.get_y_midpoint();
    y_scale = 1.0f / (graph_window.get_total_y_length() / 2);
}

float Coordinate_Transformation_Data::get_x_offset() const
{
    return x_offset;
}

float Coordinate_Transformation_Data::get_x_scale() const
{
    return x_scale;
}

float Coordinate_Transformation_Data::get_y_offset() const
{
    return y_offset;
}

float Coordinate_Transformation_Data::get_y_scale() const
{
    return y_scale;
}
