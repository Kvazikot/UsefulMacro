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
#include "ui/shelldialog.h"
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
static Highlighter* highlighter = 0;
//static QVector<QImage> icons_cache;

QString decodePath1(QString filename)
{
    //$(UsefulClicker)/images/21.03.12.119.png
    QRegularExpression reEnv("[$(]{2}([\\w_]+)[)]{1}");
    auto match = reEnv.match(filename);
    QString clickerPath = QDir::currentPath();
    if( match.hasMatch() )
    {
        auto varname = match.capturedTexts()[1];
        filename = filename.replace("$(UsefulClicker)","");
        qDebug() << __FUNCTION__ << varname;
        clickerPath = qEnvironmentVariable(varname.toStdString().c_str(), QDir::currentPath());
    }
    return clickerPath + filename;
}

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
    //
    connect(editor, SIGNAL(textChanged()), this, SLOT(textChanged()));
    editor->setFont(font);
    highlighter = new Highlighter(editor->document());
    ui->groupBox_5->layout()->replaceWidget(ui->xmlEditor, editor);

    auto func_body_text = window->getDoc()->getFunction(ui->functionsList->currentText());
    editor->clear();
    editor->setText(func_body_text);

    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextCursor cursor = editor->textCursor();
    QTextFrameFormat frameFormat;
    frameFormat.setHeight(10);
    frameFormat.setWidth(2350);
    frameFormat.setBackground(Qt::yellow);
    cursor.insertFrame(frameFormat);
    editor->setTextCursor(cursor);
    connect(editor, SIGNAL(cursorPositionChanged()), this, SLOT(cursorPositionChanged()));

    // individfual functions tests
    decodePath1("$(UsefulClicker)/images/21.03.12.119.png");

//    QTextEdit::ExtraSelection selection;
//    selection.format.setBackground(Qt::yellow);
//    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
//    selection.cursor = cursor;
//    selection.cursor.clearSelection();
//    extraSelections.append(selection);
//    editor->setExtraSelections(extraSelections);


    startTimer(1000);
    //runFunction("Change font");
}

void CoolTestsForm::cursorPositionChanged()
{
}

void CoolTestsForm::timerEvent(QTimerEvent* event)
{
    /*
    if( lastEditTimer.elapsed() > 2000 && saved == false)
    {
        if(editor)
        {
            MainWindow* window = MainWindow::getInstance();
            window->getDoc()->setFunction(ui->functionsList->currentText(), editor->toPlainText().toLocal8Bit());
            saved = true;
        }

    }
    */
}

void CoolTestsForm::textChanged()
{
    lastEditTimer.restart();
    saved = false;
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
    qDebug() << window->getDoc()->getFunction(func_name);
    InterpreterWin64*  interpreter = static_cast<InterpreterWin64*>(window->getInterpreter());
    interpreter->executeFunction(doc->documentElement(), doc->documentElement(), func_name);
    qDebug() << __FUNCTION__ << " ~~~~~ EXECUTION DONE ~~~~~!";

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
        QStringList lines = func_body_text.split("\n");
        //highlighter->highlightBlock(lines[lines.size()/2]);
    }
}


void CoolTestsForm::on_shellDialog_clicked()
{
    ShellDialog* dlg = new ShellDialog(this);
    dlg->show();
}


void CoolTestsForm::on_pushButton_4_clicked()
{
    runFunction("Post Twit");
}



void CoolTestsForm::on_createTestXml_clicked()
{
    static ClickerDocument* testdoc;
    QString xml = "<?xml version='1.0'?> <xml error=\"This is default document. Make sure you load right xml.\"> <func name=\"test_f\" > <type text=\"text\"/>  </func>  </xml>";
    testdoc = new ClickerDocument();
    QDomDocument* dom_doc = static_cast<QDomDocument*>(testdoc);
    dom_doc->setContent(xml);
    testdoc->save("test_doc.xml");
    runFunction("Open test_doc.xml");
    delete testdoc;
}


void CoolTestsForm::on_setFunctionTest_clicked()
{
    static ClickerDocument* testdoc;
    QString xml = "<?xml version='1.0'?> " \
                  "<xml error=\"This is default document. Make sure you load right xml.\"> "
                  "<func name=\"test_f\" > <type text=\"text\"/>  </func>  </xml>";
    testdoc = new ClickerDocument();
    QDomDocument* dom_doc = static_cast<QDomDocument*>(testdoc);
    dom_doc->setContent(xml);
    QString function_body = QString("<func name=\"test_f\" ><hotkey hotkey=\"win+R\" /></func>");
    testdoc->setFunction("test_f", function_body);
    testdoc->save("test_doc.xml");
    runFunction("Open test_doc.xml");
    delete testdoc;
}

