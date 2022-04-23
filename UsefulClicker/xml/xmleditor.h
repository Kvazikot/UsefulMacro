#ifndef XMLEDITOR_H
#define XMLEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include "clickerdocument.h"

class XmlEditor : public QTextEdit
{
    Q_OBJECT
public:
    explicit XmlEditor(QWidget *parent = nullptr);
    void setDoc(ClickerDocument* doc);

public slots:
    void onTextChange();

signals:
    void updateStatusBar(const QString& xmlErrorMessage);

private:
   ClickerDocument* doc;

};

#endif // XMLEDITOR_H
