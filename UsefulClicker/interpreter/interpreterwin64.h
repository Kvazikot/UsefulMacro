#ifndef INTERPRETERWIN64_H
#define INTERPRETERWIN64_H

#include <QObject>

#include "interpreter/interpreter.h"
void hotKey(char* hot_key);



class InterpreterWin64 : public AbstractInterpreter
{
    Q_OBJECT    
public:
    QStringList validNodes = {"hotkey","click","dblclick","type",
                               "keydown","keyup","scrollup","scrolldown",
                               "func"};

    InterpreterWin64(InterpreterData* initData);
    Delays parseDelays(const QDomNode& node)  override;
    QRect parseRect(const QDomNode& node);

    void MainLoop();
    int parse(const QDomNode& node) override;
    InterpreterData* getData() override;

signals:
    void setCurrentNode(QDomNode& currentNode);

public slots:
    /*
    void Play() override;
    void StepForward() override;
    void StepBackward() override;
    void Goto(QDomNode& node) override;
    void Pause() override;
    */


};


#endif // INTERPRETERWIN64_H
