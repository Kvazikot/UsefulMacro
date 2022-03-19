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


#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QThread>
#include <QObject>
#include <QDomDocument>
#include <QDomNode>
//#include <QModelIndex>
//#include "clickermodel.h"
//-----------------------------------------------------
// В этом файле реализация интерпретатора кликера под виндовс
// Позднее я сделаю абстрактный платформонезависимый интерфейс
// И вынесу платформозависимую часть в отдельный файл
//-----------------------------------------------------
struct InterpreterData // убрать в отдельный h-файл
{
    QDomDocument defaultDocument;
    QDomDocument& domDocument = defaultDocument;
    QDomNode currentNode;
    QDomNode rootNode;
    InterpreterData(){}
    InterpreterData(QDomDocument& d, QDomNode& n)
        :domDocument(d), currentNode(n)
    {}
    InterpreterData(InterpreterData& initData)
    {
        defaultDocument = initData.defaultDocument;
        domDocument = initData.domDocument;
        currentNode = initData.currentNode;
    }
    void operator=(InterpreterData& initData)
    {
        defaultDocument = initData.defaultDocument;
        domDocument = initData.domDocument;
        currentNode = initData.currentNode;
    }
};

struct Delays
{
    float delay_fixed;
    float delay_random;
    float repeat;
};


class AbstractInterpreter : public QObject
{
    Q_OBJECT
public:
    AbstractInterpreter()
    {}
    void MainLoop();
    virtual int parse(const QDomNode& node)=0;
    virtual Delays parseDelays(const QDomNode& node)=0;
    virtual InterpreterData* getData()=0;

signals:
    void setCurrentNode(QDomNode& currentNode);

public slots:
/*
    virtual void Play()=0;
    virtual void StepForward()=0;
    virtual void StepBackward()=0;
    virtual void Goto(QDomNode& node)=0;
    virtual void Pause()=0;
*/

};




// Worker - это рабочий поток кликера
class InterpreterDaemon : public QThread
{
    Q_OBJECT
public:
    AbstractInterpreter* interpreter;
    QDeadlineTimer timer;
    bool stopFlag;

    InterpreterDaemon(){}
    InterpreterDaemon(AbstractInterpreter* interpreter);
    void TraverseXmlNode(const QDomNode& node);
    void run() override;

public slots:
    void setInterpreter(AbstractInterpreter* i)
    {
        interpreter = i;
        stopFlag = false;
    }
    void stop()
    {
        stopFlag = true;
    }
signals:
    //void resultReady(const QString &result);
    void resultReady(QModelIndex &result);

};



#endif // INTERPRETER_H
