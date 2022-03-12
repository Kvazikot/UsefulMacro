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

#include "domitem.h"

#include <QtXml>
#include <QRegularExpression>
#include "xml/xmlstreamer.h"

DomItem::DomItem(const QDomNode &node, int row, DomItem *parent)
    : domNode(node),
      parentItem(parent),
      rowNumber(row)
{

}

DomItem::~DomItem()
{
    qDeleteAll(childItems);
}

QDomNode DomItem::node() const
{
    return domNode;
}

DomItem *DomItem::parent()
{
    return parentItem;
}

DomItem *DomItem::child(int i)
{
    DomItem *childItem = childItems.value(i);
    if (childItem)
        return childItem;

    // if child does not yet exist, create it
    if (i >= 0 && i < domNode.childNodes().count()) {
        QDomNode childNode = domNode.childNodes().item(i);
        childItem = new DomItem(childNode, i, this);
        childItems[i] = childItem;
    }
    return childItem;
}

int DomItem::row() const
{
    return rowNumber;
}

int DomItem::parse()
{
    auto a = node().toElement().attribute("delay_fixed");
    bool ok = false;
    if(!a.isNull())
    {
       delay_fixed = a.toInt(&ok);
      // qDebug() << node().nodeName() << " delay_fixed = " << delay_fixed;
    }

    a = node().toElement().attribute("delay_random");
    ok = false;
    if(!a.isNull())
       delay_random = a.toInt(&ok);

    a = node().toElement().attribute("repeat");
    ok = false;
    if(!a.isNull())
       repeat = a.toInt(&ok);



    return 0;
}

// Parse value and set data
// pack additional arguments to QVariant
// QVariant( QVector<QVariant> )
// {"LeftClick", "QPoInt(0,0)" }
// {"RightClick", "QRect(0,0,100,100)" }

bool DomItem::setData(int column, const QVariant &value, int role)
{
    /*replace node if neccessary*/
    //QDomNode child = node().cloneNode(true);
    //child.setNodeValue(value);

    // parse attrs
    // example: repeat="10" x="10" y="20" delay_fixed="1000" delay_random="300"
    int n_attrs = 0;
    if(column == 2 || column == 1)
    {
        //QStringList attrlist = value.toString().split("=");
         QRegularExpression re("([\\S]+)[=]([\\S]+)");

         int pos = 0;
         bool hasMatch = true;
         while( hasMatch )
         {
             QRegularExpressionMatch match = re.match(value.toString(), pos, QRegularExpression::NormalMatch);
             if (match.hasMatch()) {
                 pos = match.capturedEnd(0);
                 n_attrs++;
                 hasMatch = true;
                 QString key = match.captured(1);
                 QString value1 = match.captured(2);
                 if(value1.contains("\""))
                    value1 = value1.mid(1, value1.size()-2);
                 if(key.contains("\""))
                     key = key.mid(1, value1.size()-2);

                 qDebug() << "readed " << key << " " << node().toElement().attribute(key);
                 node().toElement().setAttribute(key, value1);
                 qDebug() << key << " " <<  value1 << ",";
             }
             else
                 hasMatch = false;
         }

    }
    if(column == 1 || role != Qt::EditRole)
        node().toElement().setTagName(value.toString());

    //node().replaceChild(child, node());
    qDebug() << "DomItem::setData" << " " <<  column << "," << value << " role " << role;
    return true;
}

