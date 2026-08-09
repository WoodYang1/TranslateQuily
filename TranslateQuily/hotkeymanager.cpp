#include "hotkeymanager.h"
#include "settingdata.h"
HotkeyManager::HotkeyManager(QObject *parent)
    : QObject{parent}
{
    _hotkey_hide = new QHotkey(this);
    _hotkey_showTranslateInputWidget = new QHotkey(this);
    _hotkey_stateChange = new QHotkey(this);
    _hotkey_translate = new QHotkey(this);

    for(auto & keyname : SettingData::instance().getHotkeyNames()){
        updateHotKey(keyname);
    }
    connect(_hotkey_stateChange,&QHotkey::activated,this,[this](){
        emit hotkey_stateChange_trigger();
    });
    connect(_hotkey_showTranslateInputWidget,&QHotkey::activated,this,[this](){
        emit _hotkey_showTranslateInputWidget_trigger();
    });
    connect(_hotkey_hide,&QHotkey::activated,this,[this](){
        emit hotkey_hide_trigger();
    });
    connect(_hotkey_translate,&QHotkey::activated,this,[this](){
        emit hotkey_translate_trigger();
    });
}

HotkeyManager &HotkeyManager::instance()
{
    static HotkeyManager instance;
    return instance;
}

void HotkeyManager::setHotKey(const HotkeyName keyName, const QString keyValue)
{
    SettingData::instance().saveHotkeyData(keyName,keyValue);
    updateHotKey(keyName);

}

void HotkeyManager::updateHotKey(const HotkeyName hotkey)
{
    switch (hotkey) {

    case HotkeyName::ShowTranslateInputWidget:
        // 注销
        _hotkey_showTranslateInputWidget->setRegistered(false);
        // 设置新按键
        _hotkey_showTranslateInputWidget->setShortcut(QKeySequence(SettingData::instance().getHotkey(hotkey)));
        // 重新注册
        _hotkey_showTranslateInputWidget->setRegistered(true);
        break;
    case HotkeyName::StateChange:
        // 注销
        _hotkey_stateChange->setRegistered(false);
        // 设置新按键
        _hotkey_stateChange->setShortcut(QKeySequence(SettingData::instance().getHotkey(hotkey)));
        // 重新注册
        _hotkey_stateChange->setRegistered(true);
        break;
        //以下不可立马注册
    case HotkeyName::Translate:
        // 注销
        _hotkey_translate->setRegistered(false);
        // 设置新按键
        _hotkey_translate->setShortcut(QKeySequence(SettingData::instance().getHotkey(hotkey)));
        break;
    case HotkeyName::Hide:
        // 注销
        _hotkey_hide->setRegistered(false);
        // 设置新按键
        _hotkey_hide->setShortcut(QKeySequence(SettingData::instance().getHotkey(hotkey)));
        break;
    default:
        break;
    }
}

void HotkeyManager::hotkey_hide_setRegistered(bool flag)
{
    _hotkey_hide->setRegistered(flag);
}

void HotkeyManager::hotkey_translate_setRegistered(bool flag)
{
    _hotkey_translate->setRegistered(flag);
}

QString HotkeyManager::hotkeyNameToQString(const HotkeyName hotkeyName)
{
qDebug() << "hotkeyNameToQString called with:" << (int)hotkeyName;
    switch (hotkeyName) {
        case HotkeyName::ShowTranslateInputWidget: return QString("ShowTranslateInputWidget");
        case HotkeyName::Translate: return QString("Translate");
        case HotkeyName::Hide: return QString("Hide");
        case HotkeyName::StateChange: return QString("StateChange");
        default: return "";
    }
}

bool HotkeyManager::hotkey_hide_isRegistered()
{
    return _hotkey_hide->isRegistered();
}

bool HotkeyManager::hotkey_translate_isRegistered()
{
    return _hotkey_translate->isRegistered();
}


