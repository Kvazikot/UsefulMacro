#include <QTableWidgetItem>
#include <QCoreApplication>
#include "apocaliptolib.h"
#include "globals.h"
#include "log/logger.h"

#include "ui_apocaliptolib.h"

ApocaliptoLIB::ApocaliptoLIB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApocaliptoLIB)
{
    ui->setupUi(this);
}

void ApocaliptoLIB::setInterpreter(AbstractInterpreter* interpreter)
{
    this->interpreter = interpreter;
}

void ApocaliptoLIB::init()
{
    auto list = Globals::global_lists["apocaliptoLib"];
    int row=0, col=0;
    ui->bookList->setColumnWidth(0, 10);
    ui->bookList->setColumnWidth(1, 400);
    ui->bookList->setColumnWidth(2, 400);
    ui->bookList->setRowCount(list.size());
    QRegularExpression authorRE("by([ ][\\S ,]+)");
    QRegularExpression authorRE2("[(]([\\w, ]+)[)]");
    for(auto s : list)
    {
        QString authors;
        auto match = authorRE.match(s);
        auto match2 = authorRE2.match(s);
        if( match.hasMatch() )
            authors = match.capturedTexts()[1];
        if( match2.hasMatch() )
            authors = match2.capturedTexts()[1];

        ui->bookList->setItem(row, 0, new QTableWidgetItem(QString::number(row)));
        ui->bookList->setItem(row, 1, new QTableWidgetItem(s));
        ui->bookList->setItem(row, 2, new QTableWidgetItem(authors));
        row++;
        //Log(s);

    }
}

ApocaliptoLIB::~ApocaliptoLIB()
{
    delete ui;

}

void ApocaliptoLIB::closeEvent(QCloseEvent* event)
{
    QCoreApplication::exit();
}

void ApocaliptoLIB::on_downloadWithoutVPN_clicked()
{
    interpreter->resetStopFlag();
    interpreter->executeFunction("GetBooks");

}


void ApocaliptoLIB::on_stopButton_clicked()
{
    interpreter->stop();
}

