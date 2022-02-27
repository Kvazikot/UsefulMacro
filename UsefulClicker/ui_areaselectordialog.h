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
#include <QtWidgets/QDialog>
#include "canvas_label.h"

QT_BEGIN_NAMESPACE

class Ui_AreaSelectorDialog
{
public:
    Canvas_Label *label;

    void setupUi(QDialog *AreaSelectorDialog)
    {
        if (AreaSelectorDialog->objectName().isEmpty())
            AreaSelectorDialog->setObjectName(QString::fromUtf8("AreaSelectorDialog"));
        AreaSelectorDialog->setWindowModality(Qt::WindowModal);
        AreaSelectorDialog->resize(421, 376);
        AreaSelectorDialog->setWindowOpacity(0.800000000000000);
        AreaSelectorDialog->setStyleSheet(QString::fromUtf8(""));
        label = new Canvas_Label(AreaSelectorDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 40, 291, 251));

        retranslateUi(AreaSelectorDialog);

        QMetaObject::connectSlotsByName(AreaSelectorDialog);
    } // setupUi

    void retranslateUi(QDialog *AreaSelectorDialog)
    {
        AreaSelectorDialog->setWindowTitle(QCoreApplication::translate("AreaSelectorDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AreaSelectorDialog: public Ui_AreaSelectorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AREASELECTORDIALOG_H
