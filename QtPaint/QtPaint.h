#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtPaint.h"

#include "Canvas.h"

class QtPaint : public QMainWindow
{
    Q_OBJECT

public:
    QtPaint(QWidget *parent = nullptr);
    ~QtPaint();

private:
    Ui::QtPaintClass ui;
    Canvas* mCanvas;

private slots:
    void NewClicked();
    void PencilClicked();
    void LineClicked();
    void RectangleClicked();
    void CircleClicked();
    void clearClicked();
    void OpenClicked();
    void SaveClicked();
};

