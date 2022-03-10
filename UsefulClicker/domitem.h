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

#ifndef DOMITEM_H
#define DOMITEM_H

#include <QDomNode>
#include <QHash>
#include <QPoint>
/*
 *  fragment of an XML sheme
<func name = "SetUrl" arg0="https://www.youtube.com/results?search_query=" comment="function sets url in chrome browser" >
  <arg n="0" comment="url"> https://www.youtube.com/results?search_query= </arg>
  <click area="Rect(0,1,200,200)">
  <click x="10" y="20">
  <dblclick x="10" y="20">
  <mouseup x="10" y="20" delay_fixed="1000" delay_random="300" repeat="10">
  <mousedown x="10" y="20">
  <hotkey> ctrl + C </hotkey>
  <type> this is text to insert . There $(arg0) is python variable  </type>
  <keydown arg0="F6"/>
  <keyup arg0="F6"/>
  <scrollup x="10" y="20"/>
  <scrolldown />
</func>
*/

class DomItem
{
public:
    DomItem(const QDomNode &node, int row, DomItem *parent = nullptr);
    ~DomItem();
    DomItem *child(int i);
    DomItem *parent();
    QDomNode node() const;
    int row() const;
    virtual int parse();
    bool setData(int column, const QString &value);


    // common parametres for every clicker node
    // parsed in class DomItem via parse() procedure
    int delay_fixed;
    int delay_random;
    int repeat;

private:
    QDomNode domNode;
    QHash<int, DomItem *> childItems;
    DomItem *parentItem;
    int rowNumber;

};


class ClickItem : public DomItem
{
public:
    QPoint point;
    ClickItem(const QDomNode &node, int row, DomItem *parent = nullptr);
    ~ClickItem();
    int parse();
};

#endif // DOMITEM_H
