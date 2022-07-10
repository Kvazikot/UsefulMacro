# -*- coding: utf-8 -*-

# + - - - + - + - -
# + - + - + copyright by Vladimir Baranov (Kvazikot)  <br>
# + - + - + email: vsbaranov83@gmail.com  <br>
# + - + - + github: https://github.com/Kvazikot/UsefulMacro/  <br>
# ```
#                           )            (
#                          /(   (\___/)  )\
#                         ( #)  \ ('')| ( #
#                          ||___c\  > '__||
#                          ||**** ),_/ **'|
#                    .__   |'* ___| |___*'|
#                     \_\  |' (    ~   ,)'|
#                      ((  |' /(.  '  .)\ |
#                       \\_|_/ <_ _____> \______________
#                        /   '-, \   / ,-'      ______  \
#               b'ger   /      (//   \\)     __/     /   \
#                                           './_____/
# ```


#!/usr/bin/env python

#############################################################################
##
## Copyright (C) 2013 Riverbank Computing Limited
## Copyright (C) 2010 Hans-Peter Jansen <hpj@urpla.net>.
## Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
## All rights reserved.
##
## This file is part of the examples of PyQt.
##
## $QT_BEGIN_LICENSE:BSD$
## You may use this file under the terms of the BSD license as follows:
##
## "Redistribution and use in source and binary forms, with or without
## modification, are permitted provided that the following conditions are
## met:
##   * Redistributions of source code must retain the above copyright
##     notice, this list of conditions and the following disclaimer.
##   * Redistributions in binary form must reproduce the above copyright
##     notice, this list of conditions and the following disclaimer in
##     the documentation and/or other materials provided with the
##     distribution.
##   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
##     the names of its contributors may be used to endorse or promote
##     products derived from this software without specific prior written
##     permission.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
## "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
## LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
## A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
## OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
## SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
## LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
## DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
## THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
## (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
## OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
## $QT_END_LICENSE$
##
###########################################################################

import cv2
from PyQt5.QtWebEngineWidgets import QWebEngineView 
from PyQt5.QtGui import QFontDatabase, QPainter
from PyQt5.QtCore import QFile, QIODevice, Qt, QTextStream, QUrl, QTimer
from PyQt5.QtWidgets import (QAction, QApplication, QLineEdit, QMainWindow,
        QSizePolicy, QStyle, QTextEdit)
from PyQt5.QtNetwork import QNetworkProxyFactory, QNetworkRequest
from PyQt5.QtWebEngineWidgets import QWebEnginePage
#from PyQt5.QtWebKitWidgets import QWebPage, QWebView
from button_detector import Dsp
from button_detector import mat2img
import numpy as np
import string
#import jquery_rc
from xml.dom.minidom import parseString

modes = {'html':0, 'image':1}
lang_code = {'eng':0, 'ukr': 1, 'jp':2, 'sw':5, 'sp': 4, 'rus': 6, 'can': 7}

def letter_range(start, stop="{", step=1):
    """Yield a range of lowercase letters.""" 
    for ord_ in range(ord(start.lower()), ord(stop.lower()), step):
        yield chr(ord_)


eng_alphabet = string.ascii_lowercase
rus_aphabet =  list(letter_range("а", "я"))
rus_aphabet = "".join(rus_aphabet)

print(eng_alphabet)
print(rus_aphabet)

letter_spacing = 5
font_size = 24
link_additional_fonts = "<link href=\"https://fonts.googleapis.com/css2?family=Lobster&display=swap\" rel=\"stylesheet\">"
html_code=f"<div style=\"font-family: 'Lobster'; letter-spacing:{letter_spacing}px\">{rus_aphabet}<br/>"
database = QFontDatabase()
html_code=f"<div style=\"font-family: 'Lobster'; letter-spacing:{letter_spacing}px\">{rus_aphabet}<br/>"
for family in database.families():
    html_code+=f"<div style=\"font-size:{font_size}px; font-family: '{family}'; letter-spacing:{letter_spacing}px\">{rus_aphabet}<br/>"
    #print(family)
html_code+="</div>"
html_code+=f"<div style=\"letter-spacing:{letter_spacing}px\">{eng_alphabet}<br/></div>"
style_block = "<style>  hr.new1 {   border-top: 1px solid red; }  </style>"       
html_template=""
html_template = f"<!DOCTYPE html><html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">{link_additional_fonts}{style_block}<title>title</title></head><body>{html_code}</body></html>"
page1 = 'file:///C:/Projects/UsefulClicker/py/saved_web_pages/myfile.html'
with open(".\saved_web_pages\myfile.html", "wb") as html_file:
    html_file.write(html_template.encode("utf-8"))
    html_file.close()
       
   
    
#doc.saveXML(".\saved_web_pages\simple_html.html")



class OcrWebSpyder(QMainWindow):
    def __init__(self, url):
        super(OcrWebSpyder, self).__init__()

        self.progress = 0
        self.dsp = Dsp()

        fd = QFile(":/jquery.min.js")

        if fd.open(QIODevice.ReadOnly | QFile.Text):
            self.jQuery = QTextStream(fd).readAll()
            fd.close()
        else:
            self.jQuery = ''

        QNetworkProxyFactory.setUseSystemConfiguration(True)

        self.view = QWebEngineView(self)
        self.view.load(url)
        self.view.titleChanged.connect(self.adjustTitle)
        self.view.loadProgress.connect(self.setProgress)
        self.view.loadFinished.connect(self.finishLoading)

        self.locationEdit = QLineEdit(self)
        self.locationEdit.setSizePolicy(QSizePolicy.Expanding,
                self.locationEdit.sizePolicy().verticalPolicy())
        self.locationEdit.returnPressed.connect(self.changeLocation)

        toolBar = self.addToolBar("Navigation")
        toolBar.addAction(self.view.pageAction(QWebEnginePage.Back))
        toolBar.addAction(self.view.pageAction(QWebEnginePage.Forward))
        toolBar.addAction(self.view.pageAction(QWebEnginePage.Reload))
        toolBar.addAction(self.view.pageAction(QWebEnginePage.Stop))
        toolBar.addWidget(self.locationEdit)

        viewMenu = self.menuBar().addMenu("&View")
        viewSourceAction = QAction("Page Source", self)
        viewSourceAction.triggered.connect(self.viewSource)
        viewMenu.addAction(viewSourceAction)

        effectMenu = self.menuBar().addMenu("&Effect")
        effectMenu.addAction("Highlight all links", self.viewSource)

        self.rotateAction = QAction(
                self.style().standardIcon(QStyle.SP_FileDialogDetailedView),
                "Turn images upside down", self, checkable=True,
                toggled=self.viewSource)
        #effectMenu.addAction(self.viewSource)

        toolsMenu = self.menuBar().addMenu("&Tools")
        toolsMenu.addAction("Remove GIF images", self.viewSource)
        self.setCentralWidget(self.view)
    
    def finishLoading(self):
        self.progress = 100
        QTimer.singleShot(1000, self.DrawDetectedContours)

    def viewSource(self):
        accessManager = self.view.page().networkAccessManager()
        request = QNetworkRequest(self.view.url())
        reply = accessManager.get(request)
        reply.finished.connect(self.slotSourceDownloaded)

    def slotSourceDownloaded(self):
        reply = self.sender()
        self.textEdit = QTextEdit()
        self.textEdit.setAttribute(Qt.WA_DeleteOnClose)
        self.textEdit.show()
        self.textEdit.setPlainText(QTextStream(reply).readAll())
        self.textEdit.resize(600, 400)
        reply.deleteLater()

    def changeLocation(self):
        url = QUrl.fromUserInput(self.locationEdit.text())
        self.view.load(url)
        self.view.setFocus()

    def adjustTitle(self):
        if 0 < self.progress < 100:
            self.setWindowTitle("%s (%s%%)" % (self.view.title(), self.progress))
        else:
            self.setWindowTitle(self.view.title())

    def setProgress(self, p):
        self.progress = p
        self.adjustTitle()
    
    def DrawDetectedContours(self):
        self.dsp.detectButtons(0, kernel_size=4)
        w = self.dsp.areaImg.shape[1]
        h = self.dsp.areaImg.shape[0]
        img = np.zeros((w,h,3), dtype=np.uint8)
        for c in self.dsp.contours_filtred:
            cv2.drawContours(img, [c], 0, (255,0,0), thickness=2)
        cv2.imshow("w0", img)

    def closeEvent(self, a0):        
        cv2.destroyWindow("w0") 
        cv2.destroyWindow("w1") 


if __name__ == '__main__':

    import sys
    
    app = QApplication(sys.argv)
    url = QUrl(page1)   

    browser = OcrWebSpyder(url)
    scr=app.screens()[0]
    browser.setGeometry(scr.geometry())

    browser.show()

    sys.exit(app.exec_())
