/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
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

/*
    delegate.cpp

    A delegate that allows the user to change integer values from the model
    using a spin box widget.
*/

#include "model/fancydelegate.h"
#include "ui/autocompleteeditor.h"
#include "model/clickermodel.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QAbstractItemModel>
//! [0]
FancyDelegate::FancyDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}
//! [0]

//! [1]
QWidget *FancyDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &/* option */,
                                       const QModelIndex &index/* index */) const
{
    QWidget* widget = 0;
    if( index.column() == 1 )
    {
        AutocompleteEditor* comboBox = new AutocompleteEditor(parent);
        widget = comboBox;
    }
    else
    {
        QTextEdit* text_edit = new QTextEdit(parent);
        widget = text_edit;
    }

    return widget;
}
//! [1]

//! [2]
void FancyDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    if( index.column() == 1 )
    {
        AutocompleteEditor* edit = static_cast<AutocompleteEditor*>(editor);
        QString value = index.model()->data(index, Qt::EditRole).toString();
        edit->setValue(value);
    }
    else
    {
        QTextEdit* edit = static_cast<QTextEdit*>(editor);
        QString value = index.model()->data(index, Qt::EditRole).toString();
        edit->setText(value);
    }
}
//! [2]


bool isFiltered(QString text)
{
    QStringList filters = {"hot key sequence" };

    for(auto f : filters )
    {
        if (text.contains(f)) return true;
    }

    return false;
}

//! [3]
void FancyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    if( index.column() == 1 )
    {
        AutocompleteEditor* edit = static_cast<AutocompleteEditor*>(editor);
        if(!isFiltered(edit->currentText()))
        {
            model->setData(index, edit->currentText(), Qt::EditRole);
            ClickerModel* model2 = (ClickerModel*)model;
            //QModelIndex i2 = model2->index(index.row(), 2);
            //model->setData(i2, edit->getAttrsString(), Qt::EditRole);
        }
        //index.model()->data()
        //edit->setItemText(0, value);

    }
    else
    {
        if( QString(editor->metaObject()->className()).contains("QLineEdit"))
        {
            qDebug() << editor->metaObject()->className();
            QLineEdit* edit = static_cast<QLineEdit*>(editor);
            QString value = index.model()->data(index, Qt::EditRole).toString();
            qDebug() << __FUNCTION__ << edit->text();
            model->setData(index, edit->text(), Qt::EditRole);
        }
    }
}
//! [3]

//! [4]
void FancyDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex& index/* index */) const
{
    editor->setGeometry(option.rect);
}
//! [4]