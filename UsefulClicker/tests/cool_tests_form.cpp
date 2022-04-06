#include "cool_tests_form.h"
#include "ui_cool_tests_form.h"
#include "ui/mainwindow.h"
#include "ui/areaselectordialog.h"
#include "ui/screenbuttonsdetector.h"

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

void CoolTestsForm::on_runNotepadFullscreen_clicked()
{

}


void CoolTestsForm::on_buttonsDetector1_clicked()
{
    //AreaSelectorDialog* dlg = new AreaSelectorDialog(this);
    //dlg->showFullScreen();
    ScreenButtonsDetector* dlg = new ScreenButtonsDetector(this);
    dlg->showFullScreen();

}

