#include <QRegularExpression>
#include "xmleditor.h"
#include "tests/highlighter.h"

static Highlighter* highlighter;

XmlEditor::XmlEditor(QWidget *parent)
    : QTextEdit{parent}
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);
    //connect(editor, SIGNAL(textChanged()), this, SLOT(textChanged()));
    setFont(font);

    highlighter = new Highlighter(document());
    connect(this, SIGNAL(textChanged()), this, SLOT(onTextChange()));

}

void XmlEditor::setFuncNode(const QDomNode& node)
{
    currentNode = node;
}

void XmlEditor::applyChanges()
{

}

void XmlEditor::onTextChange()
{
    bool applyChangesFlag=true;
    QString str;

    QTextStream ts(&str);
    currentNode.save(ts, 0);
    if (str != toPlainText())
        applyChangesFlag = true;

    QRegularExpression re("<func name=([\"\\w _\\d]+)");
    QRegularExpressionMatch match = re.match(toPlainText());
    if( match.hasMatch() )
    {
        QString funcname = match.capturedTexts()[1];
        funcname = funcname.replace("\"","");
        if( !doc->setFunction(funcname, toPlainText()) )
            emit updateStatusBar("Xml error!", applyChangesFlag);
        else
            emit updateStatusBar("Xml OK!", applyChangesFlag);
    }
    QRegularExpression re2("<func[ ]+>");
    match = re2.match(toPlainText());
    if( match.hasMatch() )
    {
        // generate function name
        QString randFunctionName = genFunName();
        if( !doc->setFunction(randFunctionName, toPlainText()))
            emit updateStatusBar("Xml error!", applyChangesFlag);
        else
            emit updateStatusBar("Xml OK!", applyChangesFlag);
    }
}

void XmlEditor::newFun(QString name)
{
    QString initialXml = QString("<func name=\"%1\">\n</func>").arg(name);
    setText(initialXml);
}

QString XmlEditor::genFunName()
{
    QString randFunctionName = QString("func%1").arg(rand()%10000);
    return randFunctionName;
}

void XmlEditor::setDoc(ClickerDocument* doc)
{
    this->doc = doc;
}
