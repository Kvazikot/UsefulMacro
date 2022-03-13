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


class AbstractInterpreter
{
    Q_OBJECT
public:
    AbstractInterpreter(QDomDocument& domDocument, QDomNode& currentNode);
    void MainLoop();
    virtual void ScrollUp(int number_scrolls);
    virtual void ScrollDown(int number_scrolls);
    virtual void keyDown(Qt::Key key);
    virtual void keyUp(Qt::Key key);
    virtual void MouseClick(QPoint coordinates, Qt::MouseButton button);
    virtual void MouseDblClick(QPoint coordinates, Qt::MouseButton button);
    virtual void hotKey(QVector<Qt::Key> keys);
    virtual void type(QString string);

signals:
    void setCurrentNode(QDomNode& currentNode);

public slots:
    void Play();
    void StepForward();
    void StepBackward();
    void Goto(QDomNode& node);
    void Pause();
};

struct InterpreterData
{
    QDomDocument& domDocument;
    QDomNode& currentNode;
    InterpreterData(QDomDocument& d, QDomNode& n)
        :domDocument(d), currentNode(n)
    {}
};


// Worker - это рабочий поток кликера
class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(InterpreterData initData);

public slots:
    void mainLoop(const QString &);
    void doJob(const QDomNode& job);
    void pause();
signals:
    void resultReady(const QString &result);

private:
    AbstractInterpreter interpreter;

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
    void runMainLoop(const QString &);
    void operate(const QDomNode& job);
    void set_pause();
};



#endif // INTERPRETER_H
