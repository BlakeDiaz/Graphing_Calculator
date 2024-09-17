#pragma once
#include "User_Function.hpp"
#include "graph_widget.hpp"
#include "ui_calculator_form.h"
#include <QColorDialog>
#include <string>
#include <vector>
#include <optional>
#include <Parse_Error.hpp>
#include <User_Function_Map_Error.hpp>

class Calculator_Form : public QDialog
{
    Q_OBJECT;

  public:
    Graph_Widget* graph_gl_widget;

    explicit Calculator_Form(QWidget* parent = nullptr);

  protected:
    void changeEvent(QEvent* e);

  private:
    Ui::Calculator_Form ui;
    QColorDialog* color_dialog;
    inline static const QColor default_function_color = QColor(255, 0, 0);
    static const int default_number_of_functions = 5;
    static const int input_column = 0;
    static const int output_column = 1;
    static const int color_column = 2;
    inline static const std::string default_function_input_text = "f(x) = x + 3";
    std::unordered_map<char, User_Function> user_function_map;
    std::vector<std::unordered_set<char>> user_functions;

  private slots:
    void add_function();
    void remove_function();
    void reset_graph();
    void update_graph();
    void x_axis_toggled(Qt::CheckState state);
    void y_axis_toggled(Qt::CheckState state);
    void change_function_color(QPushButton* button, const QColor& color);
    std::optional<Graph_Window_Data> get_graph_window_data();
    void display_user_function_map_error_in_table(const User_Function_Map_Error& parse_error);
    void display_error_in_table(const Parse_Error& parse_error, int row);
    void display_error_message_box(const QString& header, const QString& message);
};
