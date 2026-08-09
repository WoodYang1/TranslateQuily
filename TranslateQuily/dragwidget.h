#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
/*********************************************************
 * @file    dragwidget.h
 * @brief   当作移动窗口的基类，继承者可以通过鼠标拖动来移动窗口
 *
 * @author  木杨
 * @date    2026/08/08
 * @history
 *********************************************************/
class DragWidget : public QWidget
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent* e)override;
    void mouseMoveEvent(QMouseEvent* e)override;
    void mouseReleaseEvent(QMouseEvent* e)override;
public:
    explicit DragWidget(QWidget *parent = nullptr);
private:

    bool _isDragging = false;
    QPoint _dragStartPos;
signals:
};

#endif // DRAGWIDGET_H
