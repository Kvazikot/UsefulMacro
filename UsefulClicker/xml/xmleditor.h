#ifndef XMLEDITOR_H
#define XMLEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QDomNode>
#include "clickerdocument.h"

class XmlEditor : public QTextEdit
{
    Q_OBJECT
public:
    explicit XmlEditor(QWidget *parent = nullptr);
    void setDoc(ClickerDocument* doc);
    void setFuncNode(const QDomNode& node);
    QString genFunName();
    void newFun(QString name);
    void applyChanges();


public slots:
    void onTextChange();

signals:
    void updateStatusBar(const QString& xmlErrorMessage, bool applyChangesFlag);

private:
   ClickerDocument* doc;
   QDomNode currentNode;

};

#endif // XMLEDITOR_H
