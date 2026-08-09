#ifndef SETTINGDATA_H
#define SETTINGDATA_H

#include <QObject>
#include <QMap>
#include "hotkeymanager.h"
/*********************************************************
 * @file    settingdata.h
 * @brief   数据配置类，所有数据均在这个类的save()中保存，配置类加载config.ini文件来实现配置持久化
 *
 * @author  木杨
 * @date    2026/08/08
 * @history
 *********************************************************/
QString formatText(const QString& input);
class SettingData : public QObject
{
    Q_OBJECT
private:
    explicit SettingData(QObject *parent = nullptr);
    ~SettingData() = default;
    SettingData(const SettingData&) = delete;
    SettingData& operator=(const SettingData&) = delete;
public:

    static SettingData& instance();
    void save();
    void load();
    void saveHotkeyData(HotkeyName keyName,QString keyValue);
    QString getHotkey(const HotkeyName& keyName);
    //获取与设置apikey和appid
    QString getApiKey();
    QString getAppId();
    void setApiKey(QString apiKey);
    void setAppId(QString appId);

    //获取语言集的keys,value,获取与设置默认语言源和目标
    QList<QString> getTransLanguageKeys();
    QString getTransLanguageValue(const QString& key)const;
    QString getTransLanguageValue(const QString& key);
    QString getDefaultTransLanguageKey_onTransWidget_from();
    QString getDefaultTransLanguageKey_onTransWidget_to();

    QString getDefaultCopyTransLanguageKey_from();
    QString getDefaultCopyTransLanguageKey_to();

    void setDefaultCopyTransLanguageKey_from(const QString& from);
    void setDefaultCopyTransLanguageKey_to(const QString& to);
    void setDefaultTransLanguageKey_onTransWidget_from(const QString& from);
    void setDefaultTransLanguageKey_onTransWidget_to(const QString& to);

    QList<HotkeyName> getHotkeyNames();

    //
private:
    QMap<HotkeyName, QString> _hotkeys = {
        {HotkeyName::ShowTranslateInputWidget, "F2"},
        {HotkeyName::Translate, "Enter"},
        {HotkeyName::Hide, "Esc"},
        {HotkeyName::StateChange,"F1"}
    };
    QMap<QString,QString> _transLanguage=
        {{"简体中文", "zh"},
        {"繁体中文", "zh-TW"},
        {"英文", "en"},
        {"日文", "ja"},};

    QString _defaultTransLanguageKey_onTransWidget_from = "简体中文";
    QString _defaultTransLanguageKey_onTransWidget_to = "英文";
    QString _defaultCopyTransLanguageKey_from = "英文";
    QString _defaultCopyTransLanguageKey_to = "简体中文";
    QString _apiKey;
    QString _appId;

signals:
};

#endif // SETTINGDATA_H
