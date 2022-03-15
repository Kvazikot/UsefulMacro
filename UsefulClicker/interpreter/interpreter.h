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


//-----------------------------------------------------
// В этом файле реализация интерпретатора кликера под виндовс
// Позднее я сделаю абстрактный платформонезависимый интерфейс
// И вынесу платформозависимую часть в отдельный файл
//-----------------------------------------------------
struct InterpreterData
{
    QDomDocument defaultDocument;
    QDomDocument& domDocument = defaultDocument;
    QDomNode currentNode;
    InterpreterData(){}
    InterpreterData(QDomDocument& d, QDomNode& n)
        :domDocument(d), currentNode(n)
    {}
};

class AbstractInterpreter : public QObject
{
    Q_OBJECT
public:
    AbstractInterpreter()
        :data(InterpreterData())
    {}
    AbstractInterpreter(InterpreterData initData);
    void MainLoop();
    virtual void ScrollUp(int number_scrolls)=0;
    virtual void ScrollDown(int number_scrolls)=0;
    virtual void keyDown(Qt::Key key)=0;
    virtual void keyUp(Qt::Key key)=0;
    virtual void MouseClick(QPoint coordinates, Qt::MouseButton button)=0;
    virtual void MouseDblClick(QPoint coordinates, Qt::MouseButton button)=0;
    virtual void hotKey(char* hot_key)=0;
    virtual void type(QString string)=0;

signals:
    void setCurrentNode(QDomNode& currentNode);

public slots:
    virtual void Play()=0;
    virtual void StepForward()=0;
    virtual void StepBackward()=0;
    virtual void Goto(QDomNode& node)=0;
    virtual void Pause()=0;
private:
    InterpreterData data;

};




// Worker - это рабочий поток кликера
class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(InterpreterData initData);

public slots:
    void mainLoop(const AbstractInterpreter& interpreter);
    void doJob(const AbstractInterpreter& interpreter, const QDomNode& job);
    void pause();
signals:
    void resultReady(const QString &result);

};

// класс Controller управляет работой рабочего потока Worker
// он может находиться в любом потоке в том числе в GUI потоке
class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;
    InterpreterData initData;
public:
    Controller(InterpreterData initData)
        :initData(initData)
    {
        // при старте контроллер запускает поток
        // с интерпретацией главного цикла кликера
        Worker *worker = new Worker(initData);
        worker->moveToThread(&workerThread);
        connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &Controller::runMainLoop, worker, &Worker::mainLoop);
        connect(this, &Controller::operate, worker, &Worker::doJob);
        connect(this, &Controller::set_pause, worker, &Worker::pause);
        connect(worker, &Worker::resultReady, this, &Controller::handleResults);
        workerThread.start();
    }

    // однократная работа - описанная в одном xml элементе
    // полезна при отладке скрипта, что позволяет запускать строчки на языке пайтон в отдельном потоке
    void doJob(QDomNode& job )
    {
        InterpreterData data(initData.domDocument, job);
        Worker *worker = new Worker(data);
        QThread* jobThread = new QThread();
        worker->moveToThread(jobThread);
        connect(jobThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &Controller::operate, worker, &Worker::doJob);
        connect(this, &Controller::set_pause, worker, &Worker::pause);
        connect(worker, &Worker::resultReady, this, &Controller::handleResults);
        jobThread->start();

    }
    ~Controller() {
        workerThread.quit();
        workerThread.wait();
    }
public slots:
    void handleResults(const QString &);
signals:
    void runMainLoop(const AbstractInterpreter& interpreter);
    void operate(const AbstractInterpreter& interpreter, const QDomNode& job);
    void set_pause();
};



#endif // INTERPRETER_H
