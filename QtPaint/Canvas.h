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

struct Stroke
{
    QVector<QPoint> points;
    QColor color;
    int width;
};

struct Line
{
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

    void setCurrentTool(ToolType tool);


protected:
	void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:

    QVector<Stroke> mStrokes;
    Stroke mCurrentStroke;

    QVector<Line> mLines;
    Line mCurrentLine;

    QColor mCurrentColor;
    int mCurrentWidth;

    ToolType mCurrentTool = ToolType::Pencil;

    bool mDrawing = false;

    void drawPermanentObjects(QPainter& painter);
    void drawCurrentTool(QPainter& painter);
    void drawStroke(QPainter& painter, const Stroke& stroke);
    void drawLinePreview(QPainter& painter, const Line& line);
};

