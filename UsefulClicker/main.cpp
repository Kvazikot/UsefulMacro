/*
+ - - - + - + - -
+ - + - + copyright by Vladimir Baranov (Kvazikot)  <br>
+ - + - + email: vsbaranov83@gmail.com  <br>
+ - + - + github: https://github.com/Kvazikot/UsefulMacro/  <br>
```
                          )            (
                         /(   (\___/)  )\
                        ( #)  \ ('')| ( #
                         ||___c\  > '__||
                         ||**** ),_/ **'|
                   .__   |'* ___| |___*'|
                    \_\  |' (    ~   ,)'|
                     ((  |' /(.  '  .)\ |
                      \\_|_/ <_ _____> \______________
                       /   '-, \   / ,-'      ______  \
              b'ger   /      (//   \\)     __/     /   \
                                          './_____/
```
*/
#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include <QApplication>
#include <QLabel>
#include <QMessageBox>
#include <QProcess>
#include <QSurfaceFormat>
#include <QTime>
#include <QFile>
#include "ui/mainwindow.h"
#include "ui/imagesearchdialog.h"
#include "ui/areaselectordialog.h"
#include "ui/screenbuttonsdetector.h"
#include "xml/serialisationtest.h"
#include "xml/xmlstreamer.h"
#include "ui/widgets/delaywidget.h"
#include "ui/shelldialog.h"
#include "tests/cool_tests_form.h"
/*


bool logToFile = true;
bool logToStderr = true;
extern void printToConsole(QString str);
FILE *loggingStreamStdout;

void customMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QHash<QtMsgType, QString> msgLevelHash({{QtDebugMsg, "Debug"}, {QtInfoMsg, "Info"}, {QtWarningMsg, "Warning"}, {QtCriticalMsg, "Critical"}, {QtFatalMsg, "Fatal"}});
    QByteArray localMsg = msg.toLocal8Bit();
    QTime time = QTime::currentTime();
    QString formattedTime = time.toString("hh:mm:ss.zzz");
    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();


   // if (type == QtInfoMsg) {
        QString txt = QString("%1: %2 ").arg(formattedTime, msg);
        //printToConsole(msg);
//    }

}
*/

int main(int argc, char *argv[])
{
    /*
    FILE *loggingStreamStderr;
    QFile loggingFile("app.log");
    loggingFile.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Unbuffered);
    int fd = loggingFile.handle();
    freopen_s(&loggingStreamStdout, "\\\\.\\NUL", "w", stdout);
    setvbuf(loggingStreamStdout, NULL, _IONBF, 0);
    freopen_s(&loggingStreamStderr, "\\\\.\\NUL", "w", stderr);
    setvbuf(loggingStreamStderr, NULL, _IONBF, 0);
    _dup2(fd, _fileno(stdout));
    _dup2(fd, _fileno(stderr));

    qInstallMessageHandler(customMessageOutput); // custom message handler for debugging
    */

    QApplication app(argc, argv);
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("UsefulClicker");
    app.setApplicationVersion("0.9a");
    //SerialisationTest test;
    //XmlStreamer streamer;

    MainWindow mainwindow;

    CoolTestsForm tests;
    mainwindow.show();

    tests.show();



    //InterpreterWin64 interpreter_test();

    //DelayWidget widget;
    //widget.show();

    //ShellDialog* dlg = new ShellDialog();
    //dlg->show();


    //ScreenButtonsDetector detector;
    //detector.show();
    //ImageSearchDialog dlg;
    //dlg.show();
    return app.exec();
}
