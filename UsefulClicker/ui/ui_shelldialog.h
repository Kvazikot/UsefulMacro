/********************************************************************************
** Form generated from reading UI file 'shelldialog.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHELLDIALOG_H
#define UI_SHELLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "ui/widgets/qconsole.h"

QT_BEGIN_NAMESPACE

class Ui_ShellDialog
{
public:
    QDialogButtonBox *buttonBox;
    QPlainTextEdit *commandEdit;
    QPushButton *findProgramButton;
    QPlainTextEdit *historyEdit;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QPushButton *executeCommandButton;
    QConsole *console;

    void setupUi(QDialog *ShellDialog)
    {
        if (ShellDialog->objectName().isEmpty())
            ShellDialog->setObjectName(QString::fromUtf8("ShellDialog"));
        ShellDialog->resize(997, 612);
        ShellDialog->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(0, 0, 0, 0), stop:0.52 rgba(0, 0, 0, 0), stop:0.565 rgba(82, 121, 76, 33), stop:0.65 rgba(159, 235, 148, 64), stop:0.721925 rgba(255, 238, 150, 129), stop:0.77 rgba(255, 128, 128, 204), stop:0.89 rgba(191, 128, 255, 64), stop:1 rgba(0, 0, 0, 0));"));
        buttonBox = new QDialogButtonBox(ShellDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(870, 60, 91, 61));
        buttonBox->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 9pt \"Segoe UI\";"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        commandEdit = new QPlainTextEdit(ShellDialog);
        commandEdit->setObjectName(QString::fromUtf8("commandEdit"));
        commandEdit->setGeometry(QRect(30, 60, 400, 141));
        commandEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(126, 91, 162);\n"
"color: rgb(115, 255, 73);\n"
"font: 700 9pt \"Segoe UI\";\n"
"border-color: rgb(85, 0, 0);\n"
""));
        commandEdit->setFrameShape(QFrame::Box);
        commandEdit->setFrameShadow(QFrame::Sunken);
        commandEdit->setLineWidth(5);
        findProgramButton = new QPushButton(ShellDialog);
        findProgramButton->setObjectName(QString::fromUtf8("findProgramButton"));
        findProgramButton->setGeometry(QRect(260, 220, 171, 81));
        findProgramButton->setStyleSheet(QString::fromUtf8("color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(204, 201, 133, 255), stop:0.479904 rgba(153, 151, 80, 255), stop:0.522685 rgba(255, 255, 255, 255), stop:1 rgba(255, 255, 255, 255));\n"
"\n"
""));
        historyEdit = new QPlainTextEdit(ShellDialog);
        historyEdit->setObjectName(QString::fromUtf8("historyEdit"));
        historyEdit->setGeometry(QRect(460, 60, 400, 141));
        historyEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(126, 91, 162);\n"
"color: rgb(115, 255, 73);\n"
"font: 700 9pt \"Segoe UI\";"));
        historyEdit->setFrameShape(QFrame::Panel);
        historyEdit->setFrameShadow(QFrame::Sunken);
        historyEdit->setLineWidth(5);
        historyEdit->setMidLineWidth(0);
        layoutWidget = new QWidget(ShellDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 10, 761, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 170, 127,0);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 170, 127,0);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(label_2);

        executeCommandButton = new QPushButton(ShellDialog);
        executeCommandButton->setObjectName(QString::fromUtf8("executeCommandButton"));
        executeCommandButton->setGeometry(QRect(30, 220, 191, 81));
        executeCommandButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        console = new QConsole(ShellDialog);
        console->setObjectName(QString::fromUtf8("console"));
        console->setGeometry(QRect(120, 330, 721, 221));
        console->setStyleSheet(QString::fromUtf8("background-color: rgb(126, 91, 162);\n"
"color: rgb(115, 255, 73);\n"
"font: 700 9pt \"Segoe UI\";"));

        retranslateUi(ShellDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ShellDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ShellDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ShellDialog);
    } // setupUi

    void retranslateUi(QDialog *ShellDialog)
    {
        ShellDialog->setWindowTitle(QCoreApplication::translate("ShellDialog", "Dialog", nullptr));
        commandEdit->setPlainText(QCoreApplication::translate("ShellDialog", "start /B python start.py\n"
"", nullptr));
        findProgramButton->setText(QCoreApplication::translate("ShellDialog", "Find program", nullptr));
        historyEdit->setPlainText(QCoreApplication::translate("ShellDialog", "start /B python start.py\n"
"", nullptr));
        label->setText(QCoreApplication::translate("ShellDialog", "<html><head/><body><p><span style=\" font-size:22pt; font-weight:700; vertical-align:super;\">Shell command editor</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("ShellDialog", "<html><head/><body><p><span style=\" font-size:22pt; font-weight:700; vertical-align:super;\">Command history (see) </span><a href=\"settings.ini\"><span style=\" font-size:22pt; text-decoration: underline; color:#007af4;\">settings.ini</span></a></p></body></html>", nullptr));
        executeCommandButton->setText(QCoreApplication::translate("ShellDialog", "Execute command", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShellDialog: public Ui_ShellDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHELLDIALOG_H
