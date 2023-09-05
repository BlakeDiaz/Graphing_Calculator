/********************************************************************************
** Form generated from reading UI file 'calculator_form.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATOR_FORM_H
#define UI_CALCULATOR_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Calculator_Form
{
public:
    QHBoxLayout *dialog_horizontal_layout;
    QVBoxLayout *settings_vertical_layout;
    QFrame *window_settings_frame;
    QLabel *y_axis_label;
    QLabel *x_axis_label;
    QLabel *window_settings_label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *x_axis_settings_layout;
    QCheckBox *x_axis_enabled_check_box;
    QCheckBox *x_axis_markers_enabled_check_box;
    QLineEdit *x_axis_lower_bound_line_edit;
    QLabel *x_axis_range_label;
    QLineEdit *x_axis_upper_bound_line_edit;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *y_axis_settings_layout;
    QCheckBox *y_axis_enabled_check_box;
    QCheckBox *y_axis_markers_enabled_check_box;
    QLineEdit *y_axis_lower_bound_line_edit;
    QLabel *y_axis_range_label;
    QLineEdit *y_axis_upper_bound_line_edit;
    QTableWidget *function_table_widget;
    QGridLayout *button_grid_layout;
    QPushButton *reset_graph_push_button;
    QPushButton *update_graph_push_button;
    QPushButton *remove_function_push_button;
    QPushButton *add_function_push_button;
    QSpacerItem *vertical_spacer;

    void setupUi(QDialog *Calculator_Form)
    {
        if (Calculator_Form->objectName().isEmpty())
            Calculator_Form->setObjectName("Calculator_Form");
        Calculator_Form->resize(816, 464);
        dialog_horizontal_layout = new QHBoxLayout(Calculator_Form);
        dialog_horizontal_layout->setObjectName("dialog_horizontal_layout");
        settings_vertical_layout = new QVBoxLayout();
        settings_vertical_layout->setObjectName("settings_vertical_layout");
        window_settings_frame = new QFrame(Calculator_Form);
        window_settings_frame->setObjectName("window_settings_frame");
        window_settings_frame->setMinimumSize(QSize(350, 180));
        window_settings_frame->setMaximumSize(QSize(16777215, 180));
        window_settings_frame->setFrameShape(QFrame::StyledPanel);
        window_settings_frame->setFrameShadow(QFrame::Raised);
        y_axis_label = new QLabel(window_settings_frame);
        y_axis_label->setObjectName("y_axis_label");
        y_axis_label->setGeometry(QRect(10, 110, 50, 18));
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        y_axis_label->setFont(font);
        x_axis_label = new QLabel(window_settings_frame);
        x_axis_label->setObjectName("x_axis_label");
        x_axis_label->setGeometry(QRect(10, 40, 50, 18));
        x_axis_label->setFont(font);
        window_settings_label = new QLabel(window_settings_frame);
        window_settings_label->setObjectName("window_settings_label");
        window_settings_label->setGeometry(QRect(5, 10, 81, 18));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(true);
        window_settings_label->setFont(font1);
        horizontalLayoutWidget = new QWidget(window_settings_frame);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 60, 315, 31));
        x_axis_settings_layout = new QHBoxLayout(horizontalLayoutWidget);
        x_axis_settings_layout->setObjectName("x_axis_settings_layout");
        x_axis_settings_layout->setContentsMargins(0, 0, 0, 0);
        x_axis_enabled_check_box = new QCheckBox(horizontalLayoutWidget);
        x_axis_enabled_check_box->setObjectName("x_axis_enabled_check_box");
        x_axis_enabled_check_box->setChecked(true);
        x_axis_enabled_check_box->setTristate(false);

        x_axis_settings_layout->addWidget(x_axis_enabled_check_box);

        x_axis_markers_enabled_check_box = new QCheckBox(horizontalLayoutWidget);
        x_axis_markers_enabled_check_box->setObjectName("x_axis_markers_enabled_check_box");
        x_axis_markers_enabled_check_box->setChecked(true);
        x_axis_markers_enabled_check_box->setTristate(false);

        x_axis_settings_layout->addWidget(x_axis_markers_enabled_check_box);

        x_axis_lower_bound_line_edit = new QLineEdit(horizontalLayoutWidget);
        x_axis_lower_bound_line_edit->setObjectName("x_axis_lower_bound_line_edit");

        x_axis_settings_layout->addWidget(x_axis_lower_bound_line_edit);

        x_axis_range_label = new QLabel(horizontalLayoutWidget);
        x_axis_range_label->setObjectName("x_axis_range_label");

        x_axis_settings_layout->addWidget(x_axis_range_label);

        x_axis_upper_bound_line_edit = new QLineEdit(horizontalLayoutWidget);
        x_axis_upper_bound_line_edit->setObjectName("x_axis_upper_bound_line_edit");

        x_axis_settings_layout->addWidget(x_axis_upper_bound_line_edit);

        horizontalLayoutWidget_2 = new QWidget(window_settings_frame);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(10, 140, 314, 31));
        y_axis_settings_layout = new QHBoxLayout(horizontalLayoutWidget_2);
        y_axis_settings_layout->setObjectName("y_axis_settings_layout");
        y_axis_settings_layout->setContentsMargins(0, 0, 0, 0);
        y_axis_enabled_check_box = new QCheckBox(horizontalLayoutWidget_2);
        y_axis_enabled_check_box->setObjectName("y_axis_enabled_check_box");
        y_axis_enabled_check_box->setChecked(true);
        y_axis_enabled_check_box->setTristate(false);

        y_axis_settings_layout->addWidget(y_axis_enabled_check_box);

        y_axis_markers_enabled_check_box = new QCheckBox(horizontalLayoutWidget_2);
        y_axis_markers_enabled_check_box->setObjectName("y_axis_markers_enabled_check_box");
        y_axis_markers_enabled_check_box->setChecked(true);
        y_axis_markers_enabled_check_box->setTristate(false);

        y_axis_settings_layout->addWidget(y_axis_markers_enabled_check_box);

        y_axis_lower_bound_line_edit = new QLineEdit(horizontalLayoutWidget_2);
        y_axis_lower_bound_line_edit->setObjectName("y_axis_lower_bound_line_edit");

        y_axis_settings_layout->addWidget(y_axis_lower_bound_line_edit);

        y_axis_range_label = new QLabel(horizontalLayoutWidget_2);
        y_axis_range_label->setObjectName("y_axis_range_label");

        y_axis_settings_layout->addWidget(y_axis_range_label);

        y_axis_upper_bound_line_edit = new QLineEdit(horizontalLayoutWidget_2);
        y_axis_upper_bound_line_edit->setObjectName("y_axis_upper_bound_line_edit");

        y_axis_settings_layout->addWidget(y_axis_upper_bound_line_edit);


        settings_vertical_layout->addWidget(window_settings_frame);

        function_table_widget = new QTableWidget(Calculator_Form);
        if (function_table_widget->columnCount() < 3)
            function_table_widget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        function_table_widget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        function_table_widget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        function_table_widget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (function_table_widget->rowCount() < 5)
            function_table_widget->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        function_table_widget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        function_table_widget->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        function_table_widget->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        function_table_widget->setVerticalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        function_table_widget->setVerticalHeaderItem(4, __qtablewidgetitem7);
        function_table_widget->setObjectName("function_table_widget");
        function_table_widget->setMinimumSize(QSize(350, 170));
        function_table_widget->setMaximumSize(QSize(350, 170));
        function_table_widget->setShowGrid(true);
        function_table_widget->horizontalHeader()->setVisible(true);
        function_table_widget->verticalHeader()->setVisible(true);
        function_table_widget->verticalHeader()->setHighlightSections(true);

        settings_vertical_layout->addWidget(function_table_widget);

        button_grid_layout = new QGridLayout();
        button_grid_layout->setObjectName("button_grid_layout");
        button_grid_layout->setSizeConstraint(QLayout::SetDefaultConstraint);
        button_grid_layout->setHorizontalSpacing(6);
        reset_graph_push_button = new QPushButton(Calculator_Form);
        reset_graph_push_button->setObjectName("reset_graph_push_button");
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setUnderline(false);
        reset_graph_push_button->setFont(font2);

        button_grid_layout->addWidget(reset_graph_push_button, 2, 0, 1, 1);

        update_graph_push_button = new QPushButton(Calculator_Form);
        update_graph_push_button->setObjectName("update_graph_push_button");
        update_graph_push_button->setFont(font2);

        button_grid_layout->addWidget(update_graph_push_button, 2, 1, 1, 1);

        remove_function_push_button = new QPushButton(Calculator_Form);
        remove_function_push_button->setObjectName("remove_function_push_button");
        remove_function_push_button->setFont(font2);

        button_grid_layout->addWidget(remove_function_push_button, 1, 0, 1, 1);

        add_function_push_button = new QPushButton(Calculator_Form);
        add_function_push_button->setObjectName("add_function_push_button");
        add_function_push_button->setFont(font2);

        button_grid_layout->addWidget(add_function_push_button, 1, 1, 1, 1);


        settings_vertical_layout->addLayout(button_grid_layout);

        vertical_spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        settings_vertical_layout->addItem(vertical_spacer);


        dialog_horizontal_layout->addLayout(settings_vertical_layout);


        retranslateUi(Calculator_Form);

        QMetaObject::connectSlotsByName(Calculator_Form);
    } // setupUi

    void retranslateUi(QDialog *Calculator_Form)
    {
        Calculator_Form->setWindowTitle(QCoreApplication::translate("Calculator_Form", "Dialog", nullptr));
        y_axis_label->setText(QCoreApplication::translate("Calculator_Form", "y-axis:", nullptr));
        x_axis_label->setText(QCoreApplication::translate("Calculator_Form", "x-axis:", nullptr));
        window_settings_label->setText(QCoreApplication::translate("Calculator_Form", "Window:", nullptr));
        x_axis_enabled_check_box->setText(QCoreApplication::translate("Calculator_Form", "Enabled", nullptr));
        x_axis_markers_enabled_check_box->setText(QCoreApplication::translate("Calculator_Form", "Show Markers", nullptr));
        x_axis_lower_bound_line_edit->setText(QCoreApplication::translate("Calculator_Form", "-10", nullptr));
        x_axis_range_label->setText(QCoreApplication::translate("Calculator_Form", "\342\211\244 x \342\211\244", nullptr));
        x_axis_upper_bound_line_edit->setText(QCoreApplication::translate("Calculator_Form", "10", nullptr));
        y_axis_enabled_check_box->setText(QCoreApplication::translate("Calculator_Form", "Enabled", nullptr));
        y_axis_markers_enabled_check_box->setText(QCoreApplication::translate("Calculator_Form", "Show Markers", nullptr));
        y_axis_lower_bound_line_edit->setText(QCoreApplication::translate("Calculator_Form", "-10", nullptr));
        y_axis_range_label->setText(QCoreApplication::translate("Calculator_Form", "\342\211\244 y \342\211\244", nullptr));
        y_axis_upper_bound_line_edit->setText(QCoreApplication::translate("Calculator_Form", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem = function_table_widget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Calculator_Form", "Input", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = function_table_widget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Calculator_Form", "Output", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = function_table_widget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Calculator_Form", "Color", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = function_table_widget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Calculator_Form", "1)", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = function_table_widget->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Calculator_Form", "2)", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = function_table_widget->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("Calculator_Form", "3)", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = function_table_widget->verticalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("Calculator_Form", "4)", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = function_table_widget->verticalHeaderItem(4);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("Calculator_Form", "5)", nullptr));
        reset_graph_push_button->setText(QCoreApplication::translate("Calculator_Form", "Reset", nullptr));
        update_graph_push_button->setText(QCoreApplication::translate("Calculator_Form", "Update", nullptr));
        remove_function_push_button->setText(QCoreApplication::translate("Calculator_Form", "Remove Function", nullptr));
        add_function_push_button->setText(QCoreApplication::translate("Calculator_Form", "Add Function", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Calculator_Form: public Ui_Calculator_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATOR_FORM_H
