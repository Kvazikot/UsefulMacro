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

#include "clickermodel.h"
#include "model/domitem.h"
#include "settings/clickersettings.h"
#include <QtXml>
#include <QPixmap>
#include <QImage>
#include <QIcon>

#define im(res_name) QIcon(QPixmap::fromImage(QImage(res_name).scaled(500,500)));

ClickerModel::ClickerModel(const ClickerDocument &document, QObject *parent)
    : QAbstractItemModel(parent),
      document(document),
      rootItem(new DomItem(document, 0))
{
    qDebug() << "hideCodeTags = " << _("hideCodeTags");
    iconMap["hotkey"] = im(":/images/keyboard_icon.png");
    iconMap["click"] = im(":/images/mouse_default.png");
    iconMap["leftclick"] = im(":/images/mouse_left_click.png");
    iconMap["rightclick"] = im(":/images/mouse_right_click.png");
    iconMap["scrollup"] = im(":/images/mouse_scroll.png");
    iconMap["scrolldown"] = im(":/images/mouse_scroll.png");
    iconMap["shell"] = im(":/images/Terminal-icon.png");
    iconMap["img"] = im(":/images/area_icon.png");
}

ClickerModel::~ClickerModel()
{
    delete rootItem;
}

int ClickerModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant ClickerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::DecorationRole)
        return QVariant();


    const DomItem *item = static_cast<DomItem*>(index.internalPointer());
    DomItem *item1 = (DomItem*)(index.internalPointer());
    item1->parse();

    const QDomNode node = item->node();

    switch (index.column()) {
        case 0:
        {
            //if (role == Qt::DisplayRole) {
                //qDebug() << "role " << role;
                if(node.nodeName() == "click")
                {
                    if( node.toElement().attribute("button") == "left")
                        return iconMap["leftclick"];
                    if( node.toElement().attribute("button") == "right")
                        return iconMap["rightclick"];
                }
                return  iconMap[node.nodeName()];
        }
            //}
            //return  QString::number(index.row()); //+ " " + QString::number(rand());//
        case 1:
            return node.nodeName();
        case 2:
        {
            const QDomNamedNodeMap attributeMap = node.attributes();
            QStringList attributes;
            for (int i = 0; i < attributeMap.count(); ++i) {
                QDomNode attribute = attributeMap.item(i);
                attributes << attribute.nodeName() + "=\""
                              + attribute.nodeValue() + '"';
            }
            return attributes.join(' ');
        }
        case 3:
            return node.nodeValue().split('\n').join(' ');
        default:
            break;
    }
     return item->node().nodeValue();
}


bool ClickerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //if (role != Qt::EditRole)
    //    return false;

    qDebug() << "ClickerModel::setData ";
    DomItem *item1 = (DomItem*)(index.internalPointer());
    bool result=false;
    QString v =  value.toString() ;

    if(index.column() == 0)
    {
        QImage mEditImage = QImage(":/images/refresh-icon.png");
        auto icon = QVariant(QIcon(QPixmap::fromImage(mEditImage.scaled(100,100))));
        item1->setData(0, icon, Qt::DecorationRole);
    }
    if(index.column() == 1)
    {
        auto el = item1->node().toElement();


        if( v.contains("ctrl") || v.contains("shift") || v.contains("win"))
        {
            el.setTagName("hotkey");
            el.setAttribute("hotkey", value.toString());
        }
        if( v.contains("scroll") )
            el.setTagName(v);
        if( v.contains("button") )
        {
              el.setTagName("click");
              if(v.contains("Left"))
                 el.setAttribute("button", "left");
              else
                  el.setAttribute("button", "right");
              result = item1->setData(1, "click", role);
        }

        if( v.contains("area") )
        {
            //auto el = item1->node().toElement();
            //el.setAttribute("area", "asasas");
            result = item1->setData(2, value, role);
        }
        if( v.contains("cmd") )
        {
            el.setTagName("shell");
            el.setAttribute("bg", "1");
            el.setAttribute("showConsole", "1");
            //QStringList key_value = v.split("=");
            int pos = v.indexOf("=");
            QString value = v.mid(pos+2, v.size() - pos - 2);
            el.setAttribute("cmd", value);

            /* to set text body of <shell> tag
            * i.e. text between <shell> </shell>
            * use this pieace of code
            auto span = el;
                    QString str;
                    QTextStream stream(&str);
                    span.save(stream, 4);
                    //str.replace();
                    // </tspan>
                    static QRegularExpression re("[>]([\\S]+)</>");
                    str.replace(re, ">" + v + "</shell>");

                    auto doc = span.toDocument();
                    doc.setContent(str);
                    item1->node().parentNode().replaceChild(doc, span);
            */


        }
        result = item1->setData(2, value, role);

    }
    qDebug() << __FUNCTION__ << " " << value;

    if (result)
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

    return result;
}


//! [5]
Qt::ItemFlags ClickerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}
//! [5]

//! [6]
QVariant ClickerModel::headerData(int section, Qt::Orientation orientation,
                              int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0:
                return tr("#");
            case 1:
                return tr("Name");
            case 2:
                return tr("Attributes");
            case 3:
                return tr("Value");
            default:
                break;
        }
    }
    return QVariant();
}
//! [6]

//! [7]
QModelIndex ClickerModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    DomItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<DomItem*>(parent.internalPointer());
//! [7]

//! [8]
    DomItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

//! [8]

//! [9]
QModelIndex ClickerModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    DomItem *childItem = static_cast<DomItem*>(child.internalPointer());
    DomItem *parentItem = childItem->parent();

    if (!parentItem || parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}
//! [9]

//! [10]
int ClickerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    DomItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<DomItem*>(parent.internalPointer());

    return parentItem->node().childNodes().count();
}
//! [10]


bool ClickerModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    beginInsertColumns(parent, position, position + columns - 1);
    const bool success = insertColumns(position, columns, parent);
    endInsertColumns();

    return success;
}

bool ClickerModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    auto parentItem = static_cast<DomItem*>(parent.internalPointer());
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    const bool success = insertRows(position, rows, parent);
    endInsertRows();

    return success;
}

/*

bool ClickerModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    beginRemoveColumns(parent, position, position + columns - 1);
    const bool success = removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool ClickerModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}
*/


void  ClickerModel::save(QString filename)
{
    QFile f(filename);
    //QFile f_bak(filename+".bak");
    if( f.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream ts(&f);
        document.Save(ts);
        f.close();
    }


}
