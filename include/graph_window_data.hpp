#pragma once

struct Graph_Window_Data
{
    float x_min, x_max, y_min, y_max;

    float get_total_x_length() const;
    float get_x_midpoint() const;
    float get_x_marker_height() const;
    float get_total_y_length() const;
    float get_y_midpoint() const;
    float get_y_marker_length() const;
};
