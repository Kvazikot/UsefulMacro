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

#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#include "ui/mainwindow.h"
#include "ui/imagesearchdialog.h"
#include "ui/areaselectordialog.h"
#include "ui/screenbuttonsdetector.h"
#include "xml/serialisationtest.h"
#include "xml/xmlstreamer.h"



int main(int argc, char *argv[])
{



    QApplication app(argc, argv);
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("UsefulClicker");
    app.setApplicationVersion("0.4a");
    //SerialisationTest test;
    //XmlStreamer streamer;

    MainWindow mainwindow;
    mainwindow.show();
    //InterpreterWin64 interpreter_test();

    //ScreenButtonsDetector detector;
    //detector.show();
    //ImageSearchDialog dlg;
    //dlg.show();
    return app.exec();
}
