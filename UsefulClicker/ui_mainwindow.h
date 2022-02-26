/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionDiscrete_Correlation;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *selectTargetImageButton;
    QPushButton *selectSearchImageButton;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menubar;
    QMenu *menuCompute;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(980, 682);
        actionDiscrete_Correlation = new QAction(MainWindow);
        actionDiscrete_Correlation->setObjectName(QString::fromUtf8("actionDiscrete_Correlation"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);\n"
"font: 12pt \"Segoe UI\";\n"
"background-color: rgb(0, 0, 0);\n"
""));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        selectTargetImageButton = new QPushButton(centralwidget);
        selectTargetImageButton->setObjectName(QString::fromUtf8("selectTargetImageButton"));

        gridLayout->addWidget(selectTargetImageButton, 1, 0, 1, 1);

        selectSearchImageButton = new QPushButton(centralwidget);
        selectSearchImageButton->setObjectName(QString::fromUtf8("selectSearchImageButton"));

        gridLayout->addWidget(selectSearchImageButton, 1, 1, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setPixmap(QPixmap(QString::fromUtf8("../../../../Images to Search On Screen/Picture to Find 1 at 2 21 2022 2 24 53 PM.bmp")));
        label_2->setScaledContents(true);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8(""));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setPixmap(QPixmap(QString::fromUtf8("../../../../Images to Search On Screen/search_area.bmp")));
        label_3->setScaledContents(true);

        gridLayout->addWidget(label_3, 2, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 980, 21));
        menuCompute = new QMenu(menubar);
        menuCompute->setObjectName(QString::fromUtf8("menuCompute"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuCompute->menuAction());
        menuCompute->addAction(actionDiscrete_Correlation);

        retranslateUi(MainWindow);
        QObject::connect(menubar, SIGNAL(triggered(QAction*)), MainWindow, SLOT(computeDCorrelation()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionDiscrete_Correlation->setText(QCoreApplication::translate("MainWindow", "Discrete Correlation", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "corelation = 100%  coordinates: x = 0 y =0", nullptr));
        selectTargetImageButton->setText(QCoreApplication::translate("MainWindow", "Select Target Image", nullptr));
        selectSearchImageButton->setText(QCoreApplication::translate("MainWindow", "Select Search Image", nullptr));
        label_2->setText(QString());
        label_3->setText(QString());
        menuCompute->setTitle(QCoreApplication::translate("MainWindow", "Compute", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
