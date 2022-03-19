#ifndef CLICKERDOCUMENT_H
#define CLICKERDOCUMENT_H

#include <QDomDocument>

// -------------------------------------------------------------------------------

class ClickerDocument : public QDomDocument
{
public:
    QDomDocument original_document;
    explicit ClickerDocument(QString filename);
    QDomNode filter(QDomNode rootNode);
    ~ClickerDocument();

};



#endif // CLICKERDOCUMENT_H
