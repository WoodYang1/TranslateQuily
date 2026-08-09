#include "dragwidget.h"
DragWidget::DragWidget(QWidget *parent)
    : QWidget{parent}
{}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        _isDragging = true;
        //激素按鼠标所在位置相对于窗口左上角的偏移量,鼠标相对于屏幕所在位置-窗口左上角相对于屏幕所在位置 就是偏移量
        _dragStartPos = event->globalPosition().toPoint() - frameGeometry().topLeft();
    }
    QWidget::mousePressEvent(event);
}

void DragWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (_isDragging) {
        //移动就是新的位置-偏移量
        move(event->globalPosition().toPoint() - _dragStartPos);
    }
    QWidget::mouseMoveEvent(event);
}

void DragWidget::mouseReleaseEvent(QMouseEvent *event)
{
    _isDragging = false;
    QWidget::mouseReleaseEvent(event);
}
