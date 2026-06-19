#include "EmployeeForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    EmployeeForm window;
    window.show();
    return app.exec();
}
