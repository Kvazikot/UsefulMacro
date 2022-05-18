/********************************************************************************
** Form generated from reading UI file 'typedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TYPEDIALOG_H
#define UI_TYPEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TypeDialog
{
public:
    QDialogButtonBox *buttonBox;
    QPlainTextEdit *plainTextEdit;
    QCheckBox *checkBox;
    QWidget *widget;

    void setupUi(QDialog *TypeDialog)
    {
        if (TypeDialog->objectName().isEmpty())
            TypeDialog->setObjectName(QString::fromUtf8("TypeDialog"));
        TypeDialog->resize(598, 444);
        buttonBox = new QDialogButtonBox(TypeDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(240, 380, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        plainTextEdit = new QPlainTextEdit(TypeDialog);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(30, 100, 391, 231));
        checkBox = new QCheckBox(TypeDialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(40, 50, 441, 26));
        widget = new QWidget(TypeDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(60, 359, 131, 91));

        retranslateUi(TypeDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, TypeDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, TypeDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(TypeDialog);
    } // setupUi

    void retranslateUi(QDialog *TypeDialog)
    {
        TypeDialog->setWindowTitle(QCoreApplication::translate("TypeDialog", "Dialog", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("TypeDialog", "Text that is inserted in the window. Simulating keydown event for every symbol with delay.", nullptr));
        checkBox->setText(QCoreApplication::translate("TypeDialog", "do paste from clipboard (ctrl+v) instead of typing", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TypeDialog: public Ui_TypeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TYPEDIALOG_H
