#include <QDir>
#include <QScreen>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QTimer>
#include <QTextEdit>
#include "cool_tests_form.h"
#include "interpreter/interpreterwin64.h"
#include "ui_cool_tests_form.h"
#include "ui/mainwindow.h"
#include "ui/areaselectordialog.h"
#include "ui/screenbuttonsdetector.h"
#include "ui/coordselector.h"
#include "ui/imagesearchdialog.h"
#include "tests/highlighter.h"

#include "ui/widgets/areabutton.h"
#include "ui/widgets/crossbutton.h"
#include "ui/widgets/keyboardbutton.h"
#include "ui/widgets/mousebutton.h"
#include "ui/widgets/comboedit.h"
#include "ui/widgets/shellbutton.h"


static KeyboardButton* keyboard_but;
static CrossButton* cross_but;
static MouseButton* mouse_but;
static AreaButton* area_but;
static ShellButton* shell_but;
static QTextEdit* editor = 0;
//static QVector<QImage> icons_cache;


//---------------------------------------------------------------------------------------------------------
void CoolTestsForm::createButtons()
{

    keyboard_but = new KeyboardButton(0);
    keyboard_but->setIcon(":/images/keyboard_icon.png", true, false);
    setContextMenuPolicy(Qt::PreventContextMenu);
    connect(keyboard_but, SIGNAL(clicked()),this, SLOT(slotKeyboardClick()));
    connect(keyboard_but, SIGNAL(clicked()),this, SLOT(slotButtonClicked()));

    mouse_but = new MouseButton(0);
    mouse_but->setIcon(":/images/mouse_default.png", true, true);
    connect(mouse_but, SIGNAL(click(QString)), this, SLOT(slotSetSequence(QString)));
    connect(mouse_but, SIGNAL(clicked()),this, SLOT(slotButtonClicked()));

    cross_but = new CrossButton(0);
    connect(cross_but, SIGNAL(click(QString)), this, SLOT(slotSetSequence(QString)));
    connect(cross_but, SIGNAL(clicked()),this, SLOT(updateSequence()));

    area_but = new AreaButton(this);
    area_but->state = true;
    area_but->setIcon(":/images/area_icon.png", true, true);
    connect(area_but, SIGNAL(clicked()),this, SLOT(slotButtonClicked()));
    connect(QCoreApplication::instance(), SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(slotFocusChanged(QWidget*, QWidget*)));

    shell_but = new ShellButton(this);
    connect(shell_but, SIGNAL(click(QString)), this, SLOT(slotSetSequence(QString)));
    connect(shell_but, SIGNAL(clicked()),this, SLOT(slotButtonClicked()));

    QHBoxLayout* hbox = new QHBoxLayout((QWidget*)ui->buttonsGroup);
    //hbox->addWidget(this);
    hbox->addWidget(shell_but);
    hbox->addWidget(area_but);
    hbox->addWidget(cross_but);
    hbox->addWidget(keyboard_but);
    hbox->addWidget(mouse_but);
    ui->buttonsGroup->setLayout(hbox);
    //cache_icons(hbox);



    //hbox->setStretch(0, 100);

    //QWidget* w = (QWidget*)this->parent();
    //w->setLayout(hbox);

}


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
    createButtons();

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);
    editor = new QTextEdit();
    editor->setFont(font);
    Highlighter* highlighter = new Highlighter(editor->document());
    ui->groupBox_5->layout()->replaceWidget(ui->xmlEditor, editor);

    auto func_body_text = window->getDoc()->getFunction(ui->functionsList->currentText());
    editor->setText(func_body_text);

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


void CoolTestsForm::on_functionsList_currentIndexChanged(int index)
{
    if(editor)
    {
        MainWindow* window = MainWindow::getInstance();
        auto func_body_text = window->getDoc()->getFunction(ui->functionsList->currentText());
        editor->setText(func_body_text);
    }
}

