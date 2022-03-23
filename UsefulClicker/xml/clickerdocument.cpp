#include <QFile>
#include <QDebug>
#include <QRegularExpression>
#include "settings/clickersettings.h"
#include "clickerdocument.h"

ClickerDocument::ClickerDocument(QString fullpath)
    : QDomDocument()
{
    QString filename = fullpath;

    QDomDocument doc(filename);
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "cannot open " << filename;
        return;
    }
    if (!doc.setContent(&file)) {
        file.close();
        qDebug() << "xml error";
        return;
    }
    file.close();

    QDomDocument& this_reference = *this;
    this_reference = doc;
    original_document = doc;


    if( _F("hideAllNonClickerTags") )
    {
        filters = {"shell", "code", "include"};
    }

}

QString ClickerDocument::getContent(QDomDocument& document)
{
    return document.toString();
}

void ClickerDocument::setContent(QDomDocument& document, QString& text)
{
    format_document(text);
    document.setContent(text);
}

void ClickerDocument::Save(QTextStream& ts)
{
    format_document(ts);
    ts <<  getContent(original_document);
}

void Fix_line(QString& line)
{
    QMap<QString, QString> key_value;
    QRegularExpression re("[\\s]{0,1}([\\w]+)(=)([\"]{0,1}[\\w\\s\\d(,).]+[\"]{0,1})");
    //
    int n_attrs = 0;
    int pos = 0;
    bool hasMatch = true;
    while( hasMatch )
    {
        QRegularExpressionMatch match = re.match(line, pos, QRegularExpression::NormalMatch);
        if (match.hasMatch()) {
            pos = match.capturedEnd(0);
            QStringList lst = match.capturedTexts();
            int i = 0;
            for(auto s : lst)
            {
                //qDebug() << "________" << lst.join(" ").replace(QChar('"'),QChar(' '));
                qDebug() << i << " " <<  s ;
                i++;
            }
            n_attrs++;
            hasMatch = true;
            QString key = lst[1];
            key.replace(QChar('"'),QChar(' ')).replace(" ","");
            QString value1 = lst[3];
            value1.replace(QChar('"'),QChar(' ')).replace(" ","");
            key_value[key] = value1;
            //line.remove(match.capturedStart(1), match.capturedLength(1));
            //line.remove(match.capturedStart(2), match.capturedLength(2));
            //line = line.replace(key,"");
            //qDebug() << line;
        }
        else
            hasMatch = false;
    }

    for( auto k : key_value)
    {
        qDebug() << k << " " << key_value[k];
    }
}

void ClickerDocument::format_document(QTextStream& ts)
{
    while(!ts.atEnd())
    {
        QString line  = ts.readLine();
        Fix_line(line);
    }
}

void ClickerDocument::reload()
{
    QString text = getContent(original_document);
    // pass xml to a custom parser to check that everything
    // satisfies UsefulClicker notation
    auto doc_ref = static_cast<QDomDocument*>(this);
    setContent(*doc_ref, text);
}


void ClickerDocument::format_document(QString& text)
{
    //This uses a C++11 raw string literal to create a regex that matches all three possibilities:
    //CR only (Mac)
    //CR+LF (Win)
    //LF (Unix)
    QRegularExpression re{R"-((\r\n?|\n))-"};

    //split text by line endings
    QStringList lines = text.split(re);

    for(QString& line : lines)
        Fix_line(line);
    text = lines.join("\n");
}

QDomNode ClickerDocument::filter(QDomNode rootNode)
{
    QDomDocument& this_reference = *this;
    this_reference = original_document;
    QDomNode n = rootNode;
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            for(QString& f: filters)
            {
                if(e.tagName().contains(f))
                {
                    qDebug() << qPrintable(e.tagName()) << "filtered out \n"; // the node really is an element.
                    //delete e;
                }
            }
            for(int i=0; i <  e.childNodes().count(); i++)
                filter(e.childNodes().at(i));
        }
        n = n.nextSibling();
    }
    return n;
}


ClickerDocument::~ClickerDocument()
{

}
