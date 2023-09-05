#include "calculator_form.hpp"

#include <QApplication>

/**
 * Main function.
 *
 * @param argc Number of command line arguments.
 * @param argv List of command line arguments.
 */
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    Calculator_Form ui;
    ui.show();

    return app.exec();
}
