#pragma once
#include "coordinate_transformation_data.hpp"
#include "line_rendering_data.hpp"
#include "User_Function.hpp"

#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Graph_Widget: public QOpenGLWidget
{

public:
    Graph_Widget(QWidget* parent);
    void update_state(const std::unordered_map<char, User_Function>& user_function_map, const Graph_Window_Data& graph_window);

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

private:
    QOpenGLExtraFunctions* functions;
    QOpenGLShaderProgram axis_shader;
    QOpenGLShaderProgram curve_shader;
    Coordinate_Transformation_Data transformation_data;
    Line_Rendering_Data x_axis_rendering_data;
    Line_Rendering_Data y_axis_rendering_data;
    std::vector<Line_Rendering_Data> curves_rendering_data;
    Line_Rendering_Data x_axis_marker_rendering_data;
    Line_Rendering_Data y_axis_marker_rendering_data;
    const float x_step = 0.01;
    
    std::vector<float> create_curve(const User_Function& user_function, const float lower_x_limit, const float upper_x_limit, const float x_step);
    unsigned int setup_points_VAO(float data[], unsigned int data_length);
    void render_line(QOpenGLShaderProgram& program, const Coordinate_Transformation_Data& transformation_data, const Line_Rendering_Data& curve_data);
    void render_disconnected_lines(QOpenGLShaderProgram& program, const Coordinate_Transformation_Data& transformation_data, const Line_Rendering_Data& lines_data);
};


