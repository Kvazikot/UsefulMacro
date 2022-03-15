#ifndef INTERPRETERWIN64_H
#define INTERPRETERWIN64_H

#include <QObject>

#include "interpreter.h"
void hotKey(char* hot_key);
class InterpreterWin64 : public AbstractInterpreter
{
    Q_OBJECT
public:
    InterpreterWin64(InterpreterData initData);
    void MainLoop();
    void ScrollUp(int number_scrolls) override;
    void ScrollDown(int number_scrolls) override;
    void keyDown(Qt::Key key) override;
    void keyUp(Qt::Key key) override;
    void MouseClick(QPoint coordinates, Qt::MouseButton button) override;
    void MouseDblClick(QPoint coordinates, Qt::MouseButton button) override;
    void hotKey(char* hot_key) override;
    void type(QString string) override;

signals:
    void setCurrentNode(QDomNode& currentNode);

public slots:
    void Play() override;
    void StepForward() override;
    void StepBackward() override;
    void Goto(QDomNode& node) override;
    void Pause() override;

};


#endif // INTERPRETERWIN64_H
