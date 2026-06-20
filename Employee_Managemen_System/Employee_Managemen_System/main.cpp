#include "Employee_Managemen_System.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Employee_Managemen_System window;
    window.show();
    return app.exec();
}
