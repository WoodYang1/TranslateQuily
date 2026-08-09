#include "traymanager.h"
#include "hotkeymanager.h"
TrayManager::TrayManager(QObject *parent)
    : QObject{parent},_b_wantTranslate(false)
{
    _setWidget = std::make_shared<SetWidget>(nullptr);
    _trayIcon = new QSystemTrayIcon(this);
    _trayIcon->setIcon(QIcon(":/icon/Icon/Translate_Stop.png"));
    _trayIcon->setToolTip("翻译工具\nF1:切换翻译状态\nF2打开翻译界面-回车开始翻译\n连续复制两次-翻译复制文本");
    _trayMenu = new QMenu();
    trayMenuInit(_trayMenu);
    _trayIcon->setContextMenu(_trayMenu);
    _trayIcon->show();


}

bool TrayManager::wantTranslate()
{
    return _b_wantTranslate;
}

void TrayManager::trayMenuInit(QMenu *_trayMenu)
{
    _trayMenu->addSeparator();
    QAction* autoTranslateAction = new QAction("自动翻译", this);
    autoTranslateAction->setCheckable(true);
    autoTranslateAction->setChecked(_b_wantTranslate);

    connect(autoTranslateAction, &QAction::toggled, this, [this](bool checked) {
        qDebug() << "自动翻译状态:" << checked;
        _b_wantTranslate=checked;
        if(_b_wantTranslate){
            _trayIcon->setIcon(QIcon(":/icon/Icon/Translate_Start.png"));
        }else{
            _trayIcon->setIcon(QIcon(":/icon/Icon/Translate_Stop.png"));
        }
    });
    connect(&HotkeyManager::instance(),&HotkeyManager::hotkey_stateChange_trigger,this,[autoTranslateAction](){
        autoTranslateAction->toggle();
    });

    _trayMenu->addSeparator();

    QAction* showSetWidgetAction = new QAction("设置", _trayMenu);
    connect(showSetWidgetAction, &QAction::triggered, _setWidget.get(), &SetWidget::show);
    QAction* quitAction = new QAction("退出", _trayMenu);
    connect(quitAction, &QAction::triggered, this, &TrayManager::quitApp);

    // _trayMenu->addAction(showAction);
    //_trayMenu->addAction(hideAction);
    _trayMenu->addAction(autoTranslateAction);
    _trayMenu->addAction(showSetWidgetAction);
    _trayMenu->addAction(quitAction);
}
