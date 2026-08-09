#include "setwidget.h"
#include "ui_setwidget.h"
#include <QCloseEvent>
#include "settingdata.h"
void SetWidget::closeEvent(QCloseEvent *e)
{
    hide();
    e->ignore();
}

SetWidget::SetWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SetWidget)
{
    ui->setupUi(this);
    _hotkeyEdits = {
        {HotkeyName::StateChange, ui->keySequenceEdit_stateChange},
        {HotkeyName::ShowTranslateInputWidget, ui->keySequenceEdit_showTranslateWidget}

    };
    loadWidgetData();

    connect(ui->keySequenceEdit_stateChange,&QKeySequenceEdit::keySequenceChanged,this,[this](const QKeySequence &keySequence){
        _recordHotKeySetting.insert(HotkeyName::StateChange,keySequence.toString());
    });
    connect(ui->keySequenceEdit_showTranslateWidget,&QKeySequenceEdit::keySequenceChanged,this,[this](const QKeySequence &keySequence){
        _recordHotKeySetting.insert(HotkeyName::ShowTranslateInputWidget,keySequence.toString());
    });

}

SetWidget::~SetWidget()
{
    delete ui;
}

void SetWidget::loadWidgetData()
{
    //加载快捷键数据
    for(auto &key : _hotkeyEdits.keys()){
        QString hotkey = SettingData::instance().getHotkey(key);
        _hotkeyEdits[key]->setKeySequence(QKeySequence(hotkey));
    }
    //加载key和appid
    ui->lineEdit_ApiKey->setText(SettingData::instance().getApiKey());
    ui->lineEdit_AppID->setText(SettingData::instance().getAppId());

    //加载语言项
    for(const auto & key : SettingData::instance().getTransLanguageKeys()){
        ui->comboBox_TransWidgetFrom->addItem(key);
        ui->comboBox_TransWidgetTo->addItem(key);
    }
    //加载语言项
    for(const auto & key : SettingData::instance().getTransLanguageKeys()){
        qDebug()<<key;
        ui->comboBox_copyTranslateFrom->addItem(key);
        ui->comboBox_copyTranslateTo->addItem(key);
    }
    ui->comboBox_TransWidgetFrom->setCurrentText(SettingData::instance().getDefaultTransLanguageKey_onTransWidget_from());
    ui->comboBox_TransWidgetTo->setCurrentText(SettingData::instance().getDefaultTransLanguageKey_onTransWidget_to());

    ui->comboBox_copyTranslateFrom->setCurrentText(SettingData::instance().getDefaultCopyTransLanguageKey_from());
    ui->comboBox_copyTranslateTo->setCurrentText(SettingData::instance().getDefaultCopyTransLanguageKey_to());

}

//确定,保存数据
void SetWidget::on_pushButton_clicked()
{
    //保存快捷键数据
    for(const auto &key : _recordHotKeySetting.keys()){
        HotkeyManager::instance().setHotKey(key,_recordHotKeySetting.value(key));
    }
    //保存key id
    SettingData::instance().setApiKey(ui->lineEdit_ApiKey->text());
    SettingData::instance().setAppId(ui->lineEdit_AppID->text());
    //保存默认语言翻译源和目标
    SettingData::instance().setDefaultTransLanguageKey_onTransWidget_from(ui->comboBox_TransWidgetFrom->currentText());
    SettingData::instance().setDefaultTransLanguageKey_onTransWidget_to(ui->comboBox_TransWidgetTo->currentText());

    SettingData::instance().setDefaultCopyTransLanguageKey_from(ui->comboBox_copyTranslateFrom->currentText());
    SettingData::instance().setDefaultCopyTransLanguageKey_to(ui->comboBox_copyTranslateTo->currentText());

    SettingData::instance().save();
    hide();
}


void SetWidget::on_pushButton_2_clicked()
{
    _recordHotKeySetting.clear();
    hide();
}

