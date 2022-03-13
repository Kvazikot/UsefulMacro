/*
+ - - - + - + - -
+ - + - + copyright by Vladimir Baranov (Kvazikot)  <br>
+ - + - + email: vsbaranov83@gmail.com  <br>
+ - + - + github: https:/images//github.com/Kvazikot/UsefulMacro/  <br>
```
                          )            (
                         /(   (\___/)  )\
                        ( #)  \ ('')| ( #
                         ||___c\  > '__||
                         ||**** ),_/ **'|
                   .__   |'* ___| |___*'|
                    \_\  |' (    ~   ,)'|
                     ((  |' /(.  '  .)\ |
                      \\_|_/ <_ _____> \______________
                       /   '-, \   / ,-'      ______  \
              b'ger   /      (//   \\)     __/     /   \
                                          './_____/
```
*/

#include <QPoint>
#include "interpreter.h"

AbstractInterpreter::AbstractInterpreter(InterpreterData initData)
    : data(initData)
{

}

//-------------------------------------------------------------------------------

void Worker::doJob(const AbstractInterpreter& interpreter, const QDomNode& job)
{
    QString result;
    /* ... here is the expensive or blocking operation ... */
    emit resultReady(result);
}

void Worker::mainLoop(const AbstractInterpreter& interpreter)
{

}

void Worker::pause()
{

}

//-------------------------------------------------------------------------------
void Controller::handleResults(const QString &)
{

}
