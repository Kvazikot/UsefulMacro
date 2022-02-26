#include "areaselectordialog.h"
#include "imagesearchdialog.h"
#include "ui_imagesearchdialog.h"

ImageSearchDialog::ImageSearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageSearchDialog)
{
    ui->setupUi(this);
}

ImageSearchDialog::~ImageSearchDialog()
{
    delete ui;
}

void ImageSearchDialog::on_screenAreaButton_clicked()
{
    AreaSelectorDialog* dlg = new AreaSelectorDialog(this);
    dlg->show();
}

