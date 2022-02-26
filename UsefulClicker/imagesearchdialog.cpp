#include "areaselectordialog.h"
#include "imagesearchdialog.h"
#include "ui_imagesearchdialog.h"

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
    AreaSelectorDialog* dlg = new AreaSelectorDialog(this);
    dlg->fullscreenMode = false;
    dlg->show();
}


void ImageSearchDialog::on_pushButton_5_clicked()
{
    AreaSelectorDialog* dlg = new AreaSelectorDialog(this);
    dlg->setScreen(ui->screenSelector->currentIndex());
    dlg->fullScreen();
    connect(dlg, SIGNAL(sigSetRect(QRect)), this, SLOT(slotAreaSelected(QRect)));
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
}

void ImageSearchDialog::slotTargetSelected(QRect rect)
{
    selectedTargetRect = rect;
}


void ImageSearchDialog::on_screenSelector_currentIndexChanged(int index)
{

}

