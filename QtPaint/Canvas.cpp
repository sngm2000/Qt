#include "Canvas.h"  
#include <QPainter>  
#include <QMouseEvent>

QColor mCanvasColor = Qt::white;

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

void Canvas::clearCanvas()
{
	mStrokes.clear();
	mLines.clear();
	mRectangles.clear();
	mCircles.clear();

	mCurrentStroke.points.clear();

	mDrawing = false;

	update();
}

void Canvas::saveCanvas()
{
	QString fileName =
		QFileDialog::getSaveFileName(
			this,
			"Save Image",
			"",
			"PNG (*.png);;JPEG (*.jpg);;Bitmap (*.bmp)");

	if (fileName.isEmpty())
		return;

	QPixmap pixmap(size());

	render(&pixmap);

	pixmap.save(fileName);
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
			case ToolType::Eraser:
			{
				mCurrentStroke.points.clear();
				mCurrentStroke.points.push_back(event->pos());

				if (mCurrentTool == ToolType::Pencil)
					mCurrentStroke.color = mCurrentColor;
				else
					mCurrentStroke.color = mCanvasColor;

				mCurrentStroke.width = mCurrentWidth;
				break;
			}

			case ToolType::Line:
			{
				mCurrentLine.start = event->pos();
				mCurrentLine.end = event->pos();

				mCurrentStroke.color = mCurrentColor;
				mCurrentLine.width = mCurrentWidth;
				break;
			}

			case ToolType::Rectangle:
			{
				mCurrentRectangle.start = event->pos();
				mCurrentRectangle.end = event->pos();

				mCurrentRectangle.color = mCurrentColor;
				mCurrentRectangle.width = mCurrentWidth;
				break;
			}

			case ToolType::Circle:
			{
				mCurrentCircle.start = event->pos();
				mCurrentCircle.end = event->pos();

				mCurrentCircle.color = mCurrentColor;
				mCurrentCircle.width = mCurrentWidth;

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
		case ToolType::Eraser:
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
			if (mDrawing)
			{
				mCurrentRectangle.end = event->pos();
				update();
			}
			break;
		}

		case ToolType::Circle:
		{
			if (mDrawing)
			{
				mCurrentCircle.end = event->pos();
				update();
			}
			break;
		}
	}
	
}  

void Canvas::mouseReleaseEvent(QMouseEvent* event)  
{  
	Q_UNUSED(event);

	if (mDrawing)
	{
		switch (mCurrentTool)
		{
		case ToolType::Pencil:
		case ToolType::Eraser:
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

		case ToolType::Rectangle:
		{
			mCurrentRectangle.end = event->pos();
			mRectangles.push_back(mCurrentRectangle);

			mDrawing = false;
			update();

			break;
		}

		case ToolType::Circle:
		{
			mCurrentCircle.end = event->pos();
			mCircles.push_back(mCurrentCircle);

			mDrawing = false;
			update();
		}

		default:
			break;
		}
	}

}

void Canvas::drawPermanentObjects(QPainter& painter)
{

	for (const auto& Line : mLines)
	{
		drawLinePreview(painter, Line);
	}

	for (const auto& Rectangle : mRectangles)
	{
		drawNormalizedRectangle(painter, Rectangle);
	}

	for (const auto& circle : mCircles)
	{
		drawCircle(painter, circle);
	}

	for (const auto& stroke : mStrokes)
	{
		drawStroke(painter, stroke);
	}
}

void Canvas::drawCurrentTool(QPainter& painter)
{
	if (!mDrawing)
		return;

	switch (mCurrentTool)
	{
	case ToolType::Pencil:
	case ToolType::Eraser:
		drawStroke(painter, mCurrentStroke);
		break;

	case ToolType::Line:
		drawLinePreview(painter, mCurrentLine);
		break;

	case ToolType::Rectangle:
		drawNormalizedRectangle(painter, mCurrentRectangle);
		break;

	case ToolType::Circle:
		drawCircle(painter, mCurrentCircle);
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

void Canvas::drawNormalizedRectangle(QPainter& painter,const Rectangle& rect)
{
	QPen pen;

	pen.setColor(rect.color);
	pen.setWidth(rect.width);

	painter.setPen(pen);

	QRect rectangle(rect.start, rect.end);

	painter.drawRect(rectangle.normalized());
}

void Canvas::drawCircle(QPainter& painter, const Circle& circle)
{
	QPen pen;

	pen.setColor(circle.color);
	pen.setWidth(circle.width);

	painter.setPen(pen);

	int dx = circle.end.x() - circle.start.x();
	int dy = circle.end.y() - circle.start.y();

	int radius = std::sqrt(dx * dx + dy * dy);

	QRect rect(
		circle.start.x() - radius,
		circle.start.y() - radius,
		radius * 2,
		radius * 2);

	painter.drawEllipse(rect);
}

