# -*- coding: utf-8 -*-
"""
Created on Sun Jul  3 11:44:21 2022

@author: HP
"""
import subprocess
import datetime
from collections import deque
from button_detector import Dsp
from button_detector import mat2img
import os
import re
import sys
import random
import cv2
import numpy as np
from  cv2 import connectedComponentsWithStats
from PyQt5.QtWidgets import QWidget, QApplication, QLabel, QTextEdit, QHBoxLayout, QVBoxLayout, QPushButton
from PyQt5.QtGui import QPainter, QColor, QFont, QImage, QPixmap, QCursor, QPainterPath, QPolygonF
from PyQt5.QtCore import Qt, QRect, QPoint, QTimer

def clamp(minvalue, value, maxvalue):
    return max(minvalue, min(value, maxvalue))

color_tab1 = [(255,255,255),(255,0,0),(255,255,0),(255,0,255),(0,0,255),
              (0,255,255),(255,128,0),(128,255,0),(128,0,255),(0,0,128)]



#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------

class ZommedTextWidget(QWidget):
    
    def __init__(self, im):
        QWidget.__init__(self)
        im = cv2.resize(im,(im.shape[1]*4,im.shape[0]*4))
        self.selected_contours_image = im.copy()        
        self.im = im        
        super().__init__()
        self.initUI()        
    
    def initUI(self):
        self.label = 0
        self.contours = []
        self.selected_cntrs = deque()
        dsp = Dsp()
        im, self.contours = dsp.detectSymbols(self.im)        
        self.setMouseTracking(1)
        self.mpos = QPoint(1,1)        
        self.startTimer(100)

    def mouseMoveEvent(self, event):
        self.mpos = event.pos()
            
    def mousePressEvent(self, event):
        withCntl  = (event.modifiers() == Qt.ControlModifier)
        withShift =  (event.modifiers() == Qt.ShiftModifier)
        self.mpos = event.pos()
        if event.button() == Qt.LeftButton:
            m_piece = self.pickCountour(self.mpos, withCntl, withShift) 
            self.updateCntrImage()
            self.repaint()
            return

    def keyPressEvent(self, event):                
        if event.key() == Qt.Key_Delete:
            self.selected_contours.clear()
            self.updateCntrImage()                
        if event.key() == Qt.Key_F2:
            self.save(self.im, self.selected_contours)
            self.close()
        if event.key() == Qt.Key_Q:
            self.close()            
        if (event.modifiers() & Qt.ControlModifier) and (event.key() == Qt.Key_Z):
            self.selected_contours.pop()
            self.updateCntrImage()
            #cv2.imshow("w0",tmp)
        val = event.key() - Qt.Key_0
        if val in range(1,10):
            self.label = clamp(1,val,10)
        self.label=event.text()
        self.repaint()


    def pickCountour(self, mpos, deselect=False, withCntl=False, withShift=False):
        contourIdx = 0        
        maxContoursinOneSelection = 1000000
        num_selected = 0
        #result = re.match("\d+", self.label)
        if type(self.label) is int:
            colorIndex = clamp(1, int(self.label), len(color_tab1)) 
        else:
            colorIndex = 9
        # loop over all countours         
        contourIdx = 0
        for c in self.contours:
            x,y,w,h = cv2.boundingRect(c)
            area = w*h
            mouseInsideContour = x < mpos.x() and y < mpos.y() and (x + w) > mpos.x() and (y + h) > mpos.y()
            if mouseInsideContour: 
                self.selected_cntrs.append((contourIdx, self.label))
                #print(contourIdx)
            
            contourIdx+=1

        #cv2.imshow("w0", tmp)
        return QRect(0,0,100,100)    

    def drawSelectedContours(self, img, selected_cntrs, thickness=2):
        for c in selected_cntrs:
           contourIdx = c[0]
           colorIdx = c[1]
           countour_color = color_tab1[colorIdx]
           #cv2.drawContours(img, self.contours, contourIdx, countour_color, thickness)
           c = self.contours[contourIdx]
           x,y,w,h = cv2.boundingRect(c)
           cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),thickness=2)           
           print(contourIdx)

    def updateCntrImage(self):
        #tmp = cv2.cvtColor(self.im, cv2.COLOR_GRAY2RGB)  
        self.selected_contours_image = self.im.copy()
        self.drawSelectedContours(self.im, self.selected_cntrs, thickness=2)
    
    def showEvent(self, event):
        screen = QApplication.screens()[0]
        sw = screen.geometry().width()
        sh = screen.geometry().height()
        self.setGeometry(sw/2,sh/2,self.im.shape[1],self.im.shape[0])

    def paintEvent(self, event):
        qp = QPainter()
        qp.begin(self)        
        tmp = mat2img(self.selected_contours_image, 3)
        qp.drawImage(0,0,tmp)
        qp.end()

