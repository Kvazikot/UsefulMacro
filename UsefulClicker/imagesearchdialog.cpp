#include "areaselectordialog.h"
#include "imagesearchdialog.h"
#include "ui_imagesearchdialog.h"

static AreaSelectorDialog* dlg = 0;

ImageSearchDialog::ImageSearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageSearchDialog)
{
    ui->setupUi(this);
    labels_text_templ.push_back(ui->label->text());
    labels_text_templ.push_back(ui->label_2->text());
    labels_text_templ.push_back(ui->label_3->text());
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
    areaImg = mat;
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
    //copy data to cv matrix
    //memcpy(targetImg.data, screenshot.data_ptr().data(), sizeof(int) * screenshot.width() * screenshot.height());
    imshow("areaImg", targetImg);

}


void ImageSearchDialog::on_screenSelector_currentIndexChanged(int index)
{

}

