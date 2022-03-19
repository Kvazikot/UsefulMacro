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
#include <QApplication>
#include "interpreter/interpreter.h"
#include <windows.h>
#include "interpreter/interpreterpy.h"


void AbstractInterpreter::process(const QDomNode& domNode)
{
    //qDebug() << __FUNCTION__ << "isElement" << level << QString(level, ' ').toLocal8Bit().constData() << domElement.tagName().toLocal8Bit().constData();
    // я знаю что тут нужно измерять время таймером...
    // не надо меня учить
    Delays delays = parseDelays(domNode);
    if( parse(domNode) == -1)
        delays.delay_fixed = 0;

}
