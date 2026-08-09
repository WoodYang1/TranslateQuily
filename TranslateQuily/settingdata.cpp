#include "settingdata.h"
#include <QSettings>
SettingData::SettingData(QObject *parent)
    : QObject{parent},_defaultTransLanguageKey_onTransWidget_from{"简体中文"},_defaultTransLanguageKey_onTransWidget_to{"英文"}
{
}

SettingData &SettingData::instance()
{
    static SettingData instance;
    return instance;
}

void SettingData::save()
{
    //保存快捷键方案
    QSettings settings("config.ini",QSettings::IniFormat);
    for(const auto &key : _hotkeys.keys()){
        settings.setValue(HotkeyManager::instance().hotkeyNameToQString(key),_hotkeys.value(key));
    }
    //保存key与id
    settings.setValue("apiKey",_apiKey);
    settings.setValue("appId",_appId);

    //保存默认语言转换项
    settings.setValue("defaultTransLanguageKey_onTransWidget_from",_defaultTransLanguageKey_onTransWidget_from);
    settings.setValue("defaultTransLanguageKey_onTransWidget_to",_defaultTransLanguageKey_onTransWidget_to);

    settings.setValue("defaultCopyTransLanguageKey_from",_defaultCopyTransLanguageKey_from);
    settings.setValue("defaultCopyTransLanguageKey_to",_defaultCopyTransLanguageKey_to);
}
void SettingData::load()
{
    //加载快捷键为用户配置的方案
    QSettings settings("config.ini",QSettings::IniFormat);
    for(const auto &key : _hotkeys.keys()){
        QString hotKey = settings.value(HotkeyManager::instance().hotkeyNameToQString(key)).toString();
        if(hotKey != ""){
            _hotkeys[key] = hotKey;
            HotkeyManager::instance().updateHotKey(key);
        }
    }
    //加载apiKey，appId为用户配置方案
    _apiKey = settings.value("apiKey").toString();
    _appId = settings.value("appId").toString();
    //加载默认语言转换项
    _defaultTransLanguageKey_onTransWidget_from = settings.value("defaultTransLanguageKey_onTransWidget_from","简体中文").toString();
    _defaultTransLanguageKey_onTransWidget_to = settings.value("defaultTransLanguageKey_onTransWidget_to","英文").toString();

    _defaultCopyTransLanguageKey_from = settings.value("defaultCopyTransLanguageKey_from","英文").toString();
    _defaultCopyTransLanguageKey_to = settings.value("defaultCopyTransLanguageKey_to","简体中文").toString();

}

void SettingData::saveHotkeyData(HotkeyName keyName, QString keyValue)
{
    _hotkeys[keyName] = keyValue;
}

QString SettingData::getHotkey(const HotkeyName& keyName)
{
    return _hotkeys[keyName];
}

QString SettingData::getApiKey()
{
    return _apiKey;
}
QString SettingData::getAppId(){
    return _appId;
}
void SettingData::setApiKey(QString apiKey){
    _apiKey = apiKey;
}
void SettingData::setAppId(QString appId){
    _appId = appId;
}

QList<QString> SettingData::getTransLanguageKeys()
{
    return _transLanguage.keys();
}


QString SettingData::getTransLanguageValue(const QString &key)const{
    return _transLanguage.value(key);
}

QString SettingData::getTransLanguageValue(const QString &key)
{
    return _transLanguage.value(key);
}

QString SettingData::getDefaultTransLanguageKey_onTransWidget_from()
{
    return _defaultTransLanguageKey_onTransWidget_from;
}

QString SettingData::getDefaultTransLanguageKey_onTransWidget_to()
{
    return _defaultTransLanguageKey_onTransWidget_to;
}

QString SettingData::getDefaultCopyTransLanguageKey_from(){
    return _defaultCopyTransLanguageKey_from;
}

QString SettingData::getDefaultCopyTransLanguageKey_to(){
    return _defaultCopyTransLanguageKey_to;
}

void SettingData::setDefaultCopyTransLanguageKey_from(const QString &from){
    _defaultCopyTransLanguageKey_from = from;
}

void SettingData::setDefaultCopyTransLanguageKey_to(const QString &to){
    _defaultCopyTransLanguageKey_to = to;
}

void SettingData::setDefaultTransLanguageKey_onTransWidget_from(const QString &from)
{
    _defaultTransLanguageKey_onTransWidget_from = from;
}

void SettingData::setDefaultTransLanguageKey_onTransWidget_to(const QString &to)
{
    _defaultTransLanguageKey_onTransWidget_to = to;
}
QList<HotkeyName> SettingData::getHotkeyNames()
{
    return _hotkeys.keys();
}
