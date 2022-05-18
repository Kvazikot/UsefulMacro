#ifndef TYPEDIALOG_H
#define TYPEDIALOG_H

#include <QDialog>

namespace Ui {
class TypeDialog;
}

class TypeDialog : public QDialog
{
    Q_OBJECT
public:
    QMap<QString,QString> attrs;
    explicit TypeDialog(QWidget *parent = nullptr);
    explicit TypeDialog(QString mode);

    ~TypeDialog();

signals:
    void sigSetAttrs(QMap<QString,QString>);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::TypeDialog *ui;
};

#endif // TYPEDIALOG_H
