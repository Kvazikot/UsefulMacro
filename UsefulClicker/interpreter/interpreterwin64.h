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

    bool stopFlag;
    Delays currentDelays;
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
    int executeScrollUp(const QDomNode& node);
    int executeScrollDown(const QDomNode& node);
    void executeFunction(const QDomNode& rootNode, QDomNode funcNode, QString function_name);
signals:
    void setCurrentNode(const QDomNode& currentNode, Delays delays);

public slots:
    void stop();
    /*
    void Play() override;
    void StepForward() override;
    void StepBackward() override;
    void Goto(QDomNode& node) override;
    void Pause() override;
    */


};

typedef int (InterpreterWin64::*method_t)(const QDomNode& n);
typedef std::map<std::string, method_t> func_map_t;


#endif // INTERPRETERWIN64_H
