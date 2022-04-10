#include <QDebug>
#include <QPoint>
#include <QTime>
#include <QDateTime>
#include <QClipboard>
#include <QApplication>
#include <windef.h>
#include "interpreter/interpreterwin64.h"
#include "model/clickermodel.h"
#include "windows.h"
#include "settings/clickersettings.h"
#include <windows.h>
#include <QRect>
#include <QRegularExpression>

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


void Key(char* hot_key)
{
    //SendCtrlA();
    //return;
    if( strlen(hot_key) > 200 ) return;
    QVector<WORD> vkeys;
    char c = hot_key[strlen(hot_key)-1];
    SHORT code = c-32;
    code = VkKeyScanA(c);
    //qDebug() << __FUNCTION__ << QString(hot_key) << " VkKeyScanA code =" << code << " c=" << c ;

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

InterpreterWin64::InterpreterWin64()
    : AbstractInterpreter()
{
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

void InterpreterWin64::MySleep(QDateTime endTime)
{
    const auto MAX_DELAY_SEC = 20;
    QDateTime startTime = QDateTime::currentDateTime();
    while(1)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, MAX_DELAY_SEC);
        QDateTime currentTime = QDateTime::currentDateTime();
        if( currentTime.msecsTo(endTime) < 0)
            break;
        if( startTime.secsTo(currentTime) >  MAX_DELAY_SEC)
            break;
        Sleep(10);
    }

}

int InterpreterWin64::executeHotkey(const QDomNode& node)
{
    QString str = node.toElement().attribute("hotkey");
    str = str.replace(" ","");
    Key((char*)str.toLocal8Bit().toStdString().c_str());
    return 1;
}

int InterpreterWin64::executeClick(const QDomNode& node)
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

int InterpreterWin64::executeType(const QDomNode& node)
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    //QString originalText = clipboard->text();
    QString text;
    if( node.toElement().hasAttribute("text") )
        text = node.toElement().attribute("text");
    else
        text = node.toElement().nodeValue();
    clipboard->setText(text);
    Key("ctrl+v");
}


void InterpreterWin64::executeFunction(const QDomNode& rootNode, QDomNode funcNode, QString function_name)
{

    QDomNode domNode = rootNode.firstChild();
    QDomElement domElement;
    while(!(domNode.isNull()))
    {
        if(domNode.isElement())
        {
            domElement = domNode.toElement();
            if(!(domElement.isNull()))
            {
                QString name = domNode.nodeName();
                if(name == "func" && domElement.attribute("name") == function_name)
                   funcNode = domNode;
            }

        }
        //getFunctionsList(domNode, outList);
        if( domNode.parentNode() == funcNode)
        {
            qDebug() << "node name " << domNode.nodeName() << "is in function" << funcNode.toElement().attribute("name");
            execute(domNode);
        }
        //qDebug() << "node name is " << domNode.nodeName() << "is in function" << funcNode.toElement().attribute("name");
        executeFunction(domNode, funcNode, function_name);
        domNode = domNode.nextSibling();
    }
}

int InterpreterWin64::executeShellCommand(const QDomNode& node)
{
    QString cmd;
    if( node.toElement().hasAttribute("cmd") )
    {
        cmd = node.toElement().attribute("cmd");
        ShellExecuteA(0, 0, (char*)cmd.toStdString().c_str(), 0, 0, SW_NORMAL);
    }
    return 0;
}

int InterpreterWin64::execute(const QDomNode& node)
{
    QString name = node.toElement().tagName().toLocal8Bit();
    if( !validNodes.contains( name  ) ) return -1;

    qDebug() << name;

    //
    int repeats = ATTR("repeats").toInt();
    int n = 0;

    while(n++ < repeats)
    {

        if( name == "hotkey" )
            executeHotkey(node);

        if( name == "click" )
            executeClick(node);

        if( name == "type" )
            executeType(node);

        if( name == "shell" )
            executeShellCommand(node);

        // make a delay
        Delays delays = parseDelays(node);
        int delay = delays.delay_fixed + (delays.delay_random * (float)rand()/RAND_MAX);
        QDateTime t = QDateTime::currentDateTime().addMSecs(delay);
        MySleep(t);
        qDebug() << __FUNCTION__ << " delay=" << delay;
    }


    return 0;
}
