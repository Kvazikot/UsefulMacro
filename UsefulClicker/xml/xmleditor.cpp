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

}
