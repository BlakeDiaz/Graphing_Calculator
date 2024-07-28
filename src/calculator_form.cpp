#include "calculator_form.hpp"
#include "Calculator.hpp"
#include "Input_Manager.hpp"
#include "graph_widget.hpp"
#include <QPushButton>
#include <QString>
#include <iostream>
#include <ostream>
#include <tuple>

static bool check_if_user_function_can_be_defined(const std::unordered_map<char, User_Function>& user_function_map,
                                                  const std::string& expression,
                                                  const std::unordered_set<char>& dependencies);

Calculator_Form::Calculator_Form(QWidget* parent) : QDialog(parent)
{
    ui.setupUi(this);

    // Create graph widget
    graph_gl_widget = new Graph_Widget(this);
    graph_gl_widget->setObjectName("graphGLWidget");
    graph_gl_widget->setMinimumSize(QSize(440, 0));
    graph_gl_widget->setMaximumSize(QSize(10000, 10000));
    ui.dialog_horizontal_layout->addWidget(graph_gl_widget);

    // Create color dialog
    color_dialog = new QColorDialog(this);

    QTableWidget* table = ui.function_table_widget;
    // Change input column width
    {
        int total_width = table->width();
        int vertical_header_width = table->verticalHeader()->sizeHint().width();
        int output_column_width = table->columnWidth(output_column);
        int color_column_width = table->columnWidth(color_column);
        int scroll_bar_width = style()->pixelMetric(QStyle::PM_ScrollBarExtent);
        int input_column_width =
            total_width - vertical_header_width - output_column_width - color_column_width - scroll_bar_width;
        table->setColumnWidth(0, input_column_width);
    }

    // Initialize table elements
    {
        QTableWidgetItem* current_input_item;
        QTableWidgetItem* current_output_item;
        QPushButton* current_color_button;
        for (int row = 0; row < table->rowCount(); row++)
        {
            current_input_item = new QTableWidgetItem();
            current_output_item = new QTableWidgetItem();
            current_color_button = new QPushButton();

            current_output_item->setFlags(current_output_item->flags() & ~Qt::ItemIsEditable);
            QObject::connect(current_color_button, &QPushButton::clicked, this, [this, current_color_button] {
                change_function_color(current_color_button, color_dialog->getColor());
            });
            change_function_color(current_color_button, default_function_color);

            table->setItem(row, input_column, current_input_item);
            table->setItem(row, output_column, current_output_item);
            table->setCellWidget(row, color_column, current_color_button);
        }
        QString initialFunctionText = QString::fromStdString(default_function_input_text);
        table->item(0, input_column)->setText(initialFunctionText);
    }

    // Set default button for when the enter key is hit
    ui.update_graph_push_button->setAutoDefault(true);
    ui.update_graph_push_button->setDefault(true);

    // Set up signals/slots
    QObject::connect(ui.add_function_push_button, &QPushButton::clicked, this, &Calculator_Form::add_function);
    QObject::connect(ui.remove_function_push_button, &QPushButton::clicked, this, &Calculator_Form::remove_function);
    QObject::connect(ui.reset_graph_push_button, &QPushButton::clicked, this, &Calculator_Form::reset_graph);
    QObject::connect(ui.update_graph_push_button, &QPushButton::clicked, this, &Calculator_Form::update_graph);
}

void Calculator_Form::add_function()
{
    QTableWidget* table = ui.function_table_widget;

    // Add vertical header
    int row_count = table->rowCount();
    QString vertical_header_text = QString::fromStdString(std::to_string(table->rowCount() + 1) + ")");
    table->insertRow(table->rowCount());
    table->setVerticalHeaderItem(table->rowCount() - 1, new QTableWidgetItem(vertical_header_text));

    QTableWidgetItem* input_item = new QTableWidgetItem();
    QTableWidgetItem* output_item = new QTableWidgetItem();
    QPushButton* color_button = new QPushButton();

    table->setItem(table->rowCount() - 1, input_column, input_item);
    table->setItem(table->rowCount() - 1, output_column, output_item);
    table->setCellWidget(table->rowCount() - 1, color_column, color_button);

    output_item->setFlags(output_item->flags() & ~Qt::ItemIsEditable);
    QObject::connect(color_button, &QPushButton::clicked, this,
                     [this, color_button] { change_function_color(color_button, color_dialog->getColor()); });
    change_function_color(color_button, default_function_color);


    // Redraw window to prevent ghost color button from appearing
    update();
}

void Calculator_Form::remove_function()
{
    QTableWidget* table = ui.function_table_widget;
    if (table->rowCount() > default_number_of_functions)
    {
        table->removeRow(table->rowCount() - 1);
    }
}

void Calculator_Form::reset_graph()
{
    QTableWidget* table = ui.function_table_widget;
    while (table->rowCount() > default_number_of_functions)
    {
        table->removeRow(table->rowCount() - 1);
    }

    for (int row = 0; row < table->rowCount(); row++)
    {
        // Reset text of table
        table->item(row, 0)->setText("");
        table->item(row, 1)->setText("");
        // Reset color button to red
        change_function_color((QPushButton*)table->cellWidget(row, 2), default_function_color);
    }
    table->item(0, 0)->setText("f(x) = x + 3");
}

void Calculator_Form::update_graph()
{
    QTableWidget* table = ui.function_table_widget;
    QString input_text;
    QColor current_color;

    std::vector<std::tuple<std::string, std::unordered_set<char>, QColor>> new_user_function_expressions;

    for (int row = 0; row < table->rowCount(); row++)
    {
        input_text = table->item(row, input_column)->text();
        current_color = table->cellWidget(row, color_column)->palette().color(QPalette::Button);

        if (input_text == "")
        {
            continue;
        }

        Calculator::ExpressionType type = Calculator::identify_expression(input_text.toStdString());

        switch (type)
        {
        case Calculator::SOLVABLE_EXPRESSION: {
            break;
        }
        case Calculator::FUNCTION_DEFINITION: {
            new_user_function_expressions.push_back(
                std::tuple(input_text.toStdString(),
                           Calculator::locate_user_function_dependencies(input_text.toStdString()), current_color));

            break;
        }
        default: {
            std::cerr << "Invalid Expression Type" << std::endl;

            break;
        }
        }
    }

    user_function_map = Input_Manager::create_user_function_map(new_user_function_expressions);

    float x_min = std::stof(ui.x_axis_lower_bound_line_edit->text().toStdString());
    float y_min = std::stof(ui.y_axis_lower_bound_line_edit->text().toStdString());
    float x_max = std::stof(ui.x_axis_upper_bound_line_edit->text().toStdString());
    float y_max = std::stof(ui.y_axis_upper_bound_line_edit->text().toStdString());
    QString output_text;

    for (int row = 0; row < table->rowCount(); row++)
    {
        input_text = table->item(row, input_column)->text();

        if (input_text == "")
        {
            table->item(row, output_column)->setText("");
            continue;
        }

        switch (Calculator::identify_expression(input_text.toStdString()))
        {
        case Calculator::SOLVABLE_EXPRESSION: {
            output_text = QString::number(Calculator::solve_expression(
                Calculator::format_expression(user_function_map, input_text.toStdString())));
            break;
        }
        case Calculator::FUNCTION_DEFINITION: {
            output_text = "";
            break;
        }
        default: {
            std::cerr << "Invalid Expression Type" << std::endl;
            break;
        }
        }

        table->item(row, output_column)->setText(output_text);
    }

    graph_gl_widget->update_state(user_function_map, {.x_min = x_min, .x_max = x_max, .y_min = y_min, .y_max = y_max});
}

void Calculator_Form::change_function_color(QPushButton* button, const QColor& color)
{
    QPalette palette = button->palette();
    palette.setColor(QPalette::Button, color);
    button->setAutoFillBackground(true);
    button->setPalette(palette);
    button->update();
}

void Calculator_Form::changeEvent(QEvent* e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui.retranslateUi(this);
        break;
    default:
        break;
    }
}
