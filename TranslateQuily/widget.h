#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QClipboard>
#include <QGuiApplication>
#include "traymanager.h"
#include "dragwidget.h"
QT_BEGIN_NAMESPACE
/*********************************************************
 * @file    widget.h
 * @brief   通过计时器达成两次连续复制 开始翻译并显示界面
 *
 * @author  木杨
 * @date    2026/08/08
 * @history
 *********************************************************/
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public DragWidget
{
    Q_OBJECT
protected:
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    void bindCopyTriggerTranslate();
    void handleTranslate(bool success, const QString& result);
    void showWidgetFromCursor();
private:
    Ui::Widget *ui;

    QClipboard* _clipboard;
    TrayManager* _trayManager;
    QElapsedTimer _lastCopyTime;  // 计时器
    bool _hasCopyHistory = false; // 是否有上一次复制记录
};
#endif // WIDGET_H
