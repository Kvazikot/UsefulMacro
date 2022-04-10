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
    void runFunction(QString func_name);
    ~CoolTestsForm();

private slots:
    void on_buttonsDetector1_clicked();
    void on_runNotepadFullscreen_clicked();
    void on_imageSearch_clicked();
    void on_typeTest_clicked();


    void on_runFunction_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::CoolTestsForm *ui;
};

#endif // COOL_TESTS_FORM_H
