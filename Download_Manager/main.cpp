#include "Download_Manager.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Download_Manager window;
    window.show();
    return app.exec();
}
