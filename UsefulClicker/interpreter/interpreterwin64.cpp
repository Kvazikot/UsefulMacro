#include <QDebug>
#include <QPoint>
#include <windef.h>
#include "interpreter/interpreterwin64.h"
#include "model/clickermodel.h"
#include "settings/clickersettings.h"
#include <windows.h>
#include <QRect>
#include <QRegularExpression>

static InterpreterData* data = 0;

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
    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    Sleep(DEFAULT("input_delay_msec").toInt());
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
    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    Sleep(DEFAULT("input_delay_msec").toInt());
}


void hotKey(char* hot_key)
{
    //SendCtrlA();
    //return;
    QVector<WORD> vkeys;
    char c = hot_key[strlen(hot_key)-1];
    SHORT code = c-32;
    code = VkKeyScanA(c);
    qDebug() << __FUNCTION__ << QString(hot_key) << " VkKeyScanA code =" << code << " c=" << c;

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

InterpreterWin64::InterpreterWin64(InterpreterData* initData)
    : AbstractInterpreter()
{
    data = initData;
}

Delays InterpreterWin64::parseDelays(const QDomNode& node)
{
    Delays delays;

    delays.delay_fixed = ATTR("delay_fixed").toFloat();
    delays.delay_random = ATTR("delay_random").toFloat();
    delays.repeat =  ATTR("repeat").toFloat();

    return delays;
}


QRect InterpreterWin64::parseRect(const QDomNode& node)
{
    QString value = node.toElement().attribute("area","QRect(1000,100,400,400)");
    QRegularExpression re("([\\d]+)");
    bool hasMatch = true;
    int pos = 0;
    QVector<int> args;
    while( hasMatch )
    {
        bool ok;
        QRegularExpressionMatch match = re.match(value, pos, QRegularExpression::NormalMatch);
        if (match.hasMatch()) {
            pos = match.capturedEnd(0);
            int i = match.captured(1).toInt(&ok);
            qDebug() << i;
            if (ok) args.push_back(i);
        }
        else hasMatch = false;
    }
    if( args.size() == 4)
        return QRect(args[0],args[1],args[2],args[3]);
    return  QRect();
}

InterpreterData* InterpreterWin64::getData()
{
    return data;
}

void MouseClick(QPoint coordinates, Qt::MouseButton button)
{
    POINT mouse_pos;
    mouse_pos.x = coordinates.x();
    mouse_pos.y = coordinates.y();

    qDebug() << __FUNCTION__ << " " << mouse_pos.x << " " << mouse_pos.y;
    GetCursorPos(&mouse_pos);
    mouse_pos.x =  coordinates.x();
    mouse_pos.y =  coordinates.y();
    SetCursorPos(mouse_pos.x, mouse_pos.y);

    return;
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

void MouseClick(QRect rect, Qt::MouseButton button)
{
    int x = rect.left() + (float)rect.width() * ((float)rand())/RAND_MAX;
    int y = rect.top() + (float)rect.height() * ((float)rand())/RAND_MAX;
    qDebug() << __FUNCTION__ << " rect = " << rect <<  "x=" << x << " y" << y;
    MouseClick(QPoint(x,y), button);
}

int InterpreterWin64::parse(const QDomNode& node)
{
    QString name = node.toElement().tagName().toLocal8Bit();
    if( !validNodes.contains( name  ) ) return -1;

    qDebug() << name;

    if( name == "hotkey" )
    {
        QString str = node.toElement().attribute("hotkey");
        str = str.replace(" ","");
        hotKey((char*)str.toLocal8Bit().toStdString().c_str());
        return 1;
    }
    //<click area="Rect(0,1,200,200)" button="left"/>
    //<click x="10" y="20"  button="right"/>
    if( name == "click" )
    {
        QString atr = node.toElement().attribute("button");
        Qt::MouseButton b;
        if (atr == "left")
            b = Qt::MouseButton::LeftButton;
        else
            b = Qt::MouseButton::RightButton;
        bool ok1,ok2;
        auto x = node.toElement().attribute("x").toInt(&ok1);
        auto y = node.toElement().attribute("y").toInt(&ok2);
        if(ok1 && ok2)
            MouseClick(QPoint(x,y), b);
        if( node.toElement().hasAttribute("area"))
        {
            QRect rect = parseRect(node);
            MouseClick(rect, b);
        }


        return 1;
    }

    return 0;
}
