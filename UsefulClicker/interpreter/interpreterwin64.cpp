#include <QDebug>
#include <QPoint>
#include <QTime>
#include <QDateTime>
#include <QClipboard>
#include <QDir>
#include <QGuiApplication>
#include <QScreen>
#include <QtGlobal>
#include <QApplication>
#include <windef.h>
#include "interpreter/interpreterwin64.h"
#include "model/clickermodel.h"
#include "cv/dspmodule.h"
#include "windows.h"
#include "settings/clickersettings.h"
#include <windows.h>
#include <QRect>
#include <QRegularExpression>

static DspModule* dsp;
using namespace cv;

InterpreterWin64::InterpreterWin64()
    : AbstractInterpreter()
{
    dsp = new DspModule();
}

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
}

void KeySequence(char* hot_key, int delay_ms)
{
    QVector<WORD> vkeys;
    QStringList keys = QString(hot_key).split('+');
    int k = 0;
    // keyup events
    for(QString tok : keys)
    {
        tok = tok.toLower();
        SHORT c = (int)tok[0].toLower().toLatin1()-32;
        k = VkKeyScanA(c);
        if(tok == "left")
           k = VK_LEFT;
        if(tok == "right")
           k = VK_RIGHT;
        if(tok == "down")
           k  = VK_DOWN;
        if(tok == "up")
            k = VK_UP;
        if(tok == "enter")
         k = VK_RETURN;
        INPUT inputs[2];
        ZeroMemory(inputs, sizeof(inputs));
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = k;
        SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    }



    // keydown events
    for(QString tok : keys)
    {
        tok = tok.toLower();
        SHORT c = (int)tok[0].toLower().toLatin1()-32;
        k = VkKeyScanA(c);
        if(tok == "left")
           k = VK_LEFT;
        if(tok == "right")
           k = VK_RIGHT;
        if(tok == "down")
           k  = VK_DOWN;
        if(tok == "up")
            k = VK_UP;
        if(tok == "enter")
         k = VK_RETURN;
        INPUT inputs[2];
        ZeroMemory(inputs, sizeof(inputs));
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = k;
        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    }

}

void ScrollDown()
{
    POINT mouse_pos;
    GetCursorPos(&mouse_pos);
    mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_WHEEL, 0, 0, DWORD(-100), 0);
    /*
    INPUT inputs[2];
    ZeroMemory(inputs, sizeof(inputs));
    inputs[0].mi.mouseData = -1040;
    inputs[0].mi.dy = -100;
    inputs[0].mi.dwExtraInfo = -100;
    SendInput(ARRAYSIZE(inputs), inputs, sizeof(MOUSEINPUT));
    */
}

void ScrollUp()
{
    POINT mouse_pos;
    GetCursorPos(&mouse_pos);
    mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_WHEEL, 0, 0, DWORD(100), 0);
    /*
    INPUT inputs[2];
    ZeroMemory(inputs, sizeof(inputs));
    inputs[0].mi.mouseData = 1040;
    inputs[0].mi.dy = 100;
    inputs[0].mi.dwExtraInfo = 100;
    SendInput(ARRAYSIZE(inputs), inputs, sizeof(MOUSEINPUT));
    */
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

    if( strstr(hot_key, "F1") !=NULL )
        vkeys.push_back(VK_F1);
    if( strstr(hot_key, "F2") !=NULL )
        vkeys.push_back(VK_F2);
    if( strstr(hot_key, "F3") !=NULL )
        vkeys.push_back(VK_F3);
    if( strstr(hot_key, "F4") !=NULL )
        vkeys.push_back(VK_F4);
    if( strstr(hot_key, "F5") !=NULL )
        vkeys.push_back(VK_F5);
    if( strstr(hot_key, "F6") !=NULL )
        vkeys.push_back(VK_F6);
    if( strstr(hot_key, "F7") !=NULL )
        vkeys.push_back(VK_F7);
    if( strstr(hot_key, "F8") !=NULL )
        vkeys.push_back(VK_F8);
    if( strstr(hot_key, "F9") !=NULL )
        vkeys.push_back(VK_F9);
    if( strstr(hot_key, "F10") !=NULL )
        vkeys.push_back(VK_F10);
    if( strstr(hot_key, "F11") !=NULL )
        vkeys.push_back(VK_F11);
    if( strstr(hot_key, "F12") !=NULL )
        vkeys.push_back(VK_F12);
    if( strstr(hot_key, "shift") !=NULL )
        vkeys.push_back(VK_SHIFT);
    if( strstr(hot_key, "ctrl") !=NULL )
        vkeys.push_back(VK_CONTROL);
    if( strstr(hot_key, "alt") !=NULL )
        vkeys.push_back(VK_MENU);
    if( strstr(hot_key, "win") !=NULL )
        vkeys.push_back(VK_LWIN);
    if( strstr(hot_key, "enter") !=NULL )
        vkeys.push_back(VK_RETURN);
    if( strstr(hot_key, "return") !=NULL )
        vkeys.push_back(VK_RETURN);
    if( strstr(hot_key, "home") !=NULL )
        vkeys.push_back(VK_HOME);
    if( strstr(hot_key, "up") !=NULL )
        vkeys.push_back(VK_UP);
    if( strstr(hot_key, "down") !=NULL )
        vkeys.push_back(VK_DOWN);

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
            if (ok) args.push_back(i);
        }
        else hasMatch = false;
    }
    if( args.size() == 4)
        return QRect(args[0],args[1],args[2],args[3]);
    return  QRect();
}

QPoint GetMousePos()
{
    POINT mouse_pos;
    GetCursorPos(&mouse_pos);
    return QPoint(mouse_pos.x, mouse_pos.y);
}

void MouseClick(QPoint coordinates, Qt::MouseButton button)
{
    POINT mouse_pos;
    mouse_pos.x = coordinates.x();
    mouse_pos.y = coordinates.y();

    GetCursorPos(&mouse_pos);
    mouse_pos.x =  coordinates.x();
    mouse_pos.y =  coordinates.y();
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

void MouseClick(QRect rect, Qt::MouseButton button)
{
    int x = rect.left() + (float)rect.width() * ((float)rand())/RAND_MAX;
    int y = rect.top() + (float)rect.height() * ((float)rand())/RAND_MAX;
    MouseClick(QPoint(x,y), button);
}

/* Windows sleep in 100ns units */
BOOLEAN nanosleep(LONGLONG ns){
    /* Declarations */
    HANDLE timer;	/* Timer handle */
    LARGE_INTEGER li;	/* Time defintion */
    /* Create timer */
    if(!(timer = CreateWaitableTimer(NULL, TRUE, NULL)))
        return FALSE;
    /* Set timer properties */
    li.QuadPart = -ns;
    if(!SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE)){
        CloseHandle(timer);
        return FALSE;
    }
    /* Start & wait for timer */
    WaitForSingleObject(timer, INFINITE);
    /* Clean resources */
    CloseHandle(timer);
    /* Slept without problems */
    return TRUE;
}

void InterpreterWin64::MySleep(QDateTime endTime)
{
    const auto MAX_DELAY_SEC = 20;
    QDateTime startTime = QDateTime::currentDateTime();
    while(1)
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        if( currentTime.msecsTo(endTime) < 0)
            break;
        if( startTime.secsTo(currentTime) >  MAX_DELAY_SEC)
            break;
        nanosleep(1000); // sleep 1000 nanoseconds
        QCoreApplication::processEvents(QEventLoop::AllEvents, MAX_DELAY_SEC);
    }

}

int InterpreterWin64::executeHotkey(const QDomNode& node)
{
    QString str;
    if( node.toElement().hasAttribute("hotkey") )
    {
        str = node.toElement().attribute("hotkey");
        str = str.replace(" ","");
        Key((char*)str.toLocal8Bit().toStdString().c_str());
    }
    if( node.toElement().hasAttribute("keysequence") )
    {
        str = node.toElement().attribute("keysequence");
        str = str.replace(" ","");
        auto delay_ms = node.toElement().attribute("delay_ms").toInt();
        KeySequence((char*)str.toLocal8Bit().toStdString().c_str(), delay_ms);
    }


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
    //clipboard->c
    Key("ctrl+v");
    return 0;
}

void InterpreterWin64::stop()
{
    stopFlag = true;
}


void InterpreterWin64::executeFunction(const QDomNode& rootNode, QDomNode funcNode, QString function_name)
{

    QDomNode domNode = rootNode.firstChild();
    QDomElement domElement;
    stopFlag = false;
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
        if( stopFlag ) return;
        //getFunctionsList(domNode, outList);
        if( domNode.parentNode() == funcNode)
        {
            execute(domNode);
        }
        else
            executeFunction(domNode, funcNode, function_name);

        domNode = domNode.nextSibling();
    }

}

int InterpreterWin64::executeShellCommand(const QDomNode& node)
{
    QString cmd;
    QStringList args;
    if( node.toElement().hasAttribute("cmd") )
    {
        cmd = node.toElement().attribute("cmd");
        args = cmd.split(" ");
        cmd = args[0];
        args.pop_front();
        ShellExecuteA(0, 0, (char*)cmd.toStdString().c_str(), (char*)args.join(" ").toStdString().c_str(), 0, SW_NORMAL);
    }
    return 0;
}

QString decodePath(QString filename)
{
    //$(UsefulClicker)/images/21.03.12.119.png
    QRegularExpression reEnv("[$(]{2}([\\w_]+)[)]{1}");
    auto match = reEnv.match(filename);
    QString clickerPath = QDir::currentPath();
    if( match.hasMatch() )
    {
        auto varname = match.capturedTexts()[1];
        filename = filename.replace("$(UsefulClicker)","");
        clickerPath = qEnvironmentVariable(varname.toStdString().c_str(), QDir::currentPath());
    }
    return clickerPath + filename;
}
//<clickimg area="Rect(330,645,229,56)" screenNum="0" targetImg="$(UsefulClicker)/images/21.03.12.119.png" button="left"> </clickimg>
int InterpreterWin64::executeClickImg(const QDomNode& node)
{
    QString targetImg_fn = decodePath(node.toElement().attribute("targetImg"));
    QString areaImg_path = QDir::currentPath() + "/images/";//decodePath(node.toElement().attribute("areaImg"));
    int screenNum = node.toElement().attribute("screenNum").toInt();
    QString button = node.toElement().attribute("button");
    QString areImg_fn = areaImg_path + "areaImg.bmp";

    /*
    QScreen* screen = QGuiApplication::screens()[screenNum];
    QImage screenshot = screen->grabWindow(0,0,0,screen->geometry().width(), screen->geometry().height()).toImage();
    cv::Mat areaImg(screenshot.height(), screenshot.width(),CV_8UC4, screenshot.bits());
    cvtColor( areaImg, areaImg, cv::COLOR_BGRA2BGR  );
    cv::imwrite(areImg_fn.toStdString(), areaImg);
    */

    dsp->searchImage(targetImg_fn.toStdString());
    if ( dsp->matchedRectangle.height() < 10 ) return 0;
    if ( dsp->matchedRectangle.width() < 10 ) return 0;

    if( button == "left")
        MouseClick(dsp->matchedRectangle, Qt::MouseButton::LeftButton);
    if( button == "right")
        MouseClick(dsp->matchedRectangle, Qt::MouseButton::RightButton);

    return 0;
}

int InterpreterWin64::executeScrollUp(const QDomNode& node)
{
    ScrollUp();
    return 1;
}

int InterpreterWin64::executeScrollDown(const QDomNode& node)
{
    ScrollDown();
    return 1;
}


std::map<std::string, method_t> interpreter_func_map{{"click",&InterpreterWin64::executeClick},
                                {"type",&InterpreterWin64::executeType},
                                {"shell",&InterpreterWin64::executeShellCommand},
                                {"clickimg",&InterpreterWin64::executeClickImg},
                                {"scrollup",&InterpreterWin64::executeScrollUp},
                                {"scrolldown",&InterpreterWin64::executeScrollDown},
                                {"hotkey",&InterpreterWin64::executeHotkey}};

int InterpreterWin64::execute(const QDomNode& node)
{
    QString name = node.toElement().tagName().toLocal8Bit();
    if( !validNodes.contains( name  ) ) return -1;


    //
    int repeats = ATTR("repeats").toInt();
    int n = 0;

    while(n++ < repeats)
    {
        if( stopFlag ) return 0;

       // find method in table by name of xml node
       auto kv = interpreter_func_map.find(name.toStdString());

       // call the method
       if( kv != interpreter_func_map.end())
         (this->*(kv->second))(node);

        // make a delay
        currentDelays = parseDelays(node);
        long delay = currentDelays.delay_fixed + (currentDelays.delay_random * (float)rand()/RAND_MAX);
        qDebug() << "delay " << delay;
        QDateTime t = QDateTime::currentDateTime().addMSecs(delay);
        MySleep(t);
        //QThread::msleep(delay);
        //nanosleep(delay * 10e6);
        emit setCurrentNode(node, currentDelays);
    }

    return 0;
}
