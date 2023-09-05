#pragma once
#include <vector>

/**
 * Class containing data about the coordinate markers on an axis.
 */
class Axis_Marker_Data
{
public:
    Axis_Marker_Data(float axis_min, float axis_max);

    /**
     * Gets the constant interval between each marker.
     * @return the constant interval between each marker.
     */
    float get_marker_step() const;

    /**
     * Gets the number of markers on the axis.
     * @return number of markers on the axis.
     */
    int get_number_of_markers() const;

    /**
     * Gets the starting point
     */
    int get_starting_point() const;

    /**
     * Provides a vector containing coordinates of where each marker on an axis should go.
     * The vector only contains coordinates in one axis.
     * The coordinates are spaced by a constant interval.
     * @return vector containing coordinates of where each marker on an axis should go.
     */
    std::vector<float> get_markers() const;
    /**
     * Render w/ GL_LINES
     */
    std::vector<float> get_x_marker_points(float marker_top_y_coordinate, float marker_bottom_y_coordinate) const;

    /**
     * Render w/ GL_LINES
     */
    std::vector<float> get_y_marker_points(float marker_right_x_coordinate, float marker_left_x_coordinate) const;

private:
    float marker_step;
    float starting_point;
    int number_of_markers;
    std::vector<float> markers;
};
