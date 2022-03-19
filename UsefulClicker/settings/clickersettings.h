#ifndef CLICKERSETTINGS_H
#define CLICKERSETTINGS_H

#include <QSettings>

// -------------------------------------------------------------------------------

#define _F(f) ClickerSettings::getInstance()->readFlag(f)
#define _(f) ClickerSettings::getInstance()->readFlag(f)
#define DEFAULT(f) ClickerSettings::getInstance()->readDefault(f)
#define ATTR(a) node.toElement().attribute(a, DEFAULT(a).toString())

class ClickerSettings
{
public:
    static ClickerSettings instance;
    QSettings* settings;
    QString strKey;
    ClickerSettings();
    static ClickerSettings* getInstance(){return &instance;}
    void reload();
    bool readFlag(QString name);
    QVariant readDefault(QString name);
};

#endif // CLICKERSETTINGS_H
