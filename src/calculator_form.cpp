#include "calculator_form.hpp"
#include "graph_widget.hpp"
#include <iostream>
#include <QPushButton>
#include <QString>

Calculator_Form::Calculator_Form(QWidget* parent)
    : QDialog(parent)
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
        int input_column_width = total_width - vertical_header_width - output_column_width - color_column_width - scroll_bar_width;
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
            QObject::connect(current_color_button, &QPushButton::clicked, this, [this, current_color_button]{change_function_color(current_color_button, color_dialog->getColor());});
            change_function_color(current_color_button, default_function_color);

            table->setItem(row, input_column, current_input_item);
            table->setItem(row, output_column, current_output_item);
            table->setCellWidget(row, color_column, current_color_button);

            
        }
        QString initialFunctionText = QString::fromStdString(default_function_input_text); 
        table->item(0, input_column)->setText(initialFunctionText);
    }

    // Set up signals/slots
    QObject::connect(ui.add_function_push_button, &QPushButton::clicked, this, &Calculator_Form::on_add_function);
    QObject::connect(ui.remove_function_push_button, &QPushButton::clicked, this, &Calculator_Form::on_remove_function);
    QObject::connect(ui.reset_graph_push_button, &QPushButton::clicked, this, &Calculator_Form::on_reset_graph);
    QObject::connect(ui.update_graph_push_button, &QPushButton::clicked, this, &Calculator_Form::on_update_graph);
}

void Calculator_Form::on_add_function()
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

    output_item->setFlags(output_item->flags() & ~Qt::ItemIsEditable);
    QObject::connect(color_button, &QPushButton::clicked, this, [this, color_button]{change_function_color(color_button, color_dialog->getColor());});
    change_function_color(color_button, default_function_color);

    table->setItem(table->rowCount() - 1, input_column, input_item);
    table->setItem(table->rowCount()-1, output_column, output_item);
    table->setCellWidget(table->rowCount()-1, color_column, color_button);
}

void Calculator_Form::on_remove_function()
{
    QTableWidget* table = ui.function_table_widget;
    if (table->rowCount() > default_number_of_functions)
    {
        table->removeRow(table->rowCount() - 1);
    }
}

void Calculator_Form::on_reset_graph()
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

void Calculator_Form::on_update_graph()
{
    // Pass text from input sections of table to calculator, then display on openglwidget
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
    switch(e->type())
    {
        case QEvent::LanguageChange:
            ui.retranslateUi(this);
            break;
        default:
            break;
    }
}
