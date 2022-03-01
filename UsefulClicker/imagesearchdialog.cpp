#include "areaselectordialog.h"
#include "imagesearchdialog.h"
#include "dspmodule.h"
#include <windows.h>
#include "ui_imagesearchdialog.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

static AreaSelectorDialog* dlg = 0;
static DspModule* dsp;

ImageSearchDialog::ImageSearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageSearchDialog)
{
    ui->setupUi(this);
    labels_text_templ.push_back(ui->label->text());
    labels_text_templ.push_back(ui->label_2->text());
    labels_text_templ.push_back(ui->label_3->text());
    dsp = new DspModule();
}

ImageSearchDialog::~ImageSearchDialog()
{
    delete ui;
}

void ImageSearchDialog::on_screenAreaButton_clicked()
{
    dlg = new AreaSelectorDialog(this);
    dlg->setScreen(ui->screenSelector->currentIndex());
    screenshot = dlg->makeScreenshot().toImage();
    dlg->show();
    dlg->selectByWindow();
    connect(dlg, SIGNAL(sigSetRect(QRect)), this, SLOT(slotAreaSelected(QRect)));
}


void ImageSearchDialog::on_pushButton_5_clicked()
{


    AreaSelectorDialog* dlg = new AreaSelectorDialog(this);
    dlg->setScreen(ui->screenSelector->currentIndex());
    screenshot = dlg->makeScreenshot().toImage();
    dlg->fullScreen();
    connect(dlg, SIGNAL(sigSetRect(QRect)), this, SLOT(slotTargetSelected(QRect)));
}

void ImageSearchDialog::slotAreaSelected(QRect rect)
{
    selectedAreaRect = rect;
    QString text = "<html><head/><body><p align=\"center\"><span style=\" font-weight:700;\">Search Area Rectangle: </span></p><p>x0 = %1</p><p>y0 = %2</p><p>width = %3</p><p>height = %4</p></body></html>";//labels_text_templ[3];
    text = text.arg(rect.top())
                .arg(rect.left())
                .arg(rect.width())
                .arg(rect.height());
    ui->label_3->setText(text);

    areaImg.create(screenshot.height(), screenshot.width(), CV_8UC4);
    cv::Mat mat(screenshot.height(), screenshot.width(),CV_8UC4, screenshot.bits());
    cv::Rect rect1(rect.left(),rect.top(),rect.width(),rect.height());
    areaImg.create(screenshot.height(), screenshot.width(), CV_8UC4);
    areaImg = cv::Mat(mat, rect1);
    areaImg2  = new cv::Mat(screenshot.height(), screenshot.width(), CV_8UC4);
    *areaImg2 = cv::Mat(mat, rect1);

    QPixmap pix;
    pix.load(":/green_check_mark.png");
    ui->iconSearchArea->setPixmap(pix);
    cv::Size s1 = targetImg.size();
    cv::Size s2 = areaImg.size();
    if( s1.width != 0 && s2.width != 0)
    {
        ui->testClickButton->setEnabled(true);
        ui->testClickButton->setStyleSheet("");
        ui->findButton->setEnabled(true);
        ui->findButton->setStyleSheet("");
    }
    //imshow("areaImg", areaImg);
    // set target image to label
    QImage imgIn= QImage((uchar*) areaImg.data, areaImg.cols, areaImg.rows, areaImg.step, QImage::Format_ARGB32);
    ui->label_2->setPixmap(QPixmap::fromImage(imgIn));
    cvtColor( areaImg, areaImg, cv::COLOR_BGRA2BGR  );
    cv::imwrite("C:\\Images to Search On Screen\\areaImg.bmp", areaImg);


}

void ImageSearchDialog::slotTargetSelected(QRect rect)
{
    selectedTargetRect = rect;
    selectedAreaRect = rect;
    QString text = "<html><head/><body><p align=\"center\"><span style=\" font-weight:700;\">Search Area Rectangle: </span></p><p>x0 = %1</p><p>y0 = %2</p><p>width = %3</p><p>height = %4</p></body></html>";//labels_text_templ[3];
    text = text.arg(rect.top())
                .arg(rect.left())
                .arg(rect.width())
                .arg(rect.height());
    ui->label_3->setText(text);
    targetImg.create(screenshot.height(), screenshot.width(), CV_8UC4);
    cv::Mat mat(screenshot.height(), screenshot.width(),CV_8UC4, screenshot.bits());
    cv::Rect rect1(rect.left(),rect.top(),rect.width(),rect.height());
    targetImg = cv::Mat(mat, rect1);

    // set check mark
    QPixmap pix;
    pix.load(":/green_check_mark.png");
    ui->iconTargetSelected->setPixmap(pix);

    // set Test click button to Enabled state
    cv::Size s1 = targetImg.size();
    cv::Size s2 = areaImg.size();
    if( s1.width != 0 && s2.width != 0)
    {
        ui->testClickButton->setEnabled(true);
        ui->testClickButton->setStyleSheet("");
        ui->findButton->setEnabled(true);
        ui->findButton->setStyleSheet("");
    }

    // set target image to label
    QImage imgIn= QImage((uchar*) targetImg.data, targetImg.cols, targetImg.rows, targetImg.step, QImage::Format_ARGB32);
    ui->label_2->setPixmap(QPixmap::fromImage(imgIn));
    cvtColor( targetImg, targetImg, cv::COLOR_BGRA2BGR  );
    cv::imwrite("C:\\Images to Search On Screen\\targetImg.bmp", targetImg);


}


void ImageSearchDialog::on_screenSelector_currentIndexChanged(int index)
{

}


void ImageSearchDialog::on_findButton_clicked()
{
    dsp->computeHaudorf();
    ui->label_4->setText(QString("Coordinates found %1 %2").arg(dsp->X + rect().x()).
                                  arg(dsp->Y + rect().y()));
    //imshow("Target", targetImg);
    //imshow("Area", *areaImg2);


}


void ImageSearchDialog::on_testClickButton_clicked()
{
    INPUT Inputs[3] = {0};

    Inputs[0].type = INPUT_MOUSE;
 //   qDebug("MOUSE TO COORDINATES", );
    Inputs[0].mi.dx = dsp->X + rect().x(); // desired X coordinate
    Inputs[0].mi.dy = dsp->Y + rect().y(); // desired Y coordinate
    Inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;

    Inputs[1].type = INPUT_MOUSE;
    Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    Inputs[2].type = INPUT_MOUSE;
    Inputs[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(3, Inputs, sizeof(INPUT));
}
