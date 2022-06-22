
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
        underline_kernel = np.array([[0, 0, 0, 0, 0, 0, 0, ],
                                     [0, 61, 61, 61, 61, 61, 0],
                                     [0, 0, 0, 0, 0, 0, 0]])
        
        #underline_kernel =  np.rot90(underline_kernel, 1)
        
        im_response = cv2.filter2D(src=m_gradient, ddepth=-1, kernel=underline_kernel)

        im_gray = im_response #cv2.cvtColor(im_response, cv2.COLOR_BGR2GRAY)
        #ret, binary = cv2.threshold(im_response,255,20,cv2.THRESH_BINARY)
        #------------- PREFILTERING operations        
        rect_kernel = cv2.getStructuringElement(cv2.MORPH_CROSS, (3, 3))
        M = cv2.getStructuringElement(cv2.MORPH_CROSS, (3,3))               
        #im_gray = im_gray[0:im_gray.shape[0]-300,:]
        m_gradient = cv2.morphologyEx(im_gray, cv2.MORPH_GRADIENT, M)      
        #canny_output = cv2.Canny(im_gray, 40, 40 * 2 )
        #canny_output = cv2.dilate(canny_output, rect_kernel)
        #cv2.imshow("w0", m_gradient)
        

        output = cv2.connectedComponentsWithStats(m_gradient, connectivity=4)
        (numLabels, labels, stats, centroids) = output
        
 
        # preparing dict for every point in every rectangle
        indexesX = {0: set([])}
        indexesY = {0: set([])}             
        minAreaIndexes = {'10,20': set([1])}

        for x in range(0, m_gradient.shape[1], 1):
            indexesX[x] = set([])
        for y in range(0, m_gradient.shape[0], 1):
            indexesY[y] = set([])  
        
        def area(rect):
            return rect.width() * rect.height()

        def areaI(rect_idx):
            return self.rects[rect_idx].width() * self.rects[rect_idx].height()

        # loop over connected components with creating dicts indexesX and     
        rect_dictX = {}
        rect_dictY = {}
        RectGraf = {}
        n_rect = 0
        minRectHeight = 20
        minRectWidth = 20
        if stats.shape[1] == 5:
            for i in range(0, numLabels, 1):
                x = stats[i, cv2.CC_STAT_LEFT]
                y = stats[i, cv2.CC_STAT_TOP]
                w = stats[i, cv2.CC_STAT_WIDTH]
                h = stats[i, cv2.CC_STAT_HEIGHT]
                if  ( w*h < minRectWidth*minRectHeight) :
                    continue
                r = QRect(x,y,w,h)
                self.rects.append(r);
                for x in range(r.left(), r.right(), 1):
                   if x not in indexesX:
                       indexesX[x] = set([])
                   indexesX[x].add(n_rect)
                for y in range(r.top(), r.bottom(), 1):
                   if y not in indexesY:
                       indexesY[y] = set([])                    
                   indexesY[y].add(n_rect)   
                n_rect+=1
        
        print(f'rects number = {len(self.rects)}')
        #print(indexesY)
        #for x in indexesX:
        #    print(f'{x} =  {len(indexesX[x])}')
        
        for x in indexesX:
            for key in indexesX[x]:
                if key not in RectGraf:
                   RectGraf[key] = set([])
                for irect in indexesX[x]:
                    RectGraf[key] |= set([irect])
                    #print(len(RectGraf[key]))

        # for y in indexesY:
        #     for key in indexesY[y]:
        #         if key not in RectGraf:
        #            RectGraf[key] = set([])
        #         for irect in indexesY[y]:
        #             RectGraf[key] |= set([irect])
        #             #print(len(RectGraf[key]))

        
        
        includedRects = set([])
        excludedRects = set([])
        for key in RectGraf:
            includedRects.add(key)
            #print(f"key {key} is ")
            #print(includedRects)
            
            if len(RectGraf[key]) > 125:
                print(f'rect has more then 2 links {key}')
                excludedRects.add(key)
        
            
        print(excludedRects)
        non_overvlaping_rectangles = set([])
        for i in includedRects:
            if i not in excludedRects:
                non_overvlaping_rectangles.add(i)
                
        print(non_overvlaping_rectangles)
        rects2 = []
        for i in  non_overvlaping_rectangles:
            rects2.append(self.rects[i])
        
        self.rects = rects2
                         

        #print(non_overvlaping_rectangles)
        
        # def take_second(elem):
        #     return elem[1]
        
        # def interval_intersect(i1, i2):
        #     A = set(range(i1[0],i1[1]))
        #     B = set(range(i2[0],i2[1]))            
        #     if (set(A) & set(B)) == set([]):
        #         return True
        #     else:
        #         return False
            

        # for x_key in indexesX:
        #     # select not intersecting intervals in A
        #     intervals = indexesX[x_key]            
        #     intervalsT = []
        #     for interval in intervals:
        #        i = interval.split(',')
        #        intervalsT.append((int(i[0]),int(i[1])))
        #     sorted_list = sorted(intervalsT, key=take_second, reverse=False)
        #     for i in range(0, len(sorted_list)-1, 1):
        #         if not interval_intersect(sorted_list[i],sorted_list[i+1]):
        #             interval=sorted_list[i]
        #             key = f'{interval[0]},{interval[1]}'
        #             non_overvlaping_rectangles.add(rect_dictX(key))
                    
            
        
        
        return []
    
        
    def detectButtons(self, screen_num, kernel_size):
        if len(QApplication.screens()) < screen_num :
           return
        # take screenshot 
        screen = QApplication.screens()[screen_num]
        screenshot = QImage()
        desktop = QApplication.desktop()
        screen = QApplication.screens()[screen_num]
        geom = screen.geometry()
        x = geom.x()
        y = geom.y()
        screenshot = QApplication.screens()[screen_num].grabWindow(
                 desktop.winId(), x, y, geom.width(), geom.height()).toImage()
        areaImg = np.zeros((screenshot.height(), screenshot.width() ,3), dtype=np.uint8)
        bufersize = screenshot.height() * screenshot.width() * 4
        self.screenshot = screenshot
        b = screenshot.bits()        
        channels_count = 4
        kernel_size = 2
        thresh = 40       
        b.setsize(screenshot.height() * screenshot.width() * channels_count)
        
        # converting QImage to Mat
        areaImg = np.frombuffer(b, np.uint8).reshape((screenshot.height(), screenshot.width(), channels_count))       
        
        # apply Sobel filtering
        kernel = np.array([[-1,-1,-1], [-1,9,-1], [-1,-1,-1]])
        #areaImg = cv2.filter2D(areaImg, -1, kernel)
        
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
        im, self.contours, self.hierarchy = cv2.findContours(canny_output, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

        # 2. detect underlined text like hyperlinks
        self.CreateTextMasks(self.m_gradient)
        

        # 3. --------------  DRAW CONTOURS         
        self.contours_filtred = []
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
        self.selected_rect = QRect(0,0,1,1)
        self.selected_cntr = []
        self.selected_cntrs = deque()
        self.selected_rects = []
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
        SELECTION_METHOD = 'RECT'
        #METHOD = 'CONTOUR'
        
        # saving part of image that is filtered using TextMask filter 
        if SELECTION_METHOD == 'RECT':
            for selected_rect in self.selected_rects:
                x = selected_rect.x()
                y = selected_rect.y()
                h = selected_rect.height()
                w = selected_rect.width()
                print(f'saving rect {x} {y} {w} {h}')
                roi=self.dsp.m_gradient[y:y+h,x:x+w]
                resized=roi
                width_max = 200
                w = min(w, width_max)
                #resized = cv2.resize(roi, self.sample_dim, interpolation = cv2.INTER_AREA)
                number = random.randint(0,100000)
                label = 2
                n_str="sample_{:d}_{:0d}".format(label,number)
                path=f'./data/{label}/{n_str}.png'
                print("saving " + path)
                cv2.imwrite(path, resized)
            
        
        # saving part of a contour as sample
        if SELECTION_METHOD == 'CONTOUR':            
            for c in selected_cntrs:
               contourIdx = c[0]
               label = c[1]
               countour = self.dsp.contours_filtred[contourIdx]
               x,y,w,h = cv2.boundingRect(countour)
               
               print(f'saving contour {x} {y} {w} {h}')
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
            self.selected_rects.pop() 
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
        for c in selected_cntrs:
           contourIdx = c[0]
           colorIdx = c[1]
           countour_color = color_tab1[colorIdx]
           cv2.drawContours(img, self.dsp.contours_filtred, contourIdx, countour_color, thickness)
        
   
    def pickCountour(self,mpos):
        contourIdx = 0        
        minSquare = 80000*80000
        minSquareIndex = 0
        colorIndex = clamp(1, self.label, len(color_tab1)) 
        removed_items = []        

        # select \ deselect contour logic 
        # loop over all countours         
        for c in self.dsp.contours_filtred:
            x,y,w,h = cv2.boundingRect(c)
            square = w*h
            #if (x+w/2) in range(self.selected_rect.left(), self.selected_rect.right()):
            if (x) in range(self.selected_rect.left(), self.selected_rect.right()):                
                if (y) in range(self.selected_rect.top(), self.selected_rect.bottom()): 
                    # if countour alredy selected deselect                         
                    if (contourIdx, colorIndex) in self.selected_cntrs:
                        removed_items.append((contourIdx,colorIndex))
                        self.cntr2label_map[contourIdx] = -1
                    else:
                        self.selected_cntrs.append((contourIdx, colorIndex))
            contourIdx+=1

        
       # remove countour from selection if it alredy selected  
        for countourIdx,i in removed_items:
            self.selected_cntrs.remove((countourIdx,i))
            
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
                # make bitmap offset
                #r.setLeft(r.left())
                return r
        return QRect(1,1,1,1)
    
    def pickSample(self):
        #self.selected_rect = self.pickRect(self.mpos)
        r = self.pickCountour(self.mpos)
        self.selected_rects.append(self.selected_rect)
        
        
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
        tmp = mat2img(self.dsp.m_gradient, 3)
        qp.drawImage(0,0,tmp)
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

        for r in self.dsp.rects:
            if r.contains(self.mpos):
                self.selected_rect = r
                qp.fillRect(r, QColor(244,1,1,20))
            else:
                qp.fillRect(r, QColor(1,244,1,20))
            
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



