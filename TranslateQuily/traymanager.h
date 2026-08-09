#ifndef TRAYMANAGER_H
#define TRAYMANAGER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <memory>
#include "setwidget.h"
/*********************************************************
 * @file    traymanager.h
 * @brief   管理托盘图标
 *
 * @author  木杨
 * @date    2026/08/08
 * @history
 *********************************************************/
class TrayManager : public QObject
{
    Q_OBJECT
public:
    explicit TrayManager(QObject *parent = nullptr);
    bool wantTranslate();
private:
    void trayMenuInit(QMenu* _trayMenu);
signals:
    void showMainWindow();
    void hideMainWindow();
    void quitApp();

private:
    QSystemTrayIcon* _trayIcon;
    QMenu* _trayMenu;
    bool _b_wantTranslate;
    std::shared_ptr<SetWidget> _setWidget;

signals:
};

#endif // TRAYMANAGER_H
