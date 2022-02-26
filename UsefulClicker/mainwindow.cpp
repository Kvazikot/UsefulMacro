#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dspmodule.h"

static DspModule* dsp;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startTimer(100);

    // defaults load from c:
    SearchIn.load("C:\\Images to Search On Screen\\search_area.bmp");
    TargetIn.load("C:\\Images to Search On Screen\\Picture to Find 1 at 2 21 2022 2 24 53 PM.bmp");
    ui->label_3->setPixmap(QPixmap::fromImage(SearchIn));
    ui->label_2->setPixmap(QPixmap::fromImage(TargetIn));
    qDebug() << "SearchIn w=" << SearchIn.width() << " h=" << SearchIn.height();
    qDebug() << "TargetIn w=" << TargetIn.width() << " h=" << TargetIn.height();


    //create dsp
    dsp = new DspModule();
    connect(dsp, SIGNAL(sigSendImage(QImage&,int)), this, SLOT(slotSetImage(QImage&,int)));
    //dsp->computeDiscreteCorrelation(SearchIn, TargetIn, Out);
    dsp->computeHaudorf();


}

void MainWindow::slotSetImage(QImage& img, int n_screen)
{
    //ui->label_3->setPixmap(QPixmap::fromImage(SearchIn));
    //ui->label_2->setPixmap(QPixmap::fromImage(TargetIn));
    qDebug() << "slot slotSetImage";

    if(n_screen)
    {
        summary.size1 = img.size();
        ui->label_3->setPixmap(QPixmap::fromImage(img));
        ui->label->setText(summary.toString());
    }
    else
    {
        summary.size2 = img.size();
        ui->label_2->setPixmap(QPixmap::fromImage(img));
        ui->label->setText(summary.toString());
    }

}

void MainWindow::computeDCorrelation()
{
   dsp->computeDiscreteCorrelation(SearchIn, TargetIn, Out);
}

void MainWindow::timerEvent(QTimerEvent* event)
{

    event->accept();
}

MainWindow::~MainWindow()
{
    delete ui;
}
