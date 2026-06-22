#pragma once

#include <QWidget>
#include <QPoint>
#include <QVector>

enum class ToolType
{
    Pencil,
    Line,
    Rectangle,
    Circle,
    Eraser
};

struct Shape
{
    ToolType tool;

    QPoint start;

    QPoint end;

    QColor color;

    int width;
};

class Canvas  : public QWidget
{
	Q_OBJECT

public:
	explicit Canvas(QWidget* parent = nullptr);
	~Canvas();


protected:
	void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:

    QVector<QPoint> mPoints;

    bool mDrawing = false;

};

