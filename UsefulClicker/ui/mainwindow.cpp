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

#include "ui/mainwindow.h"
#include "dialogtype.h"
#include <QToolBar>
#include <QFile>
#include <QPushButton>
#include <QSettings>
#include <QLabel>
#include <QDir>
#include <QInputDialog>
#include <QTimer>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QPainter>
#include <windows.h>
#include "model/treemodel.h"
#include "model/simpledelegate.h"
#include "model/fancydelegate.h"
#include "model/clickermodel.h"
#include "model/domitem.h"
#include "aboutbox.h"
#include "settings/clickersettings.h"
#include "xml/clickerdocument.h"
#include "ui/shelldialog.h"
#include "interpreter/interpreter.h"
#include "interpreter/interpreterwin64.h"

MainWindow* MainWindow::instance;
static InterpreterWin64* interpreter = 0;
static QComboBox* functionSelector;
QString MainWindow::current_filename;
extern void MouseClick(QPoint coordinates, Qt::MouseButton button);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    setWindowTitle("UsefulClicker");
    instance = this;

    const QStringList headers({tr("#"), tr("Title"), tr("Description")});

    startTimer(50);
    n_cycle = 0;
    current_filename = DEFAULT("last_sheme").toString();
    //----------------------------------------------------
    //QString xml = "<xml> <error message=\"You have xml error. This is a default xml. Check xml document\"> </xml>";
    QString xml = "<?xml version='1.0'?> <xml error=\"This is default document. Make sure you load right xml.\">  </xml>";
    bool ok  = (*(QDomDocument*)&defaultDoc).setContent(xml);
    qDebug() << "defaultDoc.setContent " << ok;
    setDoc(&defaultDoc);


    loadDocument(current_filename);
    //--------------------------------------------------------------------
    loadSettings();
    interpreter = new InterpreterWin64();

    //--------------------------------------------------------------------

    QToolBar* toolbar = new QToolBar(this);
    playAction =  toolbar->addAction(QIcon(":/images/play.png"), "Play");
    pauseFlag = true;

    QAction* refreshAction =  toolbar->addAction(QIcon(":/images/refresh-icon.png"), "Refresh");
    connect(refreshAction, &QAction::triggered, this, &MainWindow::reload);

    QLabel* label = new QLabel(this);
    label->setText("<b>Fucntion List</b>-->");

    functionSelector = new QComboBox(this);
    QStringList list;
    getDoc()->getFunctionsList(doc->documentElement(),list);
    functionSelector->addItems(list);
    functionSelector->setMinimumWidth(200);
    toolbar->addWidget(label);
    toolbar->addWidget(functionSelector);
    connect(functionSelector, SIGNAL(currentTextChanged(const QString&)), this, SLOT(functionSelected(const QString&)));

    QAction* newFunAction =  toolbar->addAction(QIcon(":/images/new_fun.png"), "New fun");
    connect(newFunAction, &QAction::triggered, this, &MainWindow::new_fun);

    QLabel* xmlEditorStatus = new QLabel(this);
    connect(xmlEditor, SIGNAL(updateStatusBar(const QString&, bool)), this, SLOT(updateStatus(const QString&, bool)));
    //updateStatusBar
    statusBar()->addWidget(xmlEditorStatus);

    connect(xmlEditor, SIGNAL(textChanged()), this, SLOT(xmlChanged()));


    //connect(playAction, &QAction::triggered, daemon, &InterpreterDaemon::terminate);
    connect(playAction, &QAction::triggered, this, &MainWindow::pause);
    connect(actionOpen, &QAction::triggered, this, &MainWindow::openXml);
    addToolBar(toolbar);

    FancyDelegate* spinbox = new FancyDelegate(view);
    view->setItemDelegate(spinbox);
    view->header()->setEditTriggers(QAbstractItemView::NoEditTriggers);


    QImage image(":/images/vector-star-icon.png");
    QStandardItem *item = new QStandardItem();
    //item->setData(QVariant(QPixmap::fromImage(image)), Qt::DecorationRole);
    model->itemData(model->index(0,0))[Qt::DecorationRole].setValue(QPixmap::fromImage(image));

    for (int row = 0; row < model->rowCount(); ++row)
    {
        QMap<int,QVariant> roles;
        roles[Qt::DecorationRole] = QVariant(QPixmap::fromImage(image));
        model->setItemData(model->index(row,0),roles);
        model->setHeaderData(0,Qt::Orientation::Horizontal,roles[Qt::DecorationRole],Qt::DecorationRole);
    }
 //
    connect(view, SIGNAL(clicked(const QModelIndex &)), this, SLOT(itemActivated(const QModelIndex &)));
    connect(view, SIGNAL(activated()), this, SLOT(itemActivated()));
    view->parentWidget()->setStyleSheet("QTreeView::item { padding: 10px }; white-space:pre-wrap; word-wrap:break-word" );

    for (int column = 1; column < model->columnCount(); ++column)
        view->setColumnWidth(column, 500);

    view->setColumnWidth(0, 130);

    connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    connect(view->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::updateActions);

    connect(actionsMenu, &QMenu::aboutToShow, this, &MainWindow::updateActions);
    connect(insertRowAction, &QAction::triggered, this, &MainWindow::insertRow);
    connect(removeRowAction, &QAction::triggered, this, &MainWindow::removeRow);
    connect(insertChildAction, &QAction::triggered, this, &MainWindow::insertChild);
    connect(actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(actionSave, &QAction::triggered, this, &MainWindow::save);
    connect(view,SIGNAL(currentChanged(const QModelIndex &current, const QModelIndex &previous)),
            this,SLOT(elementClicked(const QModelIndex& current, const QModelIndex& previous)));

    updateActions();
}



void MainWindow::xmlChanged()
{

}

void drawPlus(QImage& act_image, QPixmap& plus)
{
    QPainter painter(&act_image);
    QRect rect1 = act_image.rect();
    QRect rect2 = rect1;
    rect2.setWidth(300);
    rect2.setHeight(300);
    rect2.setTop(rect1.height()-rect2.height());
    rect2.setBottom(rect1.bottom());
    rect2.moveLeft(300);
    //painter.fillRect(rect2,Qt::red);
    painter.drawPixmap(rect2, plus);
}



void MainWindow::contextMenuActionTriggered()
{
    QAction* act = static_cast<QAction*>(sender());
    qDebug() << __FUNCTION__ << act->text();
    if( action_map.contains(act->text()) )
    {
        DialogType dialog_type = action_map[act->text()];
        createDialog(this, dialog_type);
    }
}

QAction* MainWindow::createAction(QString icon, QString text, bool addPlusFlag)
{
    static QPixmap plus_image(":/images/plus.png");
    QImage act_image = QImage(icon);
    act_image = act_image.scaled(600,600);
    if( addPlusFlag )
        drawPlus(act_image, plus_image);
    QAction* act =  new QAction(QIcon(QPixmap::fromImage(act_image)),text);
    connect(act, SIGNAL(triggered()), this, SLOT(contextMenuActionTriggered()));
    return act;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(createAction(":/images/copy-icon.png", "Copy this ", false));
    menu.addAction(createAction(":/images/paste-icon.png", "Paste after this", false));
    menu.addSeparator();
    menu.addAction(createAction(":/images/mouse_left_click.png", "Add left click"));
    menu.addAction(createAction(":/images/mouse_right_click.png", "Add right click"));
    menu.addAction(createAction(":/images/mouse_scroll.png", "Add scroll down"));
    menu.addAction(createAction(":/images/mouse_scroll.png", "Add scroll up"));
    menu.addSeparator();
    menu.addAction(createAction(":/images/keyboard_icon.png", "Add keydown action"));
    menu.addAction(createAction(":/images/type.png", "Add type"));
    menu.addAction(createAction(":/images/Terminal-icon.png", "Add Shell"));
    menu.addAction(createAction(":/images/area_icon.png", "Add image click"));
    menu.addSeparator();
    menu.addAction(createAction(":/images/clock-icon.png", "Set delay for this"));
    menu.exec(event->globalPos());
}

void MainWindow::new_fun()
{
    qDebug() << __FUNCTION__;
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Function name:"), QLineEdit::Normal,
                                         xmlEditor->genFunName(), &ok);
    if (ok && !text.isEmpty())
        xmlEditor->newFun(text);

}

static QPushButton* applyButton = 0;
static QPushButton* apply_button2 = 0;
static QLabel* errorLabel = 0;

void MainWindow::updateStatus(const QString& text, bool applyChangesFlag)
{
    if( text.contains("error"))
    {
        if(errorLabel!=0)
        {
            statusBar()->removeWidget(errorLabel);
            delete errorLabel;
            errorLabel = 0;
        }
        errorLabel = new QLabel(this);
        errorLabel->setText(text);
        errorLabel->setStyleSheet("background-color: rgb(255, 0, 0); color: rgb(255, 255, 255);");
        statusBar()->addWidget(errorLabel, width()-errorLabel->width());

    }
    else
    {
        if(errorLabel!=0)
        {
            statusBar()->removeWidget(errorLabel);
            delete errorLabel;
            errorLabel = 0;
        }
        if( applyChangesFlag && applyButton == 0 )
        {
            applyButton = new QPushButton(this);
            applyButton->setText("Apply changes");
            connect(applyButton, SIGNAL(clicked()), this, SLOT(applyChangesXml()));
            statusBar()->addWidget(applyButton, width()-applyButton->width());

        }
    }


}

void MainWindow::applyChangesXml()
{
    xmlEditor->applyChanges();
    statusBar()->removeWidget(applyButton);
    applyButton = 0;

    auto doc = *model->getDoc();
    delete model;
    model = new ClickerModel(doc);
    view->setModel(model);
}

void MainWindow::applyChanges()
{
    auto current = view->currentIndex();
    QDomNode node = model->getNodeByIndex(current);
    node.toElement().setAttribute("comment", commentEditor->toPlainText());
    if( commentEditor->toPlainText().size() == 0 )
        node.toElement().removeAttribute("comment");
    statusBar()->removeWidget(apply_button2);
    apply_button2 = 0;
}

void MainWindow::commentChanged()
{
    auto current = view->currentIndex();
    QDomNode node = model->getNodeByIndex(current);
    QString old_comment;
    if( node.toElement().hasAttribute("comment") )
        old_comment = node.toElement().attribute("comment");
    if( old_comment!=commentEditor->toPlainText() )
    {
      //node.toElement().setAttribute("comment", commentEditor->toPlainText());
        //statusBar()->widge
        if( apply_button2 == 0 )
        {
            apply_button2 = new QPushButton(this);
            apply_button2->setText("Apply changes");
            connect(apply_button2, SIGNAL(clicked()), this, SLOT(applyChanges()));
            statusBar()->addWidget(apply_button2);
        }
    }
}

void MainWindow::itemActivated(const QModelIndex &)
{
    auto current = view->currentIndex();
    const int row =  current.row();
    const int column = current.column();
    qDebug() << "Clicked at " << row << column;


    statusBar()->removeWidget(errorLabel);

    QDomNode node = model->getNodeByIndex(current);
    if( node.toElement().hasAttribute("comment") )
        commentEditor->setText(node.toElement().attribute("comment"));
    else
        commentEditor->setText(node.toElement().attribute(""));

    connect(commentEditor, SIGNAL(textChanged()), this, SLOT(commentChanged()) );

    if( node.nodeName() == "func" )
    {
        auto fun_name = node.toElement().attribute("name");
        auto func_body_text = getDoc()->getFunction(fun_name);
        xmlEditor->setFuncNode(node);
        xmlEditor->enableChangeEvent(false);
        xmlEditor->clear();
        xmlEditor->setText(func_body_text);
        xmlEditor->enableChangeEvent(true);
    }
    if( node.parentNode().nodeName() == "func" )
    {
        node = node.parentNode();
        auto fun_name = node.toElement().attribute("name");
        auto func_body_text = getDoc()->getFunction(fun_name);
        xmlEditor->setFuncNode(node);
        xmlEditor->enableChangeEvent(false);
        xmlEditor->clear();
        xmlEditor->setText(func_body_text);
        xmlEditor->enableChangeEvent(true);
    }
    //xmlEditor->setText();
}

AbstractInterpreter* MainWindow::getInterpreter()
{
    return interpreter;
}

void MainWindow::functionSelected(const QString&)
{
    auto current = view->currentIndex();
    QDomNode node = model->getNodeByIndex(current);
    auto func_body_text = getDoc()->getFunction(functionSelector->currentText());
    xmlEditor->setFuncNode(node);
    xmlEditor->clear();
    xmlEditor->setText(func_body_text);

}

MainWindow* MainWindow::getInstance()
{
    return instance;
}


void MainWindow::openXml()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setDirectory(QDir::currentPath() + "/xml");
    QStringList fileNames;
    if (dialog.exec())
    {
        fileNames = dialog.selectedFiles();
        if( fileNames.size()>0 )
          loadDocument(fileNames[0]);
    }


}

void MainWindow::pause()
{
    pauseFlag = ! pauseFlag;
    if( pauseFlag )
       playAction->setIcon(QIcon(":/images/play.png"));
    else
    {
       playAction->setIcon(QIcon(":/images/pause.jpg"));
    }
}

void MainWindow::reload()
{
    reloadFromFile(current_filename);
}

// reload from memory (original document)
void MainWindow::reloadFromMemory()
{
    loadSettings();
    //loadDocument(current_filename);
    model->getDoc()->reload();
    ClickerDocument doc = *model->getDoc();
    delete model;
    model = new ClickerModel(doc);
    view->setModel(model);


}

// reload from file
void MainWindow::reloadFromFile(QString& filename)
{
    loadSettings();
    current_filename = filename;
    loadDocument(current_filename);
}

ClickerDocument* MainWindow::getDoc()
{
    return doc;
}

void MainWindow::setDoc(ClickerDocument* _doc)
{
    doc = _doc;
    xmlEditor->setDoc(doc);
}


void MainWindow::loadDocument(QString filename)
{
    current_filename = filename;
    SAVE_DEFAULT("last_sheme", filename);
    delete model;
    ClickerDocument* doc = new ClickerDocument(filename);
    if( doc->isLoaded )
    {
        setDoc(doc);
        model = new ClickerModel(*doc);
        view->setModel(model);
        view->collapseAll();
        view->expand(view->currentIndex());
        //view->expandAll();
    }
    else
    {
        setDoc(&defaultDoc);
        model = new ClickerModel(defaultDoc);
        view->setModel(model);
        view->expandAll();
    }
}

void MainWindow::setNextItem(QModelIndex& index)
{
    auto index2 = view->indexBelow(index);
    view->setCurrentIndex(index2);
}

void MainWindow::setCurentDomNode(QDomNode& currentNode)
{
    traverseTree(model->index(0,0), currentNode, view );
}

void MainWindow::traverseTree(const QModelIndex &index, const QDomNode& targetNode, QTreeView *view)
{
    if (!index.isValid()) {
        return;
    }

    const QModelIndex &child = view->indexBelow(index);
    DomItem *item1 = (DomItem*)(index.internalPointer());

    if(item1)
    {
        if (index.isValid())
        {
            view->setCurrentIndex(view->indexBelow(index));
            if( item1->node() == targetNode)
                return;
        }
    }

    // Recursively call the function for each child node.
    traverseTree(child, targetNode, view);

    if (!view->isExpanded(index)) {
        view->expand(index);
    }
}

void MainWindow::loadSettings()
{
    ClickerSettings::getInstance()->reload();
}

//-----------------------------------------------------------

void MainWindow::timerEvent(QTimerEvent* event)
{
    event->accept();
}

void MainWindow::saveToFile(QString& filename)
{
    QString textData;
    ClickerModel *model =  (ClickerModel*)view->model();
    model->save(filename);

}

void MainWindow::about()
{
    AboutBox* aboutbox = new AboutBox(this);
    aboutbox->show();

}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    event->accept();
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


void MainWindow::insertRow()
{
    const QModelIndex index = view->currentIndex();
    QRect rect = view->visualRect(index);
    QPoint center = view->mapToGlobal(rect.center());
    center.setY(center.y()+rect.height());
    auto parentItem = static_cast<DomItem*>(index.internalPointer());
    QDomNode newNode = parentItem->node().cloneNode(false);
    parentItem->node().parentNode().toElement().insertAfter(newNode, parentItem->node());
    //model->domDocument.
    save();
    reloadFromFile(current_filename);
    MouseClick(center, Qt::MouseButton::LeftButton);
}
void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    event->globalPosition();
}

void MainWindow::removeRow()
{
    const QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();
    model->removeRow(index.row(), index.parent());
}

void MainWindow::updateActions()
{
    const QModelIndex current = view->selectionModel()->currentIndex();
    const int row =  current.row();
    const int column = current.column();
    qDebug() << "Clicked at " << row << column;
}



