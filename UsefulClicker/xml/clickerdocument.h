#ifndef CLICKERDOCUMENT_H
#define CLICKERDOCUMENT_H

#include <QDomDocument>
#include <QStringList>
// -------------------------------------------------------------------------------

class ClickerDocument : public QDomDocument
{
public:
    QStringList filters;
    QDomDocument original_document;
    explicit ClickerDocument(QString filename);
    QDomNode filter(QDomNode rootNode);
    QString getContent(QDomDocument& document);
    void setContent(QDomDocument& document, QString& text);
    void format_document(QTextStream& ts);
    void format_document(QString& text);
    void Save(QTextStream& ts);
    void reload();
    ~ClickerDocument();

};



#endif // CLICKERDOCUMENT_H
