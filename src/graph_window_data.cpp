#include "graph_window_data.hpp"

float Graph_Window_Data::get_total_x_length() const
{
    return x_max - x_min;
}

float Graph_Window_Data::get_x_midpoint() const
{
    return (x_max + x_min)/2;
}

float Graph_Window_Data::get_x_marker_height() const
{
    return get_total_y_length()/50;
}

float Graph_Window_Data::get_total_y_length() const
{
    return y_max - y_min;
}

float Graph_Window_Data::get_y_midpoint() const
{
    return (y_max + y_min)/2;
}

float Graph_Window_Data::get_y_marker_length() const
{
    return get_total_x_length()/50;
}
