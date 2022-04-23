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

void XmlEditor::onTextChange(){

    QRegularExpression re("$<func name=([\\w]+)");
    QRegularExpressionMatch match = re.match(toPlainText());
    if( match.hasMatch() )
    {
        QString funcname = match.capturedTexts()[2];
        if( !doc->setFunction(funcname, toPlainText()) )
            emit updateStatusBar("Xml error!");
        else
            emit updateStatusBar("Xml OK!");
    }
    QRegularExpression re2("$<func[ ]+>");
    match = re2.match(toPlainText());
    if( match.hasMatch() )
    {
        // generate function name
        QString randFunctionName = QString("func%1").arg(rand()%10000);
        if( !doc->setFunction(randFunctionName, toPlainText()))
            emit updateStatusBar("Xml error!");
        else
            emit updateStatusBar("Xml OK!");
    }
}

void XmlEditor::setDoc(ClickerDocument* doc)
{
    this->doc = doc;
}
