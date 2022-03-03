#ifndef USEFULINTERPRETER_H
#define USEFULINTERPRETER_H

#include <QObject>

// This class is interface for more specific classes
// for varios specific platforms
// currently there is a x86 win 64

class UsefulInterpreter : public QObject
{
    Q_OBJECT
public:
    explicit UsefulInterpreter(QObject *parent = nullptr);

signals:

};

#endif // USEFULINTERPRETER_H
