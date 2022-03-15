#define BIT(bit_no)         (1 << (bit_no))
#define CLEAR_BIT(reg, bit_no)   (reg) &= ~BIT(bit_no)
#define SET_BIT(reg, bit_no)   (reg) |= BIT(bit_no)
#define CHECK_BIT(reg, bit_no)   ( (reg) & BIT(bit_no) )
#define SWITCH_BIT(reg, bit_no)   (reg) ^= BIT(bit_no)


#include <QDebug>
#include <QPoint>
#include <windef.h>
#include "interpreter/interpreterwin64.h"
#include <windows.h>


void hotKey(char* hot_key)
{
    //SendCtrlA();
    //return;
    int n_modifiers=0;
    char c = hot_key[strlen(hot_key)-1];
    WORD flags=0;
    SHORT code = c-32;
    code = VkKeyScanA(c);
    qDebug() << hot_key << "VkKeyScanA code =" << code;

    if( strstr(hot_key, "shift") !=NULL )
    {
        SET_BIT(flags, 1);
        n_modifiers++;
    }
    if( strstr(hot_key, "ctrl") !=NULL )
    {
        SET_BIT(flags, 0);
        n_modifiers++;
    }
    if( strstr(hot_key, "alt") !=NULL )
    {
        SET_BIT(flags, 2);
        n_modifiers++;
    }
    if( strstr(hot_key, "win") !=NULL )
    {
        SET_BIT(flags, 3);
        n_modifiers++;
    }

/*
    HWND h = GetForegroundWindow();
    qDebug() << "Send WM_HOTKEY to " << h << " window code=" << code;
    PostMessage(h, WM_KEYDOWN, VK_CONTROL, MAKELPARAM(1,VK_CONTROL));
    PostMessageW(h, WM_KEYDOWN,  code, MAKELPARAM(1,0x01EF));
    //SendMessage(h, WM_KEYUP, VK_CONTROL, MAKELPARAM(1,0x01DF));
    PostMessage(h, WM_KEYUP,  code, MAKELPARAM(1,0x01EF));
*/

    INPUT inputs[4] = {};
    ZeroMemory(inputs, sizeof(inputs));

    inputs[0].type = INPUT_KEYBOARD;
    if( CHECK_BIT(flags, 0) )
        inputs[0].ki.wVk = VK_CONTROL;
    else
        inputs[0].ki.wVk = 0;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = code;

    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = code;
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[3].type = INPUT_KEYBOARD;
    if( CHECK_BIT(flags, 0) )
        inputs[3].ki.wVk = VK_CONTROL;
    else
        inputs[3].ki.wVk = 0;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));


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
