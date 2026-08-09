#include "translateinputwidget.h"
#include "ui_translateinputwidget.h"
#include "httpclient.h"
#include "hotkeymanager.h"
#include "settingdata.h"
#include "global.h"
TranslateInputWidget::TranslateInputWidget(QWidget *parent)
    : DragWidget(parent)
    , ui(new Ui::TranslateInputWidget)
{
    ui->setupUi(this);
    //取消标题栏，永久置顶
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    // 把 key（显示文本）添加到 ComboBox
    for (const QString& key : SettingData::instance().getTransLanguageKeys()) {
        ui->comboBox_from->addItem(key);
        ui->comboBox_to->addItem(key);
    }

    ui->comboBox_from->setCurrentText(SettingData::instance().getDefaultTransLanguageKey_onTransWidget_from());
    ui->comboBox_to->setCurrentText(SettingData::instance().getDefaultTransLanguageKey_onTransWidget_to());
    bindHotkey();

}
//确保显示的时候才能使用隐藏和翻译快捷键，显示界面的时候 重新加载语言转换源和目标
void TranslateInputWidget::showEvent(QShowEvent *event)
{
    if(HotkeyManager::instance().hotkey_hide_isRegistered()){
        qDebug()<<"已经注册";
        return;
    }
    QWidget::showEvent(event);
    HotkeyManager::instance().hotkey_hide_setRegistered(true);
    HotkeyManager::instance().hotkey_translate_setRegistered(true);
    ui->comboBox_from->setCurrentText(SettingData::instance().getDefaultTransLanguageKey_onTransWidget_from());
    ui->comboBox_to->setCurrentText(SettingData::instance().getDefaultTransLanguageKey_onTransWidget_to());
    ui->plainTextEdit_from->setFocus();

}

void TranslateInputWidget::hideEvent(QHideEvent *event)
{
    // 1. 调用父类，保证正常隐藏
    QWidget::hideEvent(event);
    // 2. 注销快捷键
    HotkeyManager::instance().hotkey_hide_setRegistered(false);
    HotkeyManager::instance().hotkey_translate_setRegistered(false);
    ui->plainTextEdit_from->clear();
    ui->plainTextEdit_to->clear();

}



TranslateInputWidget::~TranslateInputWidget()
{
    delete ui;
}


void TranslateInputWidget::handleTranslate(bool success, const QString& result)
{
    ui->plainTextEdit_to->clear();
    if (success) {
        ui->plainTextEdit_to->setPlainText(result);
        qDebug() << "翻译结果:" << result;
    } else {
        ui->plainTextEdit_to->setPlainText(result);
        qDebug() << "翻译失败:" << result;
    }
}

void TranslateInputWidget::bindHotkey()
{
    //绑定快捷键
    connect(&HotkeyManager::instance(),&HotkeyManager::_hotkey_showTranslateInputWidget_trigger,this,[this](){
        if(HotkeyManager::instance().hotkey_hide_isRegistered()){
            qDebug()<<"按键已被注册，不显示界面";
            return;
        }
        this->raise();
        this->activateWindow();
        show();
    });
    connect(&HotkeyManager::instance(),&HotkeyManager::hotkey_hide_trigger,this,[this](){
        hide();
    });
    connect(&HotkeyManager::instance(),&HotkeyManager::hotkey_translate_trigger,this,[this](){
        QString goal = formatText(ui->plainTextEdit_from->toPlainText());
        HttpClient::instance()->translate(goal,
                                          SettingData::instance().getTransLanguageValue(ui->comboBox_from->currentText()),
                                          SettingData::instance().getTransLanguageValue(ui->comboBox_to->currentText()),
                                          std::bind(&TranslateInputWidget::handleTranslate,this,std::placeholders::_1,std::placeholders::_2));
    });
}
