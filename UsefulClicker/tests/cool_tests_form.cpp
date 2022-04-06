#include "cool_tests_form.h"
#include "ui_cool_tests_form.h"

CoolTestsForm::CoolTestsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CoolTestsForm)
{
    ui->setupUi(this);
}

CoolTestsForm::~CoolTestsForm()
{
    delete ui;
}
