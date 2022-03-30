#include "shelldialog.h"
#include "ui_shelldialog.h"

ShellDialog::ShellDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShellDialog)
{
    ui->setupUi(this);
}

ShellDialog::~ShellDialog()
{
    delete ui;
}
