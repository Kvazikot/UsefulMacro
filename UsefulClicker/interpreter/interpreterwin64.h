#ifndef INTERPRETERWIN64_H
#define INTERPRETERWIN64_H

#include <QObject>
#include <QDomNode>

#include "interpreter/interpreter.h"
void hotKey(char* hot_key);



class InterpreterWin64 : public AbstractInterpreter
{
    Q_OBJECT    
public:
    QStringList validNodes = {"hotkey","click","shell","dblclick","type",
                              "keydown","keyup","scrollup","scrolldown","clickimg",
                              "func"};


    InterpreterWin64();
    Delays parseDelays(const QDomNode& node)  override;
    QRect parseRect(const QDomNode& node);
    void MySleep(QDateTime endTime);

    void MainLoop();
    int execute(const QDomNode& node) override;
    int executeHotkey(const QDomNode& node);
    int executeClick(const QDomNode& node);
    int executeType(const QDomNode& node);
    int executeShellCommand(const QDomNode& node);
    int executeClickImg(const QDomNode& node);
    void executeFunction(const QDomNode& rootNode, QDomNode funcNode, QString function_name);
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
