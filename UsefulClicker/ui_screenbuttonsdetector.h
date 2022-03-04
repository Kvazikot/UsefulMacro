/********************************************************************************
** Form generated from reading UI file 'screenbuttonsdetector.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENBUTTONSDETECTOR_H
#define UI_SCREENBUTTONSDETECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_ScreenButtonsDetector
{
public:

    void setupUi(QDialog *ScreenButtonsDetector)
    {
        if (ScreenButtonsDetector->objectName().isEmpty())
            ScreenButtonsDetector->setObjectName(QString::fromUtf8("ScreenButtonsDetector"));
        ScreenButtonsDetector->resize(1938, 1098);
        ScreenButtonsDetector->setWindowOpacity(0.400000000000000);

        retranslateUi(ScreenButtonsDetector);

        QMetaObject::connectSlotsByName(ScreenButtonsDetector);
    } // setupUi

    void retranslateUi(QDialog *ScreenButtonsDetector)
    {
        ScreenButtonsDetector->setWindowTitle(QCoreApplication::translate("ScreenButtonsDetector", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScreenButtonsDetector: public Ui_ScreenButtonsDetector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENBUTTONSDETECTOR_H
