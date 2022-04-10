#include <QDir>
#include <QScreen>
#include <QGuiApplication>
#include <QTimer>
#include "cool_tests_form.h"
#include "interpreter/interpreterwin64.h"
#include "ui_cool_tests_form.h"
#include "ui/mainwindow.h"
#include "ui/areaselectordialog.h"
#include "ui/screenbuttonsdetector.h"
#include "ui/coordselector.h"
#include "ui/imagesearchdialog.h"

CoolTestsForm::CoolTestsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CoolTestsForm)
{
    MainWindow* window = MainWindow::getInstance();
    QString fn = ":/tests/UsefulClicker_tests.xml";
    window->loadDocument(fn);    
    ui->setupUi(this);
    QDomDocument* doc = static_cast<QDomDocument*>(window->getDoc());
    QStringList list;
    if( doc!=0 )
        window->getDoc()->getFunctionsList(doc->documentElement(),list);
    ui->functionsList->clear();
    ui->functionsList->addItems(list);
    ui->functionsList->setCurrentIndex(2);
    //runFunction("Change font");
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
    ScreenButtonsDetector* dlg = new ScreenButtonsDetector(this);
    dlg->showFullScreen();
}


void CoolTestsForm::on_imageSearch_clicked()
{
    ImageSearchDialog* dlg = new ImageSearchDialog();
    dlg->show();
}

void CoolTestsForm::runFunction(QString func_name)
{
    MainWindow* window = MainWindow::getInstance();
    QDomDocument* doc = static_cast<QDomDocument*>(window->getDoc());
    InterpreterWin64*  interpreter = static_cast<InterpreterWin64*>(window->getInterpreter());
    interpreter->executeFunction(doc->documentElement(), doc->documentElement(), func_name);
}

void CoolTestsForm::on_typeTest_clicked()
{
    runFunction("Type test 2");
}

void CoolTestsForm::on_runFunction_clicked()
{
    runFunction(ui->functionsList->currentText());
}


void CoolTestsForm::on_pushButton_3_clicked()
{
    runFunction("Change font");
}

void CoolTestsForm::slotSetAttrs(QMap<QString,QString> attrs)
{
    QString text;
    for(auto key: attrs.keys())
        text+=key+"="+attrs[key]+" ";
    ui->plainTextEdit_3->appendPlainText(text);
}


void CoolTestsForm::slotFullScreen()
{
    QScreen* screen = QGuiApplication::screens()[screenNum];
    setGeometry(screen->geometry());
    setCursor(Qt::CrossCursor);
}

void CoolTestsForm::fullScreen()
{
    show();
    QTimer::singleShot(500, this, SLOT(slotFullScreen()));
}


void CoolTestsForm::on_pickPoint_clicked()
{
    CoordSelector* dlg = new CoordSelector(this);
    int screenNum = 0;
    if( ui->screen1->isChecked() )
        screenNum = 1;
    dlg->screenNum = screenNum;
    connect(dlg, SIGNAL(sigSetAttrs(QMap<QString,QString>)), this, SLOT(slotSetAttrs(QMap<QString,QString>)));
    dlg->fullScreen();
}


void CoolTestsForm::on_areaButton_clicked()
{
    AreaSelectorDialog* dlg = new AreaSelectorDialog(this);
    dlg->show();
}

