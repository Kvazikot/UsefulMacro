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
    int screenNum=0;
    explicit CoolTestsForm(QWidget *parent = nullptr);
    void runFunction(QString func_name);
    void fullScreen();
    void createButtons();
    ~CoolTestsForm();

private slots:
    void on_buttonsDetector1_clicked();
    void on_runNotepadFullscreen_clicked();
    void on_imageSearch_clicked();
    void on_typeTest_clicked();


    void on_runFunction_clicked();

    void on_pushButton_3_clicked();

    void on_pickPoint_clicked();

    void on_areaButton_clicked();

    void on_functionsList_currentIndexChanged(int index);

public slots:
    void slotSetAttrs(QMap<QString,QString> attrs);
    void slotFullScreen();
private:
    Ui::CoolTestsForm *ui;
};

#endif // COOL_TESTS_FORM_H
