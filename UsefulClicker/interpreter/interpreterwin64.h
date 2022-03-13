#ifndef INTERPRETERWIN64_H
#define INTERPRETERWIN64_H

#include <QObject>
#include "interpreter.h"

class InterpreterWin64 : public AbstractInterpreter
{
    Q_OBJECT
public:
    InterpreterWin64(QDomDocument& domDocument, QDomNode& currentNode);

};


#endif // INTERPRETERWIN64_H
