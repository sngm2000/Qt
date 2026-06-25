#include "QtPaint.h"
#include <QActionGroup>
#include <QMessageBox>

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

    ui.actionPencil->setCheckable(true);
    ui.actionLine->setCheckable(true);
    ui.actionRectangle->setCheckable(true);
    ui.actionCircle->setCheckable(true);
    ui.actionClear->setCheckable(true);
    ui.actionPencil->setChecked(true);

    QActionGroup* toolGroup = new QActionGroup(this);
    toolGroup->addAction(ui.actionPencil);
    toolGroup->addAction(ui.actionLine);
    toolGroup->addAction(ui.actionRectangle);
    toolGroup->addAction(ui.actionCircle);
    toolGroup->addAction(ui.actionClear);

    toolGroup->setExclusive(true);

    

    connect(ui.actionNew, &QAction::triggered, this, &QtPaint::NewClicked);
    connect(ui.actionPencil, &QAction::triggered, this, &QtPaint::PencilClicked);
    connect(ui.actionLine, &QAction::triggered, this, &QtPaint::LineClicked);
    connect(ui.actionRectangle, &QAction::triggered, this, &QtPaint::RectangleClicked);
    connect(ui.actionCircle, &QAction::triggered, this, &QtPaint::CircleClicked);
    connect(ui.actionClear, &QAction::triggered, this, &QtPaint::clearClicked);
    connect(ui.actionOpen, &QAction::triggered, this, &QtPaint::OpenClicked);
    connect(ui.actionSave, &QAction::triggered, this, &QtPaint::SaveClicked);
    connect(ui.actionExit, &QAction::triggered, this, &QWidget::close);
}

QtPaint::~QtPaint()
{

}

void QtPaint::NewClicked()
{
    mCanvas->clearCanvas();
}

void QtPaint::PencilClicked()
{
    ui.actionPencil->setChecked(true);
    mCanvas->setCurrentTool(ToolType::Pencil);
}

void QtPaint::LineClicked()
{
    ui.actionLine->setChecked(true);
    mCanvas->setCurrentTool(ToolType::Line);
}

void QtPaint::RectangleClicked()
{
    ui.actionRectangle->setChecked(true);
    mCanvas->setCurrentTool(ToolType::Rectangle);
}

void QtPaint::CircleClicked()
{
    ui.actionCircle->setChecked(true);
    mCanvas->setCurrentTool(ToolType::Circle);
}

void QtPaint::clearClicked()
{
    ui.actionClear->setChecked(true);
    mCanvas->setCurrentTool(ToolType::Eraser);
}

void QtPaint::OpenClicked()
{
#include <QMessageBox>

    QMessageBox::information(
        this,
        "Information",
        "Comming Soon.."
    );
}

void QtPaint::SaveClicked()
{
    mCanvas->saveCanvas();
}

