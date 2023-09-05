#pragma once
#include <QPushButton>
#include <QColor>

class Color_Picker_Widget : public QPushButton
{
public:
    Color_Picker_Widget(QWidget* parent = nullptr);

private:
    QColor color;
};
