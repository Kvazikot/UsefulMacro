/********************************************************************************
** Form generated from reading UI file 'areaselectordialog.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AREASELECTORDIALOG_H
#define UI_AREASELECTORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_AreaSelectorDialog
{
public:
    QComboBox *comboBox;

    void setupUi(QDialog *AreaSelectorDialog)
    {
        if (AreaSelectorDialog->objectName().isEmpty())
            AreaSelectorDialog->setObjectName(QString::fromUtf8("AreaSelectorDialog"));
        AreaSelectorDialog->setWindowModality(Qt::WindowModal);
        AreaSelectorDialog->resize(421, 376);
        AreaSelectorDialog->setWindowOpacity(0.800000000000000);
        AreaSelectorDialog->setStyleSheet(QString::fromUtf8(""));
        comboBox = new QComboBox(AreaSelectorDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(100, 120, 201, 24));
        comboBox->setStyleSheet(QString::fromUtf8("color: rgb(188, 188, 188);"));
        comboBox->setEditable(true);
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
        comboBox->setDuplicatesEnabled(false);

        retranslateUi(AreaSelectorDialog);

        QMetaObject::connectSlotsByName(AreaSelectorDialog);
    } // setupUi

    void retranslateUi(QDialog *AreaSelectorDialog)
    {
        AreaSelectorDialog->setWindowTitle(QCoreApplication::translate("AreaSelectorDialog", "Dialog", nullptr));
        comboBox->setCurrentText(QCoreApplication::translate("AreaSelectorDialog", "wwww", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AreaSelectorDialog: public Ui_AreaSelectorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AREASELECTORDIALOG_H
