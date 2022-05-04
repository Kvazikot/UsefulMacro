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
#include "settings/clickersettings.h"
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
    testIsRunningFlag = false;

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);
    //editor = new QTextEdit();
    //
    //connect(editor, SIGNAL(textChanged()), this, SLOT(textChanged()));
    //editor->setFont(font);
    highlighter = new Highlighter(ui->xmlEditor->document());
    ui->groupBox_5->layout()->replaceWidget(ui->xmlEditor, editor);

    auto func_body_text = window->getDoc()->getFunction(ui->functionsList->currentText());
    ui->xmlEditor->clear();
    ui->xmlEditor->setText(func_body_text);

    startTimer(1000);
    //runFunction("Change font");
}

void CoolTestsForm::cursorPositionChanged()
{
}

void CoolTestsForm::timerEvent(QTimerEvent* event)
{

    if( lastBlinkTimer.elapsed() > 1000 && testIsRunningFlag)
    {
        lastBlinkTimer.restart();
        if (ui->testStatusLabel->text() == "")
            ui->testStatusLabel->setText(currentStepText);
        else
            ui->testStatusLabel->setText("");
    }

}

void CoolTestsForm::textChanged()
{
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
    int screenNum = 0;
    if( ui->screen1->isChecked() )
        screenNum = 1;
    ScreenButtonsDetector* dlg = new ScreenButtonsDetector(this, screenNum);
    dlg->setScreenNumber(screenNum);    
    connect(dlg, &ScreenButtonsDetector::sigSetAttrs, this, &CoolTestsForm::buttonDetectorOut);

    dlg->showFullScreen();
}

void CoolTestsForm::buttonDetectorOut(QMap<QString, QString> attrs)
{
    QString xmlstring = QString("<clickimg ");
    for(auto kv=attrs.begin(); kv!=attrs.end(); kv++)
        if( kv.key()!="nodename")
            xmlstring+=kv.key()+"=\""+kv.value()+"\" ";
    xmlstring+="/>";
    //QPixmap
    auto fn = attrs["targetImg"].replace("\"","");
    fn = decodePath(fn);

    ui->buttonImage->setPixmap(QPixmap(fn));
    ui->logEdit->appendPlainText(xmlstring);
}

void CoolTestsForm::on_clickimgTest_clicked()
{
    auto lines = ui->logEdit->toPlainText().split("\n");
    MainWindow* window = MainWindow::getInstance();
    ui->buttonImage->setPixmap(QPixmap());
//    ClickerDocument* doc = window->getDoc();
    QDomDocument doc;
    //xml = "<?xml version='1.0'?><xml>" + xml + "</xml>";
    auto xml = lines.back();
    if( doc.setContent( xml ) )
    {
        QDomElement root = doc.documentElement();
        //QDomNode node = doc->createNodeFromString( lines.back() );
        InterpreterWin64*  interpreter = static_cast<InterpreterWin64*>(window->getInterpreter());
        interpreter->execute(root);

    }


}




void CoolTestsForm::on_imageSearch_clicked()
{
    ImageSearchDialog* dlg = new ImageSearchDialog();
    dlg->show();
}

void CoolTestsForm::runFunction(QString func_name)
{
    totalTime = 0;
    //ui->stopTest->setText("STO! TEST IS RUNNING!");
    testIsRunningFlag = true;
    lastNodeTimer.restart();
    currentStepText = "RUNNING " + func_name;

    MainWindow* window = MainWindow::getInstance();
    QDomDocument* doc = static_cast<QDomDocument*>(window->getDoc());
    qDebug() << window->getDoc()->getFunction(func_name);
    InterpreterWin64*  interpreter = static_cast<InterpreterWin64*>(window->getInterpreter());
    connect(interpreter, SIGNAL(setCurrentNode(const QDomNode&,Delays)), this, SLOT(currentStep(const QDomNode&,Delays)));
    connect(this, SIGNAL(stopExecutionSignal()), interpreter, SLOT(stop()));
    interpreter->executeFunction(doc->documentElement(), doc->documentElement(), func_name);
    qDebug() << __FUNCTION__ << " ~~~~~ EXECUTION DONE ~~~~~!";
    testIsRunningFlag = false;
    ui->testStatusLabel->setText("SELECT THE TEST");
    QString msg = QString("Test is done. Execution time is %1 ms!").arg(QString::number(totalTime));
    show_message("",msg);
}

void CoolTestsForm::currentStep(const QDomNode& currentNode, Delays delays)
{
    auto msec = QString::number(lastNodeTimer.nsecsElapsed()/10e8);
    totalTime+=lastNodeTimer.nsecsElapsed()/10e8;
    currentStepText = "EXECUTING " + currentNode.toElement().tagName() + " in " + msec + " sec";
    ui->testStatusLabel->setText(currentStepText);
    ui->logEdit->appendPlainText(currentStepText);
    auto s = QString("delay_fixed = %1 milliseconds delay_random = %2 milliseconds total = %3")
            .arg(delays.delay_fixed)
            .arg(delays.delay_random)
            .arg(delays.delay_random + delays.delay_fixed);
    ui->logEdit->appendPlainText(s);
    lastNodeTimer.restart();
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
    ui->logEdit->appendPlainText(text);
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
    dlg->setScreenNumber(screenNum);
    connect(dlg, SIGNAL(sigSetAttrs(QMap<QString,QString>)), this, SLOT(slotSetAttrs(QMap<QString,QString>)));
    dlg->showFullScreen();
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


void CoolTestsForm::on_scrollTest_clicked()
{
    runFunction("Scroll Test");
}


void CoolTestsForm::on_stopTest_clicked()
{
    emit stopExecutionSignal();
    ui->testStatusLabel->setText("SELECT THE TEST");
}


void CoolTestsForm::on_typeTest2_clicked()
{
    runFunction("Type test 2");
}


void CoolTestsForm::on_typeTest_clicked(bool checked)
{
     runFunction("Type test");
}

