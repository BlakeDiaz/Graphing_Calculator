#include "axis_marker_data.hpp"
#include <array>
#include <cmath>

#define MAX_NUMBER_OF_MARKERS 16

    Axis_Marker_Data::Axis_Marker_Data(float axis_min, float axis_max)
    {
        const float total_length = std::abs(axis_max - axis_min);
        // Update marker step
        float biggest_limit = std::max(std::abs(axis_min), std::abs(axis_max));
        float x_marker_step = biggest_limit / 100;
        float power_of_10 = std::log10(x_marker_step);

        power_of_10 = (power_of_10 > 0) ? std::ceil(power_of_10) : std::floor(power_of_10);

        float multiple = std::pow(10, power_of_10);
        std::array<float, 9> possible_marker_steps = {multiple * 1, multiple * 2, multiple * 5, multiple * 10, multiple * 20, multiple * 50, multiple * 100, multiple * 200, multiple * 500};
            
        marker_step = possible_marker_steps[possible_marker_steps.size()-1];
        number_of_markers = std::ceil(total_length/marker_step);

        for (int i = 0; i < possible_marker_steps.size(); i++)
        {
            int current_number_of_markers = std::ceil(total_length / possible_marker_steps[i]);
            if (current_number_of_markers <= MAX_NUMBER_OF_MARKERS)
            {
                marker_step = possible_marker_steps[i];
                number_of_markers = current_number_of_markers;
                break;
            }
        }

        if (axis_min < 0)
        {
            starting_point = axis_min - std::fmod(axis_min, marker_step);
        }
        else
        {
            starting_point = axis_min + marker_step - std::fmod(axis_min, marker_step);
        }

        markers = std::vector<float>();
        float marker;

        for (int i = 0; i < number_of_markers; i++)
        {
            marker = starting_point + (marker_step * i);
            markers.push_back(marker);
        }
    }

    /**
     * Gets the constant interval between each marker.
     * @return the constant interval between each marker.
     */
    float Axis_Marker_Data::get_marker_step() const
    {
        return marker_step;
    }
    
    /**
     * Gets the number of markers on the axis.
     * @return number of markers on the axis.
     */
    int Axis_Marker_Data::get_number_of_markers() const
    {
        return number_of_markers;
    }

    /**
     * Gets the starting point
     */
    int Axis_Marker_Data::get_starting_point() const
    {
        return starting_point;
    }

    /**
     * Provides a vector containing coordinates of where each marker on an axis should go.
     * The vector only contains coordinates in one axis.
     * The coordinates are spaced by a constant interval.
     * @return vector containing coordinates of where each marker on an axis should go.
     */
    std::vector<float> Axis_Marker_Data::get_markers() const
    {
        return markers;
    }
    
    /**
     * Render w/ GL_LINES
     */
    std::vector<float> Axis_Marker_Data::get_x_marker_points(float marker_top_y_coordinate, float marker_bottom_y_coordinate) const
    {
        std::vector<float> x_marker_points = std::vector<float>();

        for (int i = 0; i < number_of_markers; i++)
        {
            x_marker_points.push_back(markers[i]);
            x_marker_points.push_back(marker_bottom_y_coordinate);
            x_marker_points.push_back(markers[i]);
            x_marker_points.push_back(marker_top_y_coordinate);
        }

        return x_marker_points;
    }

    /**
     * Render w/ GL_LINES
     */
    std::vector<float> Axis_Marker_Data::get_y_marker_points(float marker_right_x_coordinate, float marker_left_x_coordinate) const
    {
        std::vector<float> y_marker_points = std::vector<float>();

        for (int i = 0; i < number_of_markers; i++)
        {
            y_marker_points.push_back(marker_left_x_coordinate);
            y_marker_points.push_back(markers[i]);
            y_marker_points.push_back(marker_right_x_coordinate);
            y_marker_points.push_back(markers[i]);
        }

        return y_marker_points;
    }