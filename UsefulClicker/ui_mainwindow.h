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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *exitAction;
    QAction *insertRowAction;
    QAction *removeRowAction;
    QAction *insertColumnAction;
    QAction *removeColumnAction;
    QAction *insertChildAction;
    QAction *actionAbout;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionOpen;
    QAction *actionhideCodeTags;
    QAction *actionhideAllNonClickerTags;
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QTreeView *view;
    QMenuBar *menubar;
    QMenu *fileMenu;
    QMenu *actionsMenu;
    QMenu *menuAbout;
    QMenu *menuView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1276, 858);
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName(QString::fromUtf8("exitAction"));
        insertRowAction = new QAction(MainWindow);
        insertRowAction->setObjectName(QString::fromUtf8("insertRowAction"));
        removeRowAction = new QAction(MainWindow);
        removeRowAction->setObjectName(QString::fromUtf8("removeRowAction"));
        insertColumnAction = new QAction(MainWindow);
        insertColumnAction->setObjectName(QString::fromUtf8("insertColumnAction"));
        removeColumnAction = new QAction(MainWindow);
        removeColumnAction->setObjectName(QString::fromUtf8("removeColumnAction"));
        insertChildAction = new QAction(MainWindow);
        insertChildAction->setObjectName(QString::fromUtf8("insertChildAction"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionhideCodeTags = new QAction(MainWindow);
        actionhideCodeTags->setObjectName(QString::fromUtf8("actionhideCodeTags"));
        actionhideCodeTags->setCheckable(true);
        actionhideAllNonClickerTags = new QAction(MainWindow);
        actionhideAllNonClickerTags->setObjectName(QString::fromUtf8("actionhideAllNonClickerTags"));
        actionhideAllNonClickerTags->setCheckable(true);
        actionhideAllNonClickerTags->setChecked(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setSpacing(0);
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        view = new QTreeView(centralwidget);
        view->setObjectName(QString::fromUtf8("view"));
        view->setMouseTracking(true);
        view->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        view->setDragEnabled(true);
        view->setAlternatingRowColors(true);
        view->setSelectionMode(QAbstractItemView::SingleSelection);
        view->setSelectionBehavior(QAbstractItemView::SelectRows);
        view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        view->setIndentation(22);
        view->setSortingEnabled(false);
        view->setAnimated(false);
        view->setAllColumnsShowFocus(true);
        view->header()->setCascadingSectionResizes(true);
        view->header()->setMinimumSectionSize(44);
        view->header()->setDefaultSectionSize(44);
        view->header()->setHighlightSections(true);
        view->header()->setProperty("showSortIndicator", QVariant(false));

        vboxLayout->addWidget(view);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1276, 21));
        fileMenu = new QMenu(menubar);
        fileMenu->setObjectName(QString::fromUtf8("fileMenu"));
        actionsMenu = new QMenu(menubar);
        actionsMenu->setObjectName(QString::fromUtf8("actionsMenu"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(fileMenu->menuAction());
        menubar->addAction(actionsMenu->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menubar->addAction(menuView->menuAction());
        fileMenu->addAction(actionOpen);
        fileMenu->addAction(actionSave);
        fileMenu->addAction(actionSave_as);
        actionsMenu->addAction(insertRowAction);
        actionsMenu->addSeparator();
        actionsMenu->addAction(removeRowAction);
        actionsMenu->addSeparator();
        menuAbout->addAction(actionAbout);
        menuView->addAction(actionhideCodeTags);
        menuView->addAction(actionhideAllNonClickerTags);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Editable Tree Model", nullptr));
        exitAction->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
#if QT_CONFIG(shortcut)
        exitAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        insertRowAction->setText(QCoreApplication::translate("MainWindow", "Insert Row", nullptr));
#if QT_CONFIG(shortcut)
        insertRowAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+I, R", nullptr));
#endif // QT_CONFIG(shortcut)
        removeRowAction->setText(QCoreApplication::translate("MainWindow", "Remove Row", nullptr));
#if QT_CONFIG(shortcut)
        removeRowAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+R, R", nullptr));
#endif // QT_CONFIG(shortcut)
        insertColumnAction->setText(QCoreApplication::translate("MainWindow", "Insert Column", nullptr));
#if QT_CONFIG(shortcut)
        insertColumnAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+I, C", nullptr));
#endif // QT_CONFIG(shortcut)
        removeColumnAction->setText(QCoreApplication::translate("MainWindow", "Remove Column", nullptr));
#if QT_CONFIG(shortcut)
        removeColumnAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+R, C", nullptr));
#endif // QT_CONFIG(shortcut)
        insertChildAction->setText(QCoreApplication::translate("MainWindow", "Insert Child", nullptr));
#if QT_CONFIG(shortcut)
        insertChildAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionSave_as->setText(QCoreApplication::translate("MainWindow", "Save as...", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionhideCodeTags->setText(QCoreApplication::translate("MainWindow", "hideCodeTags", nullptr));
        actionhideAllNonClickerTags->setText(QCoreApplication::translate("MainWindow", "hideAllNonClickerTags", nullptr));
        fileMenu->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
        actionsMenu->setTitle(QCoreApplication::translate("MainWindow", "&Actions", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "About", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
