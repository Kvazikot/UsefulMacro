#ifndef SHELLDIALOG_H
#define SHELLDIALOG_H

#include <QDialog>

namespace Ui {
class ShellDialog;
}

class ShellDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShellDialog(QWidget *parent = nullptr);
    ~ShellDialog();

private:
    Ui::ShellDialog *ui;
};

#endif // SHELLDIALOG_H
