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

//-------------------------------------------------------------------------------
InterpreterDaemon::InterpreterDaemon(AbstractInterpreter* interpreter)
    : QThread(), interpreter(interpreter), stopFlag(false)
{
    //InterpreterPy* python = new InterpreterPy();
}

void InterpreterDaemon::TraverseXmlNode(const QDomNode& node)
{
  QDomNode domNode = node.firstChild();
  QDomElement domElement;
  QDomText domText;

  static int level = 0;

  level++;

  while(!(domNode.isNull()))
  {
    if(domNode.isElement())
    {
      domElement = domNode.toElement();
      if(!(domElement.isNull()))
      {
      }
    }


    if(0)
    for(auto i =0; i < domNode.childNodes().count(); i++)
    {
        auto child = domNode.childNodes().at(i);
        TraverseXmlNode(child);
    }

    TraverseXmlNode(domNode);
    domNode = domNode.nextSibling();

    //qDebug() << __FUNCTION__ << "isElement" << level << QString(level, ' ').toLocal8Bit().constData() << domElement.tagName().toLocal8Bit().constData();
    // я знаю что тут нужно измерять время таймером...
    // не надо меня учить
    Delays delays = interpreter->parseDelays(domNode);
    if( interpreter->parse(domNode) == -1)
        delays.delay_fixed = 0;
    //QThread::msleep(qRound(delays.delay_fixed));
    if ( stopFlag ) return;

    QThread::msleep(delays.delay_fixed);


    InterpreterData* data1 = interpreter->getData();
    data1->currentNode = domNode;

  }

  level--;
}

void InterpreterDaemon::run()
{
    InterpreterData* data1 = interpreter->getData();
    TraverseXmlNode(data1->rootNode);
}

