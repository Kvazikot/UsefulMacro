#ifndef USFEULINTERPRETERWIN_H
#define USFEULINTERPRETERWIN_H

#include <QObject>
#include "usefulinterpreter.h"

class UsfeulInterpreterWin : public UsefulInterpreter
{
    Q_OBJECT
public:
    explicit UsfeulInterpreterWin(QObject *parent = nullptr);

signals:

};

#endif // USFEULINTERPRETERWIN_H
