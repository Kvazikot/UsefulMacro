#include <QFile>
#include <QDebug>
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


    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            qDebug() << qPrintable(e.tagName()) << '\n'; // the node really is an element.
        }
        n = n.nextSibling();
    }

    // Here we append a new element to the end of the document
    QDomElement elem = doc.createElement("img");
    elem.setAttribute("src", "myimage.png");
    docElem.appendChild(elem);
    QDomDocument& this_reference = *this;
    this_reference = doc;
    original_document = doc;
}

QDomNode ClickerDocument::filter(QDomNode rootNode)
{
    QStringList filters;

    if( _F("hideAllNonClickerTags") )
    {
        filters = {"shell", "code", "include"};
    }

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
