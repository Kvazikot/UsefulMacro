#include <QDebug>
#include <QPoint>
#include <windef.h>
#include "interpreter/interpreterwin64.h"
#include <windows.h>

void send_key2(QVector<WORD>& vkeys, bool keyUp)
{
    INPUT inputs[2];
    ZeroMemory(inputs, sizeof(inputs));
    // keydown events
    int i=0;
    for(auto key : vkeys)
    {
        inputs[i].type = INPUT_KEYBOARD;
        inputs[i].ki.wVk = key;
        if(keyUp) inputs[i].ki.dwFlags = KEYEVENTF_KEYUP;
        i++;
    }
    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    Sleep(30);
}

void send_key3(QVector<WORD>& vkeys, bool keyUp)
{
    INPUT inputs[3];
    ZeroMemory(inputs, sizeof(inputs));
    // keydown events
    int i=0;
    for(auto key : vkeys)
    {
        inputs[i].type = INPUT_KEYBOARD;
        inputs[i].ki.wVk = key;
        if(keyUp) inputs[i].ki.dwFlags = KEYEVENTF_KEYUP;
        i++;
    }
    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    Sleep(30);
}


void hotKey(char* hot_key)
{
    //SendCtrlA();
    //return;
    QVector<WORD> vkeys;
    char c = hot_key[strlen(hot_key)-1];
    SHORT code = c-32;
    code = VkKeyScanA(c);
    qDebug() << hot_key << "VkKeyScanA code =" << code;

    if( strstr(hot_key, "shift") !=NULL )
        vkeys.push_back(VK_SHIFT);
    if( strstr(hot_key, "ctrl") !=NULL )
        vkeys.push_back(VK_CONTROL);
    if( strstr(hot_key, "alt") !=NULL )
        vkeys.push_back(VK_MENU);
    if( strstr(hot_key, "win") !=NULL )
        vkeys.push_back(VK_LWIN);
    vkeys.push_back(code);

    if(vkeys.size() == 2)
    {
       send_key2(vkeys, false);
       send_key2(vkeys, true);
    }
    if(vkeys.size() == 3)
    {
        send_key3(vkeys, false);
        send_key3(vkeys, true);
    }

}

InterpreterWin64::InterpreterWin64(InterpreterData initData)
    : AbstractInterpreter(initData)
{

}

void InterpreterWin64::ScrollUp(int number_scrolls){}
void InterpreterWin64::ScrollDown(int number_scrolls){}
void InterpreterWin64::keyDown(Qt::Key key)
{

}
void InterpreterWin64::keyUp(Qt::Key key){}

void InterpreterWin64::MouseClick(QPoint coordinates, Qt::MouseButton button)
{
    POINT mouse_pos;
    mouse_pos.x = coordinates.x();
    mouse_pos.y = coordinates.y();

    GetCursorPos(&mouse_pos);
    //mouse_pos.x =  dsp->X + selectedAreaRect.left(); //+ 100
    //mouse_pos.y =  dsp->Y + selectedAreaRect.top();
    SetCursorPos(mouse_pos.x, mouse_pos.y);

    if( button == Qt::MouseButton::LeftButton )
    {
        mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN, mouse_pos.x, mouse_pos.y, 0, 0);
        mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP, mouse_pos.x, mouse_pos.y, 0, 0);
    }

    if( button == Qt::MouseButton::RightButton )
    {
        mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTDOWN, mouse_pos.x, mouse_pos.y, 0, 0);
        mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTUP, mouse_pos.x, mouse_pos.y, 0, 0);
    }

    if( button == Qt::MouseButton::MiddleButton )
    {
        mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MIDDLEDOWN, mouse_pos.x, mouse_pos.y, 0, 0);
        mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MIDDLEUP, mouse_pos.x, mouse_pos.y, 0, 0);
    }



}

void InterpreterWin64::MouseDblClick(QPoint coordinates, Qt::MouseButton button)
{

}

void InterpreterWin64::hotKey(char* hot_key)
{
    char c = hot_key[strlen(hot_key)-1];
    WORD flags=0;
    SHORT code = VkKeyScanA(c);
    if( strstr(hot_key, "shift") !=NULL )
        flags |=MOD_SHIFT;
    if( strstr(hot_key, "ctrl") !=NULL )
        flags |=MOD_CONTROL;
    if( strstr(hot_key, "alt") !=NULL )
        flags |=MOD_ALT;
    if( strstr(hot_key, "win") !=NULL )
        flags |=MOD_WIN;
    HWND h = GetForegroundWindow();
    qDebug() << "Send WM_HOTKEY to " << h << " window";
    //SendMessageW(h, WM_HOTKEY, , MAKELPARAM(1, code));
}

void InterpreterWin64::type(QString string){}
void InterpreterWin64::Play(){}
void InterpreterWin64::StepForward(){}
void InterpreterWin64::StepBackward(){}
void InterpreterWin64::Goto(QDomNode& node){}
void InterpreterWin64::Pause(){}
