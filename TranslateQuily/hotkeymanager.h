#ifndef HOTKEYMANAGER_H
#define HOTKEYMANAGER_H

#include <QObject>
#include "3rdparty/QHotkey/qhotkey.h"
/*********************************************************
 * @file    hotkeymanager.h
 * @brief   快捷键集中管理，外部通过信号和槽进行注册
 *          快捷键数据在SettingData
 *
 * @author  木杨
 * @date    2026/08/08
 * @history
 *********************************************************/
enum class HotkeyName {
    ShowTranslateInputWidget,
    Translate,
    Hide,
    StateChange
};
class HotkeyManager : public QObject
{
    Q_OBJECT
private:
    explicit HotkeyManager(QObject *parent = nullptr);
    ~HotkeyManager() = default;
    HotkeyManager(const HotkeyManager&) = delete;
    HotkeyManager& operator=(const HotkeyManager&) = delete;
public:
    static HotkeyManager& instance();
    void setHotKey(const HotkeyName keyName,const QString keyValue);
    void updateHotKey(const HotkeyName hotkey);
    void hotkey_hide_setRegistered(bool flag);
    void hotkey_translate_setRegistered(bool flag);
    QString hotkeyNameToQString(const HotkeyName hotkeyName);
    bool hotkey_hide_isRegistered();
    bool hotkey_translate_isRegistered();
signals:
    void hotkey_stateChange_trigger();
    void hotkey_hide_trigger();
    void hotkey_translate_trigger();
    void _hotkey_showTranslateInputWidget_trigger();
private:
    QHotkey* _hotkey_stateChange;
    QHotkey* _hotkey_hide;
    QHotkey* _hotkey_translate;
    QHotkey* _hotkey_showTranslateInputWidget;
};

#endif // HOTKEYMANAGER_H
