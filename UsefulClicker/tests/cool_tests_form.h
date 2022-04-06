#ifndef COOL_TESTS_FORM_H
#define COOL_TESTS_FORM_H

#include <QDialog>

namespace Ui {
class CoolTestsForm;
}

class CoolTestsForm : public QDialog
{
    Q_OBJECT

public:
    explicit CoolTestsForm(QWidget *parent = nullptr);
    ~CoolTestsForm();

private slots:
    void on_buttonsDetector1_clicked();
    void on_runNotepadFullscreen_clicked();

private:
    Ui::CoolTestsForm *ui;
};

#endif // COOL_TESTS_FORM_H
