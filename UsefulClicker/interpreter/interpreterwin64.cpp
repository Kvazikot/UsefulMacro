#include <QPoint>
#include "interpreterwin64.h"


InterpreterWin64::InterpreterWin64(InterpreterData initData)
    : AbstractInterpreter(initData)
{

}

void InterpreterWin64::ScrollUp(int number_scrolls){}
void InterpreterWin64::ScrollDown(int number_scrolls){}
void InterpreterWin64::keyDown(Qt::Key key){}
void InterpreterWin64::keyUp(Qt::Key key){}
void InterpreterWin64::MouseClick(QPoint coordinates, Qt::MouseButton button){}
void InterpreterWin64::MouseDblClick(QPoint coordinates, Qt::MouseButton button){}
void InterpreterWin64::hotKey(QVector<Qt::Key> keys){}
void InterpreterWin64::type(QString string){}
void InterpreterWin64::Play(){}
void InterpreterWin64::StepForward(){}
void InterpreterWin64::StepBackward(){}
void InterpreterWin64::Goto(QDomNode& node){}
void InterpreterWin64::Pause(){}
