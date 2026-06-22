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
};

