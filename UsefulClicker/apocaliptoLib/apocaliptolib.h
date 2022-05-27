#ifndef APOCALIPTOLIB_H
#define APOCALIPTOLIB_H

#include <QDialog>
#include <QCloseEvent>
#include <interpreter/interpreter.h>

namespace Ui {
class ApocaliptoLIB;
}

class ApocaliptoLIB : public QDialog
{
    Q_OBJECT

public:
    explicit ApocaliptoLIB(QWidget *parent = nullptr);
    void setInterpreter(AbstractInterpreter* interpreter);
    void init();
    void closeEvent(QCloseEvent* event);
    ~ApocaliptoLIB();    

    Ui::ApocaliptoLIB *ui;
    AbstractInterpreter* interpreter;
private slots:
    void on_downloadWithoutVPN_clicked();
    void on_stopButton_clicked();
};

#endif // APOCALIPTOLIB_H
