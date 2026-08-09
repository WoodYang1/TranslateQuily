#ifndef TRANSLATEINPUTWIDGET_H
#define TRANSLATEINPUTWIDGET_H

#include <QWidget>
#include "dragwidget.h"
/*********************************************************
 * @file    translateinputwidget.h
 * @brief   根据界面显示的数据来进行翻译 - 如果widgetset,界面显示的数据从settingData获取
 *          通过HotkeyManager来设置快捷键
 *
 *
 * @author  木杨
 * @date    2026/08/08
 * @history
 *********************************************************/

namespace Ui {
class TranslateInputWidget;
}

class TranslateInputWidget : public DragWidget
{
    Q_OBJECT
protected:
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;
public:
    explicit TranslateInputWidget(QWidget *parent = nullptr);
    ~TranslateInputWidget();
private:
    void handleTranslate(bool success, const QString& result);
    //绑定快捷键
    void bindHotkey();

private:
    Ui::TranslateInputWidget *ui;
};

#endif // TRANSLATEINPUTWIDGET_H
