#ifndef SETWIDGET_H
#define SETWIDGET_H

#include <QWidget>
#include "hotkeymanager.h"
#include <QKeySequenceEdit>
/*********************************************************
 * @file    setwidget.h
 * @brief   设置界面，从SettingData读取配置信息，确定按钮按下则向SettingData写入部分配置并保存
 * @author  木杨
 * @date    2026/08/08
 * @history
 *********************************************************/
namespace Ui {
class SetWidget;
}

class SetWidget : public QWidget
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *e) override;
public:
    explicit SetWidget(QWidget *parent = nullptr);
    ~SetWidget();
    //加载界面数据
    void loadWidgetData();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SetWidget *ui;
    QMap<HotkeyName,QString> _recordHotKeySetting;
    QMap<HotkeyName, QKeySequenceEdit*> _hotkeyEdits;

};

#endif // SETWIDGET_H
