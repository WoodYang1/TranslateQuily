#include "widget.h"
#include "ui_widget.h"
#include <QCursor>
#include <QElapsedTimer>
#include "httpclient.h"
#include "hotkeymanager.h"
#include "settingdata.h"
#include "global.h"
Widget::Widget(QWidget *parent)
    : DragWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //取消标题栏，永久置顶
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    this->setStyleSheet(
        "background-color: #1a1a1a;"
        "border: 1px solid #333;"
        );
    QPixmap pixmap(":/icon/Icon/Right.png");  // 加载图标
    QPixmap scaled = pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_Right->setPixmap(scaled);

    bindCopyTriggerTranslate();

    _trayManager = new TrayManager(this);
    connect(_trayManager,&TrayManager::quitApp,this,&QCoreApplication::quit);
    connect(&HotkeyManager::instance(),&HotkeyManager::hotkey_hide_trigger,this,[this](){
        hide();
    });
}

//确保显示的时候才能使用隐藏和翻译快捷键
void Widget::showEvent(QShowEvent *event)
{
    if(HotkeyManager::instance().hotkey_hide_isRegistered()){
        qDebug()<<"已经注册";
        return;
    }
    QWidget::showEvent(event);
    HotkeyManager::instance().hotkey_hide_setRegistered(true);
}

void Widget::hideEvent(QHideEvent *event)
{
    // 1. 调用父类，保证正常隐藏
    QWidget::hideEvent(event);
    // 2. 注销快捷键
    HotkeyManager::instance().hotkey_hide_setRegistered(false);

}
Widget::~Widget()
{
    delete ui;
}

void Widget::bindCopyTriggerTranslate()
{
    //剪贴板数据改变 触发翻译
    _clipboard = QGuiApplication::clipboard();
    connect(_clipboard, &QClipboard::dataChanged, this, [this]() {

        if(HotkeyManager::instance().hotkey_hide_isRegistered()){
            qDebug()<<"按键已被注册，不显示界面,也不翻译";
            return;
        }
        if(!_trayManager->wantTranslate()){
            qDebug()<<"复制翻译为关闭状态";
            return;
        }
        if(_hasCopyHistory){
            qint64 elapsed = _lastCopyTime.elapsed();
            if(elapsed < 400){
                QString text = _clipboard->text();
                if (!text.isEmpty()) {
                    qDebug() << "捕获到剪贴板文本:" << text;
                    QString goal = formatText(text);
                    // 调用你的翻译函数
                    HttpClient::instance()->translate(goal,SettingData::instance().getTransLanguageValue(SettingData::instance().getDefaultCopyTransLanguageKey_from()),
                                                      SettingData::instance().getTransLanguageValue(SettingData::instance().getDefaultCopyTransLanguageKey_to()),
                                                      std::bind(&Widget::handleTranslate,this,std::placeholders::_1,std::placeholders::_2));
                    qDebug()<<"from"<<SettingData::instance().getTransLanguageValue(SettingData::instance().getDefaultCopyTransLanguageKey_from())
                             <<"to"<<SettingData::instance().getTransLanguageValue(SettingData::instance().getDefaultCopyTransLanguageKey_to());
                }
            }
            //触发翻译 重置状态
            _lastCopyTime.invalidate();
            _hasCopyHistory = false;
            return;
        }
        _hasCopyHistory=true;
        _lastCopyTime.restart();
    });
}

void Widget::handleTranslate(bool success, const QString& result)
{
    ui->textEdit_from->clear();
    ui->textEdit_to->clear();
    if (success) {
        ui->textEdit_from->setPlainText(_clipboard->text());
        ui->textEdit_to->setPlainText(result);
        showWidgetFromCursor();
        qDebug() << "翻译结果:" << result;
    } else {
        ui->textEdit_to->setPlainText(result);
        qDebug() << "翻译失败:" << result;
    }
}

void Widget::showWidgetFromCursor()
{
    if(HotkeyManager::instance().hotkey_hide_isRegistered()){
        qDebug()<<"按键已被注册，不显示界面";
        return;
    }
    //45 90
    QPoint pos = QCursor::pos();
    pos.setX(pos.x()+20);
    pos.setY(pos.y()+20);
    this->move(pos);
    this->raise();  // 把当前 Widget 提升到父窗口的最上层
    this->activateWindow();
    this->show();

}
