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
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_AreaSelectorDialog
{
public:
    QLabel *label;

    void setupUi(QDialog *AreaSelectorDialog)
    {
        if (AreaSelectorDialog->objectName().isEmpty())
            AreaSelectorDialog->setObjectName(QString::fromUtf8("AreaSelectorDialog"));
        AreaSelectorDialog->setWindowModality(Qt::WindowModal);
        AreaSelectorDialog->resize(421, 376);
        AreaSelectorDialog->setWindowOpacity(0.800000000000000);
        AreaSelectorDialog->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(AreaSelectorDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 90, 221, 171));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setFrameShape(QFrame::Box);
        label->setLineWidth(3);
        label->setMidLineWidth(2);
        label->setMargin(2);

        retranslateUi(AreaSelectorDialog);

        QMetaObject::connectSlotsByName(AreaSelectorDialog);
    } // setupUi

    void retranslateUi(QDialog *AreaSelectorDialog)
    {
        AreaSelectorDialog->setWindowTitle(QCoreApplication::translate("AreaSelectorDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AreaSelectorDialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AreaSelectorDialog: public Ui_AreaSelectorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AREASELECTORDIALOG_H
