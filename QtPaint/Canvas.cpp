#include "Canvas.h"  
#include <QPainter>  
#include <QMouseEvent>

Canvas::Canvas(QWidget *parent)  
: QWidget(parent)  
{  
setAutoFillBackground(true);  

QPalette pal = palette();  

pal.setColor(QPalette::Window, Qt::white);  

setPalette(pal);  
}  

Canvas::~Canvas()  
{}  

void Canvas::paintEvent(QPaintEvent * event)  
{  
   QWidget::paintEvent(event);  
   QPainter painter(this);

}

void Canvas::mousePressEvent(QMouseEvent* event)  
{  
	mDrawing = true;  
	mPoints.push_back(event->pos());  
}  

void Canvas::mouseMoveEvent(QMouseEvent* event)  
{  
	mPoints.push_back(event->pos());
	update();
}  

void Canvas::mouseReleaseEvent(QMouseEvent* event)  
{  
	mDrawing = false;
}
