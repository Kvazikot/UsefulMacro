
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
from collections import deque
import os
import sys
import random
import cv2
import numpy as np
from page_segmentation import PageSegmentor
from  cv2 import connectedComponentsWithStats
from PyQt5.QtWidgets import QWidget, QApplication, QLabel
from PyQt5.QtGui import QPainter, QColor, QFont, QImage, QPixmap, QCursor, QPainterPath, QPolygonF
from PyQt5.QtCore import Qt, QRect, QPoint, QTimer


def mat2img(mat,channels):
    if channels == 1:
        mat = cv2.cvtColor(mat, cv2.COLOR_GRAY2BGR)
    pix = QPixmap(mat.shape[1], mat.shape[0])
    is_success, im_buf_arr = cv2.imencode(".png", mat)
    byte_im = im_buf_arr.tobytes()
    pix.loadFromData(byte_im)
    print('mat2img mat shape' + str(mat.shape))
    print('mat2img img size' + str(pix.size().width()))
    return pix.toImage()

def img2mat(qimag, channels_count):
        outImg = np.zeros((qimag.height(), qimag.width() ,3), dtype=np.uint8)
        bufersize = qimag.height() * qimag.width() * 4
        b = qimag.bits()               
        b.setsize(qimag.height() * qimag.width() * channels_count)
        outImg = np.frombuffer(b, np.uint8).reshape((qimag.height(), qimag.width(), channels_count))
        return outImg

def area(rect):
    return rect.width() * rect.height()
    

class Dsp:
    def __init__(self):
        super().__init__()
        self.rects = []
        print("hello DSP!")
        
    # TODO create text masks using convolution with long line 
    def CreateTextMasks(self, m_gradient):
        underline_kernel = np.array([[0, 0, 0, 0, 0, 0, 0 ,0],
                                     [11, 11, 11, 11, 11, 11, 11, 11],
                                     [0, 0, 0, 0, 0, 0, 0, 0]])
        im_response = cv2.filter2D(src=m_gradient, ddepth=-1, kernel=underline_kernel)
        im_gray = im_response #cv2.cvtColor(im_response, cv2.COLOR_BGR2GRAY)
        ret, binary = cv2.threshold(im_response,255,20,cv2.THRESH_BINARY)
        #------------- PREFILTERING operations        
        rect_kernel = cv2.getStructuringElement(cv2.MORPH_CROSS, (3, 3))        
        M = cv2.getStructuringElement(cv2.MORPH_CROSS, (3,3))               
        m_gradient = cv2.morphologyEx(im_gray, cv2.MORPH_GRADIENT, M)      
        canny_output = cv2.Canny(im_gray, 40, 40 * 2 )
        canny_output = cv2.dilate(canny_output, rect_kernel)
        im, contours, hierarchy = cv2.findContours(canny_output, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

        cv2.imshow("w1", im_response)
        
        return contours
    
        
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

        self.areaImg = areaImg

        # drawing black frame around screenshot to avoid countour damage
        #cv2.rectangle(areaImg,(0,0),(areaImg.shape[1],areaImg.shape[0]),(0,0,0),thickness=20)
        
        # convert to grayscale
        im_gray = cv2.cvtColor(areaImg, cv2.COLOR_BGR2GRAY)
        #im_gray = cv2.blur( im_gray, (3,3) );
        #cv2.imshow("w0", im_gray)
        
        #------------- PREFILTERING operations
        rect_kernel = cv2.getStructuringElement(cv2.MORPH_CROSS, (kernel_size, kernel_size))        
        M = cv2.getStructuringElement(cv2.MORPH_CROSS, (3,3))               
        self.m_gradient = cv2.morphologyEx(im_gray, cv2.MORPH_GRADIENT, M)
        
        canny_output = cv2.Canny(im_gray, thresh, thresh * 2 )
        #cv2.imshow("w0", canny_output)
        canny_output = cv2.dilate(canny_output, rect_kernel)
        #cv2.imshow("w1", canny_output)
        
        #ret, binary = cv2.threshold(1s,40,255,cv2.THRESH_BINARY)
        #
        #(m_gradient.shape[0],m_gradient.shape[1])
                   
        #print((0,0),(m_gradient.shape[1], m_gradient.shape[0]))
        #cv2.imshow('w0',m_gradient)

        
    
        # 1. -------------- DETECT CONTOURS         
        im, self.contours, self.hierarchy = cv2.findContours(self.m_gradient, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

        # 2. detect underlined text like hyperlinks
        c2 = self.CreateTextMasks(self.m_gradient)
        #print(f'c2 len {len(c2}')
        #self.contours.append(c2)
        contourIdx = 0
        for i in c2:
            self.contours.append(i)           
            countour_color = (random.randint(100, 255),random.randint(100, 255),random.randint(100, 255))
            #cv2.drawContours(self.m_gradient, c2, contourIdx, countour_color,thickness=3)
            contourIdx+=1
        

        # 3. --------------  DRAW CONTOURS         
        self.contours_filtred = []
        print(self.contours[1])
        print(f'contours num = {len(self.contours)}')
        contourIdx = 0
        for c in self.contours:
            x,y,w,h = cv2.boundingRect(c)
            if w>5 and h>10 and w < self.m_gradient.shape[0] and h < self.m_gradient.shape[1]:
                #cv2.rectangle(areaImg,(x,y),(x+w,y+h),(255,5,0),1)
                self.contours_filtred.append(c)
                countour_color = (random.randint(100, 255),random.randint(100, 255),random.randint(100, 255))
                cv2.drawContours(self.m_gradient, self.contours, contourIdx, countour_color,thickness=1)
            contourIdx+=1       
    

        #cv2.connectedComponentsWithStats(canny_output, labels, stats, centroids)
        labels = np.zeros((screenshot.height(), screenshot.width(), 3), dtype=np.uint8)
        stats = np.zeros((screenshot.height(), screenshot.width(), 3), dtype=np.uint8)
        centroids = np.zeros((screenshot.height(), screenshot.width(), 3), dtype=np.uint8)
        output = cv2.connectedComponentsWithStats(canny_output, connectivity=4)
        (numLabels, labels, stats, centroids) = output
        #im_gray = cv2.cvtColor(im_gray, cv2.COLOR_GRAY2RGB)
        print('numLabels ' + str(numLabels))
        
        return self.rects   
       
        

color_tab1 = [(255,255,255),(255,0,0),(255,255,0),(255,0,255),(0,0,255),
              (0,255,255),(255,128,0),(128,255,0),(128,0,255),(0,0,128)]
print(len(color_tab1))

def clamp(minvalue, value, maxvalue):
    return max(minvalue, min(value, maxvalue))


#------------------------------------------------------------------------------


class Example(QWidget):

    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.dsp = Dsp()
        self.screen_num = 0
        self.label = 1
        self.sample_dim = (28, 28)
        self.selected_contours_image = None
        self.selected_cntr = []
        self.selected_cntrs = deque()
        self.cntr2label_map = {"cntrIndex": -1}
        #self.setWindowOpacity(0.8)
        self.tipLabel = QLabel(self)
        self.image = QImage('./rect_images\\00.06.36.730.png')
        
        
        self.tipLabel.setStyleSheet("font-size:24pt; color: red; background: white")
        #tip+="F1 - save selected rectangle area to ./square dir"
        tip="F2 - Confirm saving training samples from current screen. q - quit this window F5 - hide window on 1 sec"
        self.tipLabel.setAlignment(Qt.AlignBottom)
        self.tipLabel.setText(tip)
        self.setWindowTitle('Drawing')
        self.setMouseTracking(1)
        self.mpos = QPoint(1,1)
        #sys.exit(0)
        self.show()
        self.startTimer(100)
        
    def save(self, img, selected_cntrs):
        print("saving training samples...")
        for c in selected_cntrs:
           contourIdx = c[0]
           label = c[1]
           countour = self.dsp.contours_filtred[contourIdx]
           x,y,w,h = cv2.boundingRect(countour)
           
           print(f'{x} {y} {w} {h}')
           areaRoi=self.dsp.areaImg[y:y+h,x:x+w]
           roi = np.zeros((h, w, 3), dtype=np.uint8)
           for p in countour:
               p[0][0]-=x
               p[0][1]-=y
        
           countours = [countour]
           cv2.drawContours(roi, countours, 0, (255,255,255), 1)
           w2 = 200
           if w > w2:
               w = w2
           resized = cv2.resize(roi[:, :w], self.sample_dim, interpolation = cv2.INTER_AREA)
           
           #cv2.imshow("w0", resized)
           number = random.randint(0,100000)
           n_str="sample_{:d}_{:0d}".format(label,number)
           path=f'./data/{label}/{n_str}.png'
           print("saving " + path)
           cv2.imwrite(path, resized)
           #path=f'./data/{label}/bmp/{n_str}.png'
           #resized = cv2.resize(areaRoi, self.sample_dim, interpolation = cv2.INTER_AREA)
           #cv2.imwrite(path, resized)
        

    def keyPressEvent(self, event):
        val = event.key() - Qt.Key_0
        if val in range(1,10):
            self.label = clamp(1,val,10)
        print(f'current label is {self.label}')
        
        if event.key() == Qt.Key_F2:
            self.save(self.dsp.m_gradient, self.selected_cntrs)
            self.close()

        if event.key() == Qt.Key_F5:
            self.hide()
            QTimer.singleShot(1000, self.show)
            
        if event.key() == Qt.Key_F1:
            self.testSegmentation()
            
        if event.key() == Qt.Key_Q:
            self.close()
            
        if (event.modifiers() & Qt.ControlModifier) and (event.key() == Qt.Key_Z):
            self.selected_cntrs.pop()
            self.updateCntrImage()
            #cv2.imshow("w0",tmp)

    def testSegmentation(self):
        segmentor = PageSegmentor()
        contourIdx = 0
        contours_filtred = self.dsp.contours_filtred.copy()
        for countour in contours_filtred:
           x,y,w,h = cv2.boundingRect(countour)           
           print(f'{x} {y} {w} {h}')
           areaRoi=self.dsp.areaImg[y:y+h,x:x+w]
           roi = np.zeros((h, w, 3), dtype=np.uint8)
           for p in countour:
               p[0][0]-=x
               p[0][1]-=y        
           countours = [countour]
           cv2.drawContours(roi, countours, 0, (255,255,255), 1)
           for p in countour:
               p[0][0]+=x
               p[0][1]+=y        
           resized = cv2.resize(roi, self.sample_dim, interpolation = cv2.INTER_AREA)
           gray = cv2.cvtColor(resized, cv2.COLOR_BGR2GRAY)
           label = segmentor.predict(gray)
           colorIdx = label
           self.selected_cntrs.append((contourIdx, colorIdx))
           contourIdx+=1
        self.updateCntrImage()

    def updateCntrImage(self):
        tmp = cv2.cvtColor(self.dsp.m_gradient, cv2.COLOR_GRAY2RGB)  
        self.drawSelectedContours(tmp, self.selected_cntrs, thickness=2)
        self.selected_contours_image = mat2img(tmp, 4)
            

    def mouseMoveEvent(self, event):
        self.mpos = event.pos()
        
    def timerEvent(self, event):
        self.repaint()
        
    def drawSelectedContours(self, img, selected_cntrs, thickness=2):
        print(f'selected_cntrs={selected_cntrs}')
        for c in selected_cntrs:
           contourIdx = c[0]
           colorIdx = c[1]
           countour_color = color_tab1[colorIdx]
           cv2.drawContours(img, self.dsp.contours_filtred, contourIdx, countour_color, thickness=1)
        
   
    def pickCountour(self,mpos):
        contourIdx = 0        
        minSquare = 80000*80000
        minSquareIndex = 0
        for c in self.dsp.contours_filtred:
            x,y,w,h = cv2.boundingRect(c)
            square = w*h
            if x < mpos.x() and y < mpos.y() and (x + w) > mpos.x() and (y + h) > mpos.y() :
                if square < minSquare:
                    minSquare = square
                    minSquareIndex = contourIdx
                    print(f'selected = {contourIdx}');
            contourIdx+=1

        colorIndex = clamp(1, self.label, len(color_tab1)) 
        
        removed_indexes = []
        
        if minSquareIndex==0:
           self.selected_contours_image = mat2img(self.dsp.m_gradient, 4)
        else:

          if minSquareIndex not in self.cntr2label_map.keys():
             self.cntr2label_map[minSquareIndex] = colorIndex
             self.selected_cntrs.append((minSquareIndex, colorIndex))
          else: 
              if self.cntr2label_map[minSquareIndex] == -1:
                 self.cntr2label_map[minSquareIndex] = colorIndex
                 self.selected_cntrs.append((minSquareIndex, colorIndex))
              else:
                  # if countour alredy selected deselect 
                  for c in self.selected_cntrs:
                      if c[0] == minSquareIndex:
                          removed_indexes.append(c)
                          self.cntr2label_map[minSquareIndex] = -1
                          
        for c in removed_indexes:
            self.selected_cntrs.remove(c)        
            
        #countour_color = color_tab1[colorIndex]
        #cv2.rectangle(self.dsp.m_gradient, (x,y), (x+w,y+h),(255,255,255),-1)
        tmp = cv2.cvtColor(self.dsp.m_gradient, cv2.COLOR_GRAY2RGB)  
        self.drawSelectedContours(tmp, self.selected_cntrs, thickness=2)
        self.selected_contours_image = mat2img(tmp, 4)

        #print(c)
        self.selected_cntr = self.dsp.contours_filtred[minSquareIndex]
        #print('pickContour ' + str(QRect(x,y,w,h)))
        #cv2.imshow("w0", tmp)
        return QRect(0,0,100,100)        
        
    def pickRect(self, mpos):        
        for r in self.dsp.rects:
            if r.contains(mpos):
                return r
    
    def pickSample(self):
        r = self.pickCountour(self.mpos)
        
        
        #cv2.imshow("w1", self.dsp.areaImg)
        
        #print('pickSample')
        #print('pickCountour  ' + str(r))
        return self.dsp.m_gradient #[r.top():r.bottom(),r.left():r.right()]
            
    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            m_piece = self.pickSample() 
        
    def showEvent(self, a0):
        rect2 = self.rect()
        self.rects = self.dsp.detectButtons(self.screen_num, 4)
        self.updateCntrImage()
        self.repaint()

        #if len(QApplication.screens()) < self.screen_num :
        #   return
        screen = QApplication.screens()[self.screen_num]
        self.setGeometry(screen.geometry())
        self.tipLabel.move(100, screen.geometry().bottom()-40)

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
        #qp.drawImage(0,0,tmp)
        if self.selected_contours_image != None:
            qp.drawImage(0,0,self.selected_contours_image)
        qp.fillRect(self.rect(), QColor(1,1,1,110))        
        path = QPainterPath()        
        polygon = QPolygonF()
        path.addPolygon(polygon)
        for p in self.selected_cntr:
            #print('point from selected contour ' + str(p))
            polygon.append(QPoint(p[0][0],p[0][1]))
        path.addPolygon(polygon)
        qp.setPen(Qt.white)
        #qp.drawPath(path)

        # for r in self.rects:
        #     if r.contains(self.mpos):
        #         qp.fillRect(r, QColor(244,1,1,110))
        #     else:
        #         qp.fillRect(r, QColor(1,244,1,110))
            
        qp.end()


def createDataDirs():
    max_labels = 10
    for i in range(1,max_labels,1):
        os.makedirs(f"./data/{i}", exist_ok = True)


ex = None

def main2():
    app = QApplication(sys.argv)
    ex = Example()
    ex.showFullScreen()
    createDataDirs()
    sys.exit(app.exec_())

def hide():
    if not ex.isHidden():
        ex.hide()
    else:
        ex.showFullScreen()

if __name__ == '__main__':    
    main2()


path = "./rect_images"

fname = []
for root,d_names,f_names in os.walk(path):
	for f in f_names:
		fname.append(os.path.join(root, f))


#p = subprocess.Popen("dir", stdout=subprocess.PIPE, shell=True)
#print(p.communicate())



