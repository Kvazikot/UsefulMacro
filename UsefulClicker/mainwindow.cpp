/*
+ - - - + - + - -
+ - + - + copyright by Vladimir Baranov (Kvazikot)  <br>
+ - + - + email: vsbaranov83@gmail.com  <br>
+ - + - + github: https:/images//github.com/Kvazikot/UsefulMacro/  <br>
```
                          )            (
                         /(   (\___/)  )\
                        ( #)  \ ('')| ( #
                         ||___c\  > '__||
                         ||**** ),_/ **'|
                   .__   |'* ___| |___*'|
                    \_\  |' (    ~   ,)'|
                     ((  |' /(.  '  .)\ |
                      \\_|_/ <_ _____> \______________
                       /   '-, \   / ,-'      ______  \
              b'ger   /      (//   \\)     __/     /   \
                                          './_____/
```
*/


/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https:/images//www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https:/images//www.qt.io/terms-conditions. For further
** information use the contact form at https:/images//www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "treemodel.h"
#include <QToolBar>
#include <QFile>
#include <QSettings>
#include <QDir>
#include <QStandardItemModel>
#include <windows.h>
#include "simpledelegate.h"
#include "aboutbox.h"
#include "domitem.h"
#include "fancydelegate.h"
#include "clickermodel.h"
#include "interpreter/interpreter.h"
#include "interpreter/interpreterwin64.h"

void MainWindow::refresh()
{
    loadSettings();
    loadDocument();
}

void MainWindow::loadDocument()
{

    current_filename = QDir::currentPath() + "/xml/sheme2.xml";
    ClickerDocument* doc = new ClickerDocument( QDir::currentPath() + "/xml/sheme2.xml");
    //doc->filter(doc->firstChild());
    model = new ClickerModel(*doc);
    view->setModel(model);
    view->expandAll();

    //init interpreter data
    interpreterData.rootNode = doc->firstChild().parentNode();
    interpreterData.currentNode = doc->firstChild().parentNode();
    interpreterData.defaultDocument = *doc;
    interpreterData.domDocument = *doc;

}

void MainWindow::setNextItem(QModelIndex& index)
{
    auto index2 = view->indexBelow(index);
    view->setCurrentIndex(index2);
}

void MainWindow::hideDeadRows()
{
    QStringList validNodes = {"hotkey","click","dblclick","type",
                               "keydown","keyup","scrollup","scrolldown",
                               "func"};
    view->setCurrentIndex(model->index(0,0));
    QModelIndex index = view->currentIndex();
    int n_rows = model->rowCount(index);
    QModelIndex index2;
    view->expandRecursively(index);
    int cnt = 1999;
    while(cnt > 0)
    {
        cnt--;
        index2 = view->indexBelow(view->currentIndex());
        view->setCurrentIndex(index2);
        if (index2.isValid())
        {
            const DomItem* item = static_cast<DomItem*>(index2.internalPointer());
            QDomElement  el = item->node().toElement();

            //qDebug() << "node " << item->node().nodeName();

            if( !validNodes.contains(el.nodeName()) &&
                    (item->node().childNodes().count() == 0) )
                view->setRowHidden(index2.row(), index2.parent(), true);
            else
                view->setRowHidden(index2.row(), index2.parent(), false);
        }
    }
}


void MainWindow::expandChildren(QDomNode& node, const QModelIndex &index, QTreeView *view)
{
    if (!index.isValid()) {
        return;
    }

    const QModelIndex &child = view->indexBelow(index);
    DomItem *item1 = (DomItem*)(index.internalPointer());

    if(item1)
    {
        qDebug() << __FUNCTION__ << "node below " << item1->node().nodeName();
        if( item1->node() == node )
        {
            //qDebug() << __FUNCTION__ << "found my node !";
            if (index.isValid())
            {
                view->setCurrentIndex(index);
                return;
            }
        }
    }
    // Recursively call the function for each child node.
    expandChildren(node, child, view);

    if (!view->isExpanded(index)) {
        view->expand(index);
    }
}


void MainWindow::next()
{
    //view->setCurrentIndex(view->currentIndex().sibling(i,0));
    //view->indexBelow(view->currentIndex());
    qDebug() << __FUNCTION__;
    // set Mutex
    //--------------------------------------------------
    expandChildren(interpreterData.currentNode, view->currentIndex(), view);
    //QModelIndex index;
    //--------------------------------------------------

    //view->expandRecursively(next_index);
    //view->setCurrentIndex(next_index);

}

void MainWindow::loadSettings()
{
    ClickerSettings::getInstance()->reload();
}

//-----------------------------------------------------------

void MainWindow::timerEvent(QTimerEvent* event)
{
    // perform some tests
    //hotKey("ctrl + a");
    //Sleep(100);
    //hotKey("ctrl + c");
    //Sleep(100);
    //hotKey("ctrl + shift + f");
    next();

}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    const QStringList headers({tr("#"), tr("Title"), tr("Description")});

    QFile file("default.txt");
    if(!file.open(QIODevice::ReadOnly))
        return;

    //TreeModel *model = new TreeModel(headers, file.readAll(), this);
    file.close();
    startTimer(50);


    //----------------------------------------------------
    loadDocument();
//--------------------------------------------------------------------
    loadSettings();
    //set view menu checks
    //--------------------------------------------------------------------
    // Create Controller
    // Init interpreter data
    InterpreterWin64* interpreter = new InterpreterWin64(&interpreterData);

    //connect(&controller, &Controller::sigSetNextItem, this, &MainWindow::setNextItem);
    qDebug() << "MainWindow::guiTHread id = " << QThread::currentThreadId();
    AbstractInterpreter* abstract_interpreter = (AbstractInterpreter*)(interpreter);
    //qDebug() << interpreter.getData()->domDocument.documentElement().nodeName();
    InterpreterDaemon* daemon = new InterpreterDaemon(abstract_interpreter);
    connect(daemon, &QThread::finished, daemon, &QObject::deleteLater);
    daemon->start();
    //emit controller->rund(abstract_interpreter);


    // Connect mainwindow with controller
    // Run Main Loop

    //--------------------------------------------------------------------

    //QStandardItemModel* model = new QStandardItemModel(4, 2);
    //view->horizontalHeader()->setStretchLastSection(true);

    QToolBar* toolbar = new QToolBar(this);
    QAction* playAction =  toolbar->addAction(QIcon(":/images/play.jpg"), "Play");
    QAction* refreshAction =  toolbar->addAction(QIcon(":/images/refresh-icon.png"), "Refresh");
    connect(refreshAction, &QAction::triggered, this, &MainWindow::refresh);
    addToolBar(toolbar);

    //view->setModel(model);

//    QHeaderView *verticalHeader = view->headerslotSetAttrs();
//    verticalHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
//    verticalHeader->setDefaultSectionSize(200);
//    //verticalHeader->resizeSection(2, 200);
//    view->header()->resizeSections(QHeaderView::Interactive);
//    view->header()->setMinimumSectionSize(200);
//    view->header()->setStretchLastSection(true);
//    view->header()->setCascadingSectionResizes(true);

    FancyDelegate* spinbox = new FancyDelegate(view);
    view->setItemDelegate(spinbox);

    //view->setItemDelegate(new SimpleDelegate(view));
    //view->setEditTriggers(QAbstractItemView::EditTrigger::AllEditTriggers);
    view->header()->setEditTriggers(QAbstractItemView::NoEditTriggers);


    connect(view, SIGNAL(activated()), this, SLOT(itemActivated()));
    view->parentWidget()->setStyleSheet("QTreeView::item { padding: 10px }; white-space:pre-wrap; word-wrap:break-word" );

    //
    for (int column = 1; column < model->columnCount(); ++column)
    {
        view->setColumnWidth(column, 500);
        //view->setColumnHidden(0, true);
    }

    view->setColumnWidth(0, 150);

    //hideDeadRows();


    connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    connect(view->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::updateActions);

    connect(actionsMenu, &QMenu::aboutToShow, this, &MainWindow::updateActions);
    connect(insertRowAction, &QAction::triggered, this, &MainWindow::insertRow);
    connect(insertColumnAction, &QAction::triggered, this, &MainWindow::insertColumn);
    connect(removeRowAction, &QAction::triggered, this, &MainWindow::removeRow);
    connect(removeColumnAction, &QAction::triggered, this, &MainWindow::removeColumn);
    connect(insertChildAction, &QAction::triggered, this, &MainWindow::insertChild);
    connect(actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(actionSave, &QAction::triggered, this, &MainWindow::save);

    updateActions();
}

void MainWindow::save()
{
    // [Collect model data to QString]
    QString textData;
    ClickerModel *model =  (ClickerModel*)view->model();
    model->save(current_filename);

}

void MainWindow::itemActivated(QModelIndex& index)
{
}

void MainWindow::about()
{
    AboutBox* aboutbox = new AboutBox(this);
    aboutbox->show();

}

void MainWindow::mousePressEvent(QMouseEvent* event)
{


}

void MainWindow::insertChild()
{
    const QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;


    for (int column = 0; column < model->columnCount(index); ++column) {
        const QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant(tr("[No data]")), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant(tr("[No header]")), Qt::EditRole);
    }

    view->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                            QItemSelectionModel::ClearAndSelect);
    updateActions();
}

bool MainWindow::insertColumn()
{
    QAbstractItemModel *model = view->model();
    int column = view->selectionModel()->currentIndex().column();

    // Insert a column in the parent item.
    bool changed = model->insertColumn(column + 1);
    if (changed)
        model->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);


    updateActions();

    return changed;
}

void MainWindow::insertRow()
{
    const QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    updateActions();

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        const QModelIndex child = model->index(index.row() + 1, column, index.parent());
        model->setData(child, QVariant(tr("[No data]")), Qt::EditRole);
    }
}

bool MainWindow::removeColumn()
{
    QAbstractItemModel *model = view->model();
    const int column = view->selectionModel()->currentIndex().column();

    // Insert columns in each child of the parent item.
    const bool changed = model->removeColumn(column);
    if (changed)
        updateActions();

    return changed;
}

void MainWindow::removeRow()
{
    const QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();
}

void MainWindow::updateActions()
{
    const bool hasSelection = !view->selectionModel()->selection().isEmpty();
    removeRowAction->setEnabled(hasSelection);
    removeColumnAction->setEnabled(hasSelection);

    const bool hasCurrent = view->selectionModel()->currentIndex().isValid();
    insertRowAction->setEnabled(hasCurrent);
    insertColumnAction->setEnabled(hasCurrent);

    if (hasCurrent) {
        view->closePersistentEditor(view->selectionModel()->currentIndex());

        const int row = view->selectionModel()->currentIndex().row();
        const int column = view->selectionModel()->currentIndex().column();
        if (view->selectionModel()->currentIndex().parent().isValid())
            statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
        else
            statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
    }
}
