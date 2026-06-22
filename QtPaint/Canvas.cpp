#include "Canvas.h"  
#include <QPainter>  
#include <QMouseEvent>

Canvas::Canvas(QWidget *parent)  
: QWidget(parent)  
{  
	setAutoFillBackground(true);

	mCurrentColor = Qt::black;
	mCurrentWidth = 5;

	QPalette pal = palette();  

	pal.setColor(QPalette::Window, Qt::white);  

	setPalette(pal);  
}  

Canvas::~Canvas()  
{}

void Canvas::setCurrentTool(ToolType tool)
{
	mCurrentTool = tool;
}

void Canvas::paintEvent(QPaintEvent * event)  
{  
   QWidget::paintEvent(event);  
   QPainter painter(this);

   drawPermanentObjects(painter);

   drawCurrentTool(painter);

}

void Canvas::mousePressEvent(QMouseEvent* event)  
{  
	if (event->button() == Qt::LeftButton)
	{
		switch (mCurrentTool)
		{
			case ToolType::Pencil:
				mCurrentStroke.points.clear();
				mCurrentStroke.points.push_back(event->pos());
				mCurrentStroke.color = mCurrentColor;
				mCurrentStroke.width = mCurrentWidth;
				break;

			case ToolType::Line:
			{
				mCurrentLine.start = event->pos();
				mCurrentLine.end = event->pos();

				mCurrentLine.color = mCurrentColor;
				mCurrentLine.width = mCurrentWidth;
				break;
			}

			case ToolType::Rectangle:
			{
				// Future implementation
				break;
			}

			case ToolType::Circle:
			{
				// Future implementation
				break;
			}

			case ToolType::Eraser:
			{
				// Future implementation
				break;
			}

		}

		mDrawing = true;
	}
}  

void Canvas::mouseMoveEvent(QMouseEvent* event)  
{  
	switch (mCurrentTool)
	{
		case ToolType::Pencil:
		{
			if (mDrawing)
			{
				mCurrentStroke.points.push_back(event->pos());
				update();
			}
			break;
		}

		case ToolType::Line:
		{
			if (mDrawing)
			{
				mCurrentLine.end = event->pos();
				update();
			}
			break;
		}

		case ToolType::Rectangle:
		{
			// Future implementation
			break;
		}

		case ToolType::Circle:
		{
			// Future implementation
			break;
		}

		case ToolType::Eraser:
		{
			// Future implementation
			break;
		}
	}
	
}  

void Canvas::mouseReleaseEvent(QMouseEvent* event)  
{  
	Q_UNUSED(event);

	switch (mCurrentTool)
	{
	case ToolType::Pencil:
	{
		if (!mCurrentStroke.points.isEmpty())
		{
			mStrokes.push_back(mCurrentStroke);
		}

		mDrawing = false;
		update();

		break;
	}

	case ToolType::Line:
	{
		mCurrentLine.end = event->pos();
		mLines.push_back(mCurrentLine);

		mDrawing = false;
		update();

		break;
	}

	default:
		break;
	}
}

void Canvas::drawPermanentObjects(QPainter& painter)
{
	for (const auto& stroke : mStrokes)
	{
		drawStroke(painter, stroke);
	}

	for (const auto& Line : mLines)
	{
		drawLinePreview(painter, Line);
	}
}

void Canvas::drawCurrentTool(QPainter& painter)
{
	if (!mDrawing)
		return;

	switch (mCurrentTool)
	{
	case ToolType::Pencil:
		drawStroke(painter, mCurrentStroke);
		break;

	case ToolType::Line:
		drawLinePreview(painter, mCurrentLine);
		break;

	case ToolType::Rectangle:
		//drawRectanglePreview(painter);
		break;

	case ToolType::Circle:
		//drawCirclePreview(painter);
		break;

	default:
		break;
	}
}

void Canvas::drawStroke(QPainter& painter, const Stroke& stroke)
{
	QPen pen;
	pen.setColor(stroke.color);
	pen.setWidth(stroke.width);

	painter.setPen(pen);

	for (int i = 0; i < stroke.points.size() - 1; i++)
	{
		painter.drawLine(stroke.points[i],
			stroke.points[i + 1]);
	}
}

void Canvas::drawLinePreview(QPainter& painter, const Line& line)
{
	QPen pen;

	pen.setColor(line.color);
	pen.setWidth(line.width);

	painter.setPen(pen);

	painter.drawLine(line.start, line.end);
}
