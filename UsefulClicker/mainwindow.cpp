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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dspmodule.h"
#include "aboutbox.h"

static DspModule* dsp;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startTimer(100);
}

void MainWindow::slotSetImage(QImage& img, int n_screen)
{

}

void MainWindow::slotAbout()
{
    AboutBox* aboutbox = new AboutBox(this);
    aboutbox->show();
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    event->accept();
}

MainWindow::~MainWindow()
{
    delete ui;
}
