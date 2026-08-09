#include "widget.h"
#include "translateinputwidget.h"
#include "settingdata.h"
#include "hotkeymanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SettingData::instance().load();
    SettingData::instance();
    HotkeyManager::instance();


    Widget w;
    TranslateInputWidget tw;
    tw.hide();
    return a.exec();
}
