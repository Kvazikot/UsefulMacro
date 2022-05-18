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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QKeySequenceEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_TypeDialog
{
public:
    QCheckBox *checkBox;
    QPlainTextEdit *plainTextEdit;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QKeySequenceEdit *keySequenceEdit;

    void setupUi(QDialog *TypeDialog)
    {
        if (TypeDialog->objectName().isEmpty())
            TypeDialog->setObjectName(QString::fromUtf8("TypeDialog"));
        TypeDialog->resize(779, 512);
        checkBox = new QCheckBox(TypeDialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(480, 0, 261, 81));
        plainTextEdit = new QPlainTextEdit(TypeDialog);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(10, 20, 451, 371));
        buttonBox = new QDialogButtonBox(TypeDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(11, 472, 167, 29));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(TypeDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(500, 130, 221, 121));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 40, 151, 71));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/keyboard_icon.png")));
        label->setScaledContents(true);
        label_2 = new QLabel(TypeDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(500, 260, 261, 111));
        label_2->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:repeat, cx:0.5, cy:0.5, radius:0.077, fx:0.5, fy:0.5, stop:0 rgba(0, 169, 255, 147), stop:0.497326 rgba(0, 0, 0, 147), stop:1 rgba(0, 169, 255, 147));\n"
"color: rgb(247, 19, 255);"));
        keySequenceEdit = new QKeySequenceEdit(TypeDialog);
        keySequenceEdit->setObjectName(QString::fromUtf8("keySequenceEdit"));
        keySequenceEdit->setGeometry(QRect(500, 90, 221, 51));

        retranslateUi(TypeDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, TypeDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, TypeDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(TypeDialog);
    } // setupUi

    void retranslateUi(QDialog *TypeDialog)
    {
        TypeDialog->setWindowTitle(QCoreApplication::translate("TypeDialog", "Dialog", nullptr));
        checkBox->setText(QCoreApplication::translate("TypeDialog", "do paste from clipboard (ctrl+v)\n"
" instead of typing", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("TypeDialog", "Text that is inserted in the window. Simulating keydown event for every symbol with delay.", nullptr));
        groupBox->setTitle(QCoreApplication::translate("TypeDialog", "Keyboard", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("TypeDialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:700; color:#3d9840;\">Click keyboard  </span></p><p align=\"center\"><span style=\" font-size:14pt; font-weight:700; color:#3d9840;\">to enter key sequence</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TypeDialog: public Ui_TypeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TYPEDIALOG_H
