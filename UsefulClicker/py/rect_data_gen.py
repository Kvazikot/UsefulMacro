# -*- coding: utf-8 -*-
"""
Created on Sun Jun  5 12:24:38 2022

@author: HP
"""
import os
import sys
from PyQt5.QtWidgets import QWidget, QApplication, QLabel
from PyQt5.QtGui import QPainter, QColor, QFont, QImage, QPixmap, QCursor 
from PyQt5.QtCore import Qt, QRect, QPoint 

class RectsGenerator(QWidget):

    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.screen_num = 0
        self.rects = []
        #self.setWindowOpacity(0.8)
        self.tipLabel = QLabel(self)
        self.image = QImage('./rect_images\\00.06.36.730.png')
        self.tipLabel.setStyleSheet("font-size:24pt;")
        #tip+="F1 - save selected rectangle area to ./square dir"
        tip="F1 - start collecting training samples\n"
        tip+="F2 - train neural network\n"
        tip+="F3 - detect squares\n"
        tip+="PRESS left mouse button if its a RECTANGLE\n"
        tip+="PRESS left mouse button if its NOT a RECTANGLE\n"
        tip+="q - quit this window"
        self.tipLabel.setAlignment(Qt.AlignLeft)
        self.tipLabel.setText(tip)
        self.setWindowTitle('Drawing')
        self.setMouseTracking(1)
        self.mpos = QPoint(1,1)
        #sys.exit(0)
        self.show()
        self.startTimer(100)

    def keyPressEvent(self, event):
        if event.key() == Qt.Key_Q:
            self.close()
            

    def mouseMoveEvent(self, event):
        self.mpos = event.pos()
        
    def timerEvent(self, event):
        self.repaint()
            
    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            now = datetime.datetime.now()
            current_time = now.strftime("square%H.%M.%S.png")
            cv2.imwrite('./square/{t}.png'.format(t=current_time), m_piece)            
        
    def showEvent(self, a0):
        rect2 = self.rect()
        #if len(QApplication.screens()) < self.screen_num :
        #   return
        print(len(QApplication.screens()))
        screen = QApplication.screens()[self.screen_num]
        self.setGeometry(screen.geometry())

        #rect2.setTopLeft(self.rect().center())
        #rect2.setTop(rect2.center().y())
        #rect2.setWidth(rect2.width()/2)
        #rect2.setHeight(rect2.height()/2)
        #self.tipLabel.setGeometry(rect2)
    
    def closeEvent(self, a0):        
        cv2.destroyWindow("w0") 
        
    def paintEvent(self, event):
        qp = QPainter()
        qp.begin(self)
        #qp.drawImage(0,0,self.dsp.m_gradient)
        #qp.fillRect(self.rect(), QColor(1,1,1,110))        
        

        for r in self.rects:
            if r.contains(self.mpos):
                qp.fillRect(r, QColor(244,1,1,110))
            else:
                qp.fillRect(r, QColor(1,244,1,110))
            
        qp.end()



def main():
    app = QApplication(sys.argv)
    widget = RectsGenerator()
    widget.show()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()