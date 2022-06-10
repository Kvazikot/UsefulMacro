
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

import subprocess
import datetime
# This is our shell command, executed by Popen.
import os
import sys
import random
import cv2
import numpy as np
from  cv2 import connectedComponentsWithStats
from PyQt5.QtWidgets import QWidget, QApplication, QLabel
from PyQt5.QtGui import QPainter, QColor, QFont, QImage, QPixmap, QCursor 
from PyQt5.QtCore import Qt, QRect, QPoint 

def mat2img(mat,channels):
    if channels == 1:
        mat = cv2.cvtColor(mat, cv2.COLOR_GRAY2BGR)
    out_image = QImage(mat.data, mat.shape[0], mat.shape[1], 4, QImage.Format_RGB32)
    return out_image

def area(rect):
    return rect.width() * rect.height()
    

class Dsp:
    def __init__(self):
        super().__init__()
        self.rects = []
        print("hello DSP!")
    
        
    def detectButtons(self, screen_num, kernel_size):
        if len(QApplication.screens()) < screen_num :
           return
        screen = QApplication.screens()[screen_num]
        screenshot = QImage()
        #screenshot = screen.grabWindow().toImage()
        desktop = QApplication.desktop()
#        screenId = desktop.screenNumber(QCursor.pos())
        screen = QApplication.screens()[screen_num]
        geom = screen.geometry()
        x = geom.x()
        y = geom.y()
        screenshot = QApplication.screens()[screen_num].grabWindow(
                 desktop.winId(), x, y, geom.width(), geom.height()).toImage()
        #areaImg = cv2.Mat((screenshot.height(), screenshot.width()), cv2.CV_8UC4, screenshot.bits())
        #im_gray = Mat()
        #canny_output = Mat()
        areaImg = np.zeros((screenshot.height(), screenshot.width() ,3), dtype=np.uint8)
        bufersize = screenshot.height() * screenshot.width() * 4
        self.screenshot = screenshot
        b = screenshot.bits()        
        # sip.voidptr must know size to support python buffer interface
        
        #//---------- PARAMETRES ------------------------------------
        channels_count = 4
        kernel_size = 2
        thresh = 40
        
        b.setsize(screenshot.height() * screenshot.width() * channels_count)
        areaImg = np.frombuffer(b, np.uint8).reshape((screenshot.height(), screenshot.width(), channels_count))
        # drawing black frame around screenshot to avoid countour damage
        #cv2.rectangle(areaImg,(0,0),(areaImg.shape[1],areaImg.shape[0]),(0,0,0),thickness=20)
        # convert to grayscale
        im_gray = cv2.cvtColor(areaImg, cv2.COLOR_BGR2GRAY)
        im_gray = cv2.blur( im_gray, (3,3) );
        #cv2.imshow("w0", im_gray)
        
        #------------- PREFILTERING operations
        rect_kernel = cv2.getStructuringElement(cv2.MORPH_CROSS, (kernel_size, kernel_size))        
        M = cv2.getStructuringElement(cv2.MORPH_CROSS, (3,3))        
        m_gradient = cv2.morphologyEx(im_gray, cv2.MORPH_GRADIENT, M)
        canny_output = cv2.Canny(m_gradient, thresh, thresh * 2 )
        cv2.imshow("w0", canny_output)
        canny_output = cv2.dilate(canny_output, rect_kernel)
        cv2.imshow("w1", canny_output)
        
        #ret, binary = cv2.threshold(s,40,255,cv2.THRESH_BINARY)
        #
        #(m_gradient.shape[0],m_gradient.shape[1])
                   
        #print((0,0),(m_gradient.shape[1], m_gradient.shape[0]))
        cv2.imshow('w0',m_gradient)
        contours, hierarchy = cv2.findContours(m_gradient, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        print(f'contours num = {len(contours)}')
        contourIdx = 0
        for c in contours:
            x,y,w,h = cv2.boundingRect(c)
            if w>5 and h>10:
                #cv2.rectangle(areaImg,(x,y),(x+w,y+h),(255,5,0),1)
                countour_color = (random.randint(100, 255),random.randint(100, 255),random.randint(100, 255))
                cv2.drawContours(areaImg, contours, contourIdx, countour_color,thickness=2)
            contourIdx+=1
        cv2.imshow('w1',areaImg)
        
        #cv2.imshow("w1", canny_output)
        
        self.m_gradient = m_gradient #mat2img(im_gray, 1)
        #cv2.imshow("w0", m_gradient)
        

        #cv2.connectedComponentsWithStats(canny_output, labels, stats, centroids)
        labels = np.zeros((screenshot.height(), screenshot.width(), 3), dtype=np.uint8)
        stats = np.zeros((screenshot.height(), screenshot.width(), 3), dtype=np.uint8)
        centroids = np.zeros((screenshot.height(), screenshot.width(), 3), dtype=np.uint8)
        output = cv2.connectedComponentsWithStats(canny_output, connectivity=4)
        (numLabels, labels, stats, centroids) = output
        #im_gray = cv2.cvtColor(im_gray, cv2.COLOR_GRAY2RGB)
        print('numLabels ' + str(numLabels))
        
        
        mapX = {0: set([1,23])}
        mapY = {0: set([1,23])}
        
        print('m_gradient shape' + str(m_gradient.shape))
        
        for x in range(0, m_gradient.shape[1], 1):
            mapX[x] = set([])
        for y in range(0, m_gradient.shape[0], 1):
            mapY[y] = set([])  

        n_rect = 0
        #cv2.imshow("labels", labels)
        if stats.shape[1] == 5:
            for i in range(0, numLabels, 1):
                x = stats[i, cv2.CC_STAT_LEFT]
                y = stats[i, cv2.CC_STAT_TOP]
                w = stats[i, cv2.CC_STAT_WIDTH]
                h = stats[i, cv2.CC_STAT_HEIGHT]
                #if  ( w < maxRectWidth) and (h < maxRectHeight ) and (w > 0) and (h >0) :
                r = QRect(x,y,w,h)
                self.rects.append(r);
                #for x in range(r.left(), r.right(), 1):
                #    mapX[x].add(n_rect)
                #for y in range(r.top(), r.bottom(), 1):
                #    mapY[y].add(n_rect)                
                n_rect+=1      

        # filter rects that overlaps
        # select max area rect in every coordinate
        # rectsMap = {}
        # print(mapX.items())
        # for item in mapX.items():
        #    a =  0
        #    maxAreaIndex = 0
        #    for i in item[1]:
        #        if area(self.rects[i]) > a:
        #            a =  area(self.rects[i])
        #            maxAreaIndex = i
        #            #print(maxAreaIndex)
        #    #self.rects2.append(self.rects[maxAreaIndex])
           
        #    rectsMap[maxAreaIndex] = 1  
           
        # print("rects before filtering: " + str(len(self.rects)) )
        # print("rects after filtering: " + str(len(rectsMap)) )
        return self.rects   
       
        


class Example(QWidget):

    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.dsp = Dsp()
        self.screen_num = 0
        #self.setWindowOpacity(0.8)
        self.tipLabel = QLabel(self)
        self.rects = self.dsp.detectButtons(self.screen_num, 4)
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
        #self.tipLabel.setText(tip)
        self.setWindowTitle('Drawing')
        self.setMouseTracking(1)
        self.mpos = QPoint(1,1)
        #sys.exit(0)
        self.show()
        self.startTimer(100)

    def keyPressEvent(self, event):
        self.label = event.key() - Qt.Key_0
        print(f'current label is {self.label}')
        if event.key() == Qt.Key_Q:
            self.close()
            

    def mouseMoveEvent(self, event):
        self.mpos = event.pos()
        
    def timerEvent(self, event):
        self.repaint()
            
    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            m_piece = self.dsp.m_gradient[0:100,0:100]
            now = datetime.datetime.now()
            current_time = now.strftime("%H.%M.%S.png")
            fname='./data/{l}/{t}.png'.format(t=current_time,l=self.label)
            print(f'sample writed {fname}')
            cv2.imwrite(fname, m_piece)            
        
    def showEvent(self, a0):
        rect2 = self.rect()
        #if len(QApplication.screens()) < self.screen_num :
        #   return
        screen = QApplication.screens()[self.screen_num]
        self.setGeometry(screen.geometry())

        #rect2.setTopLeft(self.rect().center())
        #rect2.setTop(rect2.center().y())
        #rect2.setWidth(rect2.width()/2)
        #rect2.setHeight(rect2.height()/2)
        #self.tipLabel.setGeometry(rect2)
    
    def closeEvent(self, a0):        
        cv2.destroyWindow("w0") 
        cv2.destroyWindow("w1") 
        
    def paintEvent(self, event):
        qp = QPainter()
        qp.begin(self)
        qp.drawImage(0,0,self.dsp.screenshot)
        #qp.drawImage(0,0,self.dsp.m_gradient)
        qp.fillRect(self.rect(), QColor(1,1,1,110))        
        

        for r in self.rects:
            if r.contains(self.mpos):
                qp.fillRect(r, QColor(244,1,1,110))
            else:
                qp.fillRect(r, QColor(1,244,1,110))
            
        qp.end()


def createDataDirs():
    max_labels = 10
    for i in range(1,max_labels,1):
        os.makedirs(f"./data/{i}", exist_ok = True)

def main():
    app = QApplication(sys.argv)
    ex = Example()
    ex.showFullScreen()
    sys.exit(app.exec_())


if __name__ == '__main__':
    createDataDirs()
    main()

path = "./rect_images"

fname = []
for root,d_names,f_names in os.walk(path):
	for f in f_names:
		fname.append(os.path.join(root, f))


#p = subprocess.Popen("dir", stdout=subprocess.PIPE, shell=True)
#print(p.communicate())



