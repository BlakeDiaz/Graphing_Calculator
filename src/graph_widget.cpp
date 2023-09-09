#include "graph_widget.hpp"

#include "User_Function.hpp"
#include "Calculator.hpp"
#include "coordinate_transformation_data.hpp"
#include "axis_marker_data.hpp"
#include "graph_window_data.hpp"
#include "line_rendering_data.hpp"
#include <QOpenGLExtraFunctions>
#include <iostream>

#define MAX_NUMBER_OF_MARKERS 16

static bool create_shader_program(QOpenGLShaderProgram& program, const QString& vertex_shader_path, const QString& fragment_shader_path)
{
    bool result;

    result = program.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_shader_path);
    if (!result)
    {
        qWarning() << program.log();
        return false;
    }

    result = program.addShaderFromSourceFile(QOpenGLShader::Fragment, fragment_shader_path);
    if (!result)
    {
        qWarning() << program.log();
        return false;
    }

    result = program.link();
    if (!result)
    {
        qWarning() << program.log();
        return false;
    }

    return true;
}

Graph_Widget::Graph_Widget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    setFixedSize(200, 200);
}

void Graph_Widget::initializeGL()
{
    // Initialize shader programs
    if (!create_shader_program(axis_shader, "res/shaders/axis_shader.vs", "res/shaders/axis_shader.fs"))
    {
        std::cout << "Couldn't compile axis shader" << std::endl;
    }
    
    if (!create_shader_program(curve_shader, "res/shaders/curve_shader.vs", "res/shaders/curve_shader.fs"))
    {
        std::cout << "Couldn't compile curve shader" << std::endl;
    }

    // Clear color
    functions = QOpenGLContext::currentContext()->extraFunctions();
    functions->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    functions->glClear(GL_COLOR_BUFFER_BIT);

    // Initialize window settings
    Graph_Window_Data graph_window = {.x_min = -10, .x_max = 10, .y_min = -10, .y_max = 10};
    transformation_data.update(graph_window);

    Axis_Marker_Data x_axis_marker_data(graph_window.x_min, graph_window.x_max);
    Axis_Marker_Data y_axis_marker_data(graph_window.y_min, graph_window.y_max);

    std::array<float, 4> x_axis_points = {graph_window.x_min, 0, graph_window.x_max, 0};
    std::array<float, 4> y_axis_points = {0, graph_window.y_min, 0, graph_window.y_max};
    std::vector<float> x_axis_marker_points = x_axis_marker_data.get_x_marker_points(graph_window.get_x_marker_height()/2, -graph_window.get_x_marker_height()/2);
    std::vector<float> y_axis_marker_points = y_axis_marker_data.get_y_marker_points(graph_window.get_y_marker_length()/2, -graph_window.get_y_marker_length()/2);

    x_axis_rendering_data.VAO = setup_points_VAO(x_axis_points.data(), x_axis_points.size());
    y_axis_rendering_data.VAO = setup_points_VAO(y_axis_points.data(), y_axis_points.size());
    x_axis_marker_rendering_data.VAO = setup_points_VAO(x_axis_marker_points.data(), x_axis_marker_points.size());
    y_axis_marker_rendering_data.VAO = setup_points_VAO(y_axis_marker_points.data(), y_axis_marker_points.size());
        
    // Our containers hold x and y coordinates as individual elements,
    // so we divide the number of elements in them by 2 to get the number of points
    x_axis_rendering_data.number_of_points = x_axis_points.size()/2;
    y_axis_rendering_data.number_of_points = y_axis_points.size()/2;
    x_axis_marker_rendering_data.number_of_points = x_axis_marker_points.size()/2;
    y_axis_marker_rendering_data.number_of_points = y_axis_marker_points.size()/2;
}

void Graph_Widget::resizeGL(int width, int height)
{
}

void Graph_Widget::paintGL()
{
    functions = QOpenGLContext::currentContext()->extraFunctions();
    functions->glClear(GL_COLOR_BUFFER_BIT);

    render_line(axis_shader, transformation_data, x_axis_rendering_data);
    render_line(axis_shader, transformation_data, y_axis_rendering_data);

    for (auto& curve_rendering_data : curves_rendering_data)
    {
        render_line(curve_shader, transformation_data, curve_rendering_data);
    }

    render_disconnected_lines(axis_shader, transformation_data, x_axis_marker_rendering_data);
    render_disconnected_lines(axis_shader, transformation_data, y_axis_marker_rendering_data);
}

void Graph_Widget::update_state(const std::unordered_map<char, User_Function>& user_function_map, const Graph_Window_Data& graph_window)
{
    // This lets us call OpenGL functions outside of initializeGL, resizeGL, and paintGL 
    makeCurrent();

    functions->glDeleteVertexArrays(1, &x_axis_rendering_data.VAO);
    functions->glDeleteVertexArrays(1, &y_axis_rendering_data.VAO);
    functions->glDeleteVertexArrays(1, &x_axis_marker_rendering_data.VAO);
    functions->glDeleteVertexArrays(1, &y_axis_marker_rendering_data.VAO);
    for (Line_Rendering_Data& data : curves_rendering_data)
    {
        functions->glDeleteVertexArrays(1, &data.VAO);
    }

    // Update x and y axes, as well as their markers based on the new graph window
    transformation_data.update(graph_window);

    Axis_Marker_Data x_axis_marker_data(graph_window.x_min, graph_window.x_max);
    Axis_Marker_Data y_axis_marker_data(graph_window.y_min, graph_window.y_max);

    std::array<float, 4> x_axis_points = {graph_window.x_min, 0, graph_window.x_max, 0};
    std::array<float, 4> y_axis_points = {0, graph_window.y_min, 0, graph_window.y_max};

    std::vector<float> x_axis_marker_points = x_axis_marker_data.get_x_marker_points(graph_window.get_x_marker_height()/2, -graph_window.get_x_marker_height()/2);
    std::vector<float> y_axis_marker_points = y_axis_marker_data.get_y_marker_points(graph_window.get_y_marker_length()/2, -graph_window.get_y_marker_length()/2);

    x_axis_rendering_data.VAO = setup_points_VAO(x_axis_points.data(), x_axis_points.size());
    y_axis_rendering_data.VAO = setup_points_VAO(y_axis_points.data(), y_axis_points.size());
    x_axis_marker_rendering_data.VAO = setup_points_VAO(x_axis_marker_points.data(), x_axis_marker_points.size());
    y_axis_marker_rendering_data.VAO = setup_points_VAO(y_axis_marker_points.data(), y_axis_marker_points.size());
        
    // Our containers hold x and y coordinates as individual elements,
    // so we divide the number of elements in them by 2 to get the number of points
    x_axis_rendering_data.number_of_points = x_axis_points.size()/2;
    y_axis_rendering_data.number_of_points = y_axis_points.size()/2;
    x_axis_marker_rendering_data.number_of_points = x_axis_marker_points.size()/2;
    y_axis_marker_rendering_data.number_of_points = y_axis_marker_points.size()/2;

    // Update our curves based on the new graph window, as well as any changes to the inputted User_Functions
    float x_step = (graph_window.x_max - graph_window.x_min) / total_number_of_curve_points;

    curves_rendering_data.clear();

    for (const auto& [identifier, user_function] : user_function_map)
    {
        std::vector<float> curve_points = create_curve(user_function, graph_window.x_min, graph_window.x_max, x_step);
        curves_rendering_data.push_back({
            .VAO = setup_points_VAO(curve_points.data(), curve_points.size()),
            .number_of_points = curve_points.size()/2
        });
    }

    // Repaints the graph to display the new changes (paintGL shouldn't be called directly)
    update();
}

std::vector<float> Graph_Widget::create_curve(const User_Function& user_function, const float lower_x_limit, const float upper_x_limit, const float x_step)
{
    const int number_of_points = (upper_x_limit - lower_x_limit) / x_step;
    
    std::vector<float> graph = std::vector<float>();

    for (int i = 0; i < number_of_points; i++)
    {
        float x = (i * x_step) + lower_x_limit;
        float y = Calculator::solve_expression(user_function.call(std::to_string(x)));
        graph.push_back(x);
        graph.push_back(y);
    }
    
    return graph;
}

unsigned int Graph_Widget::setup_points_VAO(float data[], unsigned int data_length)
{
    unsigned int VBO, VAO;
    functions->glGenVertexArrays(1, &VAO);
    functions->glGenBuffers(1, &VBO);

    functions->glBindVertexArray(VAO);

    functions->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    functions->glBufferData(GL_ARRAY_BUFFER, data_length * sizeof(float), data, GL_STATIC_DRAW);

    functions->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    functions->glEnableVertexAttribArray(0);

    functions->glBindBuffer(GL_ARRAY_BUFFER, 0);

    functions->glBindVertexArray(0);
    functions->glDeleteBuffers(1, &VBO);

    return VAO;
}

void Graph_Widget::render_line(QOpenGLShaderProgram& program, const Coordinate_Transformation_Data& transformation_data, const Line_Rendering_Data& curve_data)
{
    program.bind();
    program.setUniformValue(program.uniformLocation("x_offset"), transformation_data.get_x_offset());
    program.setUniformValue(program.uniformLocation("x_scale"), transformation_data.get_x_scale());
    program.setUniformValue(program.uniformLocation("y_offset"), transformation_data.get_y_offset());
    program.setUniformValue(program.uniformLocation("y_scale"), transformation_data.get_y_scale());

    functions->glBindVertexArray(curve_data.VAO);
    functions->glDrawArrays(GL_LINE_STRIP, 0, curve_data.number_of_points);
}

void Graph_Widget::render_disconnected_lines(QOpenGLShaderProgram& program, const Coordinate_Transformation_Data& transformation_data, const Line_Rendering_Data& lines_data)
{
    program.bind();
    program.setUniformValue(program.uniformLocation("x_offset"), transformation_data.get_x_offset());
    program.setUniformValue(program.uniformLocation("x_scale"), transformation_data.get_x_scale());
    program.setUniformValue(program.uniformLocation("y_offset"), transformation_data.get_y_offset());
    program.setUniformValue(program.uniformLocation("y_scale"), transformation_data.get_y_scale());

    functions->glBindVertexArray(lines_data.VAO);
    functions->glDrawArrays(GL_LINES, 0, lines_data.number_of_points);
}
