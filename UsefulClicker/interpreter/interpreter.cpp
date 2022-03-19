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


int AbstractInterpreter::process(const QDomNode& domNode)
{
    Delays delays = parseDelays(domNode);
    // -1 if node is rejected
    if( parse(domNode) == -1)
    {
        delays.delay_fixed = 0;
        return -1;
    }
    return 0;

}
