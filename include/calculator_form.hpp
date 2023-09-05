#pragma once
#include "ui_calculator_form.hpp"
#include "graph_widget.hpp"
#include <QColorDialog>
#include <string>

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

private slots:
    void on_add_function();
    void on_remove_function();
    void on_reset_graph();
    void on_update_graph();
    void change_function_color(QPushButton* button, const QColor& color);
};
