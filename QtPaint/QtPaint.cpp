#include "QtPaint.h"

QtPaint::QtPaint(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    statusBar()->showMessage("Ready : QtPaint by Sangam");

    mCanvas = new Canvas(this);
    setCentralWidget(mCanvas);

    ui.mainToolBar->setIconSize(QSize(32, 32));
    ui.mainToolBar->setMovable(false);
    ui.mainToolBar->setFloatable(false);
}

QtPaint::~QtPaint()
{

}

