
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
from matplotlib import pyplot as plt
import os
import re
import sys
import random
import cv2
import numpy as np
#from zommed_text_widget import ZommedTextWidget
from page_segmentation import PageSegmentor
from  cv2 import connectedComponentsWithStats
from PyQt5.QtWidgets import QWidget, QApplication, QLabel, QTextEdit, QHBoxLayout, QVBoxLayout, QPushButton
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
        #cv2.imshow("w1", m_gradient)
        

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
        
        #print(f'rects number = {len(self.rects)}')
        
        for x in indexesX:
            for key in indexesX[x]:
                if key not in RectGraf:
                   RectGraf[key] = set([])
                for irect in indexesX[x]:
                    RectGraf[key] |= set([irect])
                    #print(len(RectGraf[key]))
        
        
        includedRects = set([])
        excludedRects = set([])
        for key in RectGraf:
            includedRects.add(key)
            #print(f"key {key} is ")
            #print(includedRects)
            
            if len(RectGraf[key]) > 125:
                #print(f'rect has more then 2 links {key}')
                excludedRects.add(key)
        
            
        #print(excludedRects)
        non_overvlaping_rectangles = set([])
        for i in includedRects:
            if i not in excludedRects:
                non_overvlaping_rectangles.add(i)
                
        #print(non_overvlaping_rectangles)
        rects2 = []
        for i in  non_overvlaping_rectangles:
            rects2.append(self.rects[i])
        
        self.rects = rects2
        
        return rects2
    
    def click_rect(self, ratio, histogram):
        print(f"click_rect ratio={ratio} histogram=")

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
        canny_output = cv2.dilate(canny_output, rect_kernel)
       
    
        # 1. -------------- DETECT CONTOURS         
        im, self.contours, self.hierarchy = cv2.findContours(canny_output, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

        # 2. detect underlined text like hyperlinks
        self.CreateTextMasks(self.m_gradient)
        
        # 3 Detect symbols
        #for r in self.rects:
        #r = self.rects[66]
        #roi = areaImg#[r.y():r.y()+r.height(),r.x():r.x()+r.width()]
        #roi = cv2.resize(roi,(roi.shape[1]*2,roi.shape[0]*2))
        #self.detectSymbols(roi)
        #self.detectSymbols(areaImg)
        

        # 3. --------------  DRAW CONTOURS         
        self.contours_filtred = []
        #print(f'contours num = {len(self.contours)}')
        contourIdx = 0
        for c in self.contours:
            x,y,w,h = cv2.boundingRect(c)
            if w>5 and h>10 and w < self.m_gradient.shape[0] and h < self.m_gradient.shape[1]:
                #cv2.rectangle(areaImg,(x,y),(x+w,y+h),(255,5,0),1)
                self.contours_filtred.append(c)
                countour_color = (random.randint(100, 255),random.randint(100, 255),random.randint(100, 255))
                cv2.drawContours(self.m_gradient, self.contours, contourIdx, countour_color,thickness=1)
            contourIdx+=1       
    

        # #cv2.connectedComponentsWithStats(canny_output, labels, stats, centroids)
        # labels = np.zeros((screenshot.height(), screenshot.width(), 3), dtype=np.uint8)
        # stats = np.zeros((screenshot.height(), screenshot.width(), 3), dtype=np.uint8)
        # centroids = np.zeros((screenshot.height(), screenshot.width(), 3), dtype=np.uint8)
        # output = cv2.connectedComponentsWithStats(canny_output, connectivity=4)
        # (numLabels, labels, stats, centroids) = output
        #im_gray = cv2.cvtColor(im_gray, cv2.COLOR_GRAY2RGB)
        #print('numLabels ' + str(numLabels))
        
        return self.rects   
       
        
    def detectSymbols(self, src):
       
        # take input
        areaImg = src.copy()       
        # apply Sobel filtering
        kernel = np.array([[-1,-1,-1], 
                           [-1,9,-1], [-1,-1,-1]])
        kernel1 = np.array([[-1,-1,-1,-1,-1], 
                           [-1,-1,-1,-1,-1], 
                           [-1,-1, 25,-1,-1], 
                           [-1,-1,-1,-1,-1], 
                           [-1,-1,-1,-1,-1]])
        areaImg = cv2.filter2D(areaImg, -1, kernel)
        
        # drawing black frame around screenshot to avoid countour damage
        #cv2.rectangle(areaImg,(0,0),(areaImg.shape[1],areaImg.shape[0]),(0,0,0),thickness=20)
        
        # convert to grayscale
        im_gray = cv2.cvtColor(areaImg, cv2.COLOR_BGR2GRAY)
        #kernel1 = cv2.getStructuringElement(cv2.MORPH_RECT, (1,1))
        #im_gray = cv2.erode(im_gray, kernel1)
        #qcv2.imshow("w0", im_gray)
        #im_gray = cv2.blur( im_gray, (3,3) );
        # #cv2.imshow("w0", im_gray)
        
        # #------------- PREFILTERING operations
        # rect_kernel = cv2.getStructuringElement(cv2.MORPH_CROSS, sett["kernel_size"])        
        M = cv2.getStructuringElement(cv2.MORPH_CROSS, (3,3))
        self.m_gradient = cv2.morphologyEx(im_gray, cv2.MORPH_GRADIENT, M)
        
        # canny_output = cv2.Canny(im_gray, sett["canny_thresh"][0], sett["canny_thresh"][1] )
        # #if sett["Dilate"] == 1:
        # #    canny_output = cv2.dilate(canny_output, rect_kernel)
        # #else:
        # #    canny_output = cv2.erode(canny_output, rect_kernel)

        (T, threshInv) = cv2.threshold(self.m_gradient, 20, 255,	cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU)
        #cv2.imshow("w0",threshInv)

        im, self.contours, self.hierarchy = cv2.findContours(threshInv, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

        # 2. detect underlined text like hyperlinks
        #self.CreateTextMasks(self.m_gradient)
        

        # 3. --------------  DRAW CONTOURS         
        self.contours_filtred = []
        #print(f'contours num = {len(self.contours)}')
        contourIdx = 0
        for c in self.contours:
            x,y,w,h = cv2.boundingRect(c)
            if w>5 and h>10 and w < self.m_gradient.shape[0] and h < self.m_gradient.shape[1]:
                #cv2.rectangle(areaImg,(x,y),(x+w,y+h),(255,5,0),1)
                self.contours_filtred.append(c)
                countour_color = (random.randint(100, 255),random.randint(100, 255),random.randint(100, 255))
                cv2.drawContours(areaImg, self.contours, contourIdx, countour_color,thickness=1)
            contourIdx+=1       
    
        #cv2.imshow("w0",areaImg)
        
        
        return areaImg, self.contours   
       
        

color_tab1 = [(255,255,255),(255,0,0),(255,255,0),(255,0,255),(0,0,255),
              (0,255,255),(255,128,0),(128,255,0),(128,0,255),(0,0,128)]


def clamp(minvalue, value, maxvalue):
    return max(minvalue, min(value, maxvalue))


#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------


class Example(QWidget):

    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        im = cv2.imread("./data/text.png")
        #self.zoomed_widget = ZommedTextWidget(im)
        #self.zoomed_widget.setGeometry(0,0,300,300)
        #self.zoomed_widget.show()
        
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
        self.modeLabel = QLabel(self)
        self.image = QImage('./rect_images\\00.06.36.730.png')
        
        # widget = QWidget(self)
        # layout = QVBoxLayout()
        # # Add widgets to the layout       
        # self.settings = QTextEdit()        
        # layout.addWidget(self.settings)
        # layout.addWidget(QPushButton("Left-Most"))
        # layout.addWidget(QPushButton("Center"), 1)
        # layout.addWidget(QPushButton("Right-Most"), 2)
        # widget.setLayout(layout)        
        #print(str(sett))
        #s = str(sett).replace(",",",\n")
        #self.settings.setText(s)
        
        
        self.tipLabel.setStyleSheet("font-size:24pt; color: red; background: white")
        #tip+="F1 - save selected rectangle area to ./square dir"
        tip="F1 - run CNN F2 - Confirm saving training samples from current screen. F3 - mode q - quit this window F5 - hide window 1 sec"
        self.tipLabel.setAlignment(Qt.AlignBottom)
        self.tipLabel.setText(tip)
        modeString=f"label={self.label} mode(F3): single contour . ctrl - add to selection.  shift - remove m0"
        self.modeLabel.setText(modeString)
        self.modeLabel.setStyleSheet("font-size:18pt; color: red; background: #AA2222AA")
        self.setWindowTitle('Drawing')
        self.setMouseTracking(1)
        self.mpos = QPoint(1,1)
        #sys.exit(0)
        self.show()
        self.startTimer(100)
        
    def write_csv(self, csv_path, lines):
        print(f"samples writed in {csv_path}")
        with open(csv_path, 'w') as f:
            for line in lines:
                f.write(line)
                f.write("\n")
        
    def save(self, img, selected_cntrs):
        print("saving training samples...")
        SELECTION_METHOD = 'RECT'
        #METHOD = 'CONTOUR'
            
        csv_lines=[]
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
                width_max = 28*2
                offsetX = random.randint(0,int(w/2))
                w = min(w, width_max)
                resized = cv2.resize(roi[:,offsetX:offsetX+w], self.sample_dim, interpolation = cv2.INTER_AREA)
                number = random.randint(0,100000)
                label = 2
                n_str="sample_{:d}_{:0d}".format(label,number)
                path=f'./data/{label}/{n_str}.png'
                csv_lines.append(f"{label} {path}")
                print("saving " + path)
                cv2.imwrite(path, resized)
       
            self.csv_path=f'./data/labels.csv'
            self.write_csv(self.csv_path, csv_lines)
            
        
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
            

    def keyReleaseEvent(self, event):
        self.repaint()

    def keyPressEvent(self, event):
        
        
        if event.key() == Qt.Key_Delete:
            self.selec .clear()
            self.updateCntrImage()
        
        if event.key() == Qt.Key_F3:
            modeString=self.modeLabel.text()
            mode = modeString[len(modeString)-2:len(modeString)]
            if mode == 'm0':
                modeString  = modeString.replace("single", "multiple")
                modeString = modeString.replace(mode,'m1')
            if mode == 'm1':
                modeString  = modeString.replace("multiple","rect")
                modeString = modeString.replace(mode,'m2')
            if mode == 'm2':
                modeString  = modeString.replace("rect","single")
                modeString = modeString.replace(mode,'m0')
            print(modeString)            
            self.modeLabel.setText(modeString)
            return
        
        if event.key() == Qt.Key_F2:
            self.save(self.dsp.m_gradient, self.selected_cntrs)
            self.close()

        if event.key() == Qt.Key_F6:
            mode = self.modeLabel.text()
            self.modeLabel.setText(mode)

        if event.key() == Qt.Key_F5:
            self.hide()
            self.updateCntrImage()
            self.clear()
            QTimer.singleShot(1000, self.show)
            
        if event.key() == Qt.Key_F1:
            self.testSegmentation()

        if event.key() == Qt.Key_F4:
           sample1=cv2.imread("./rect_descriptor_tests/button.png")
           sample2=cv2.imread("./rect_descriptor_tests/button_half_size.png")

           ratio = self.selected_rect.width() / self.selected_rect.width()
           
           # selected_rect = self.selected_rects.pop()
           # w = selected_rect.width()
           # h = selected_rect.height()
           # x = selected_rect.left()
           # y = selected_rect.top()
           #img = self.dsp.areaImg[y:y+h,x:x+w]           
           #cv2.imwrite("sampl2.png", img)
           #cv2.imwrite("sampl2.png", img)
           #hsv_base1 = np.zeros((sample1.shape[1],sample1.shape[0]))
           #sample2 = sample1.copy()
           hsv_sample1 = cv2.cvtColor( sample1, cv2.COLOR_BGR2HSV )
           hsv_sample2 = cv2.cvtColor( sample2, cv2.COLOR_BGR2HSV )
           channels = cv2.split(hsv_sample1)
           print(channels[1].shape)
           
           histogram1 = cv2.calcHist([sample1],[0],None,[256],[0,256])
           histogram2 = cv2.calcHist([sample2],[0],None,[256],[0,256])           
           histogram1 = cv2.normalize( histogram1, 0, 1, cv2.NORM_L1 )
           histogram2 = cv2.normalize( histogram2, 0, 1, cv2.NORM_L1 )
           #histogram = cv2.calcHist([sample2],[0],None,[256],[0,256])
           s = "hist="
           for i in histogram1:
               s+=format(i[0],".6f")+","
               
           #print(s)
               
           base_base = cv2.compareHist( histogram1, histogram2, 0 )
           #print("comaration result " + str(base_base))
           
           class RectangleDescriptor:
               def __init__(self, w, h, im):
                   super().__init__()
                   self.w = w
                   self.h = h
                   self.hist = self.getHist(im)
                   
               def getHist(self,im):
                   hsv_sample = cv2.cvtColor( im, cv2.COLOR_BGR2HSV )
                   channels = cv2.split(hsv_sample)
                   hist = []
                   for cnael in channels:
                      chanel_histogram = cv2.calcHist([cnael],[0],None,[256],[0,256])
                      hist.append(chanel_histogram)
                   return hist
                   
               def area(self):
                  return self.w*self.h        
               def ratio(self):
                   small = min(self.w, self.w)
                   big = max(self.h, self.h)
                   return float(small/big)
               
               def calculateDifference(self, descr2):
                  dh = abs(1 - cv2.compareHist( self.hist[0], descr2.hist[0], 0 ))
                  dh+= abs(1 - cv2.compareHist( self.hist[1], descr2.hist[1], 0 ))
                  dh+= abs(1 - cv2.compareHist( self.hist[2], descr2.hist[2], 0 ))                  
                  screen = QApplication.screens()[0]
                  screen_area = screen.geometry().width() * screen.geometry().height()
                  da = abs(descr2.area() - self.area()) / screen_area
                  dr = abs(descr2.ratio() - self.ratio())
                  #print(f"dh={dh} da={da} dr={dr} w={self.w} h={self.h}")
                  d = dh + da + dr
                  return d
          
           class RectangleDescriptorTest:
               def __init__(self):
                   path_to_images = "./rect_descriptor_tests/"
                   buttons = ["button_cropped.png", "button.png", "button_half_size.png", 
                             "button_scaled_no_aspect.png", "button_with_drawings.png"]
                   p = set([])
                   print("")
                   for i in range(1,len(buttons),1):
                       for j in range(1,len(buttons),1):
                           p.add(i*10+j)
                           p = p.difference( set([j*10+i]) )
                   hdr = "difference {} {} "
                   l = 35
                   hdr = format("difference ").ljust(l) + format(" file1 ").ljust(l) + format(" file2 ").ljust(l)
                   print("-------------------------------------------------------------------------------------")
                   print(hdr)
                   print("-------------------------------------------------------------------------------------")
                           
                   for i in p:
                        a = int(i / 10)
                        b = int(i % 10)
                        #print(f"{a} - {b}")
                        sample1=cv2.imread(path_to_images+buttons[a])
                        sample2=cv2.imread(path_to_images+buttons[b])
                        rd1 = RectangleDescriptor( sample1.shape[1], sample1.shape[0], sample1)
                        rd2 = RectangleDescriptor( sample2.shape[1], sample2.shape[0], sample2)
                        d = rd1.calculateDifference(rd2)                                               
                        d = format(d, ".6f").ljust(35)
                        a = buttons[a].ljust(35)
                        b = buttons[b].ljust(35)
                        print ( "{} {} {} ".format(d, a, b) )
                
           test = RectangleDescriptorTest()
           # show the plotting graph of an image
           plt.subplot(1, 3, 1)
           plt.imshow(sample1)
           plt.subplot(1, 3, 2)
           plt.imshow(sample2)           
           plt.subplot(1, 3, 3)
           plt.hist(histogram1, bins = 256)
           self.dsp.click_rect(ratio, histogram1)
           self.close()
           
            
        if event.key() == Qt.Key_Q:
            self.close()
            
        if (event.modifiers() & Qt.ControlModifier) and (event.key() == Qt.Key_Z):
            self.selected_cntrs.pop()
            self.updateCntrImage()
            #cv2.imshow("w0",tmp)

        val = event.key() - Qt.Key_0
        if val in range(1,10):
            self.label = clamp(1,val,10)
        self.label=event.text()
        modeString=f"label={self.label} mode(F3): single contour . ctrl - add to selection.  shift - remove m0"
        self.modeLabel.setText(modeString)
        
        #print(f'current label is {self.label}')
        #self.modeLabel.setText(modeString)
        self.repaint()

    def clear(self):
        self.rects.clear()
        self.selected_cntrs.clear()
        self.selected_rects.clear()
        
    def testSegmentation(self):
        segmentor = PageSegmentor()
        contourIdx = 0
        contours_filtred = self.dsp.contours_filtred.copy()
        for countour in contours_filtred:
           x,y,w,h = cv2.boundingRect(countour)           
           #print(f'{x} {y} {w} {h}')
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
        self.repaint()

    def updateCntrImage(self):
        tmp = cv2.cvtColor(self.dsp.m_gradient, cv2.COLOR_GRAY2RGB)  
        self.drawSelectedContours(tmp, self.selected_cntrs, thickness=2)
        self.selected_contours_image = mat2img(tmp, 4)
            

        
    def timerEvent(self, event):
        self.repaint()
        
    def drawSelectedContours(self, img, selected_cntrs, thickness=2):
        for c in selected_cntrs:
           contourIdx = c[0]
           colorIdx = c[1]
           countour_color = color_tab1[colorIdx]
           cv2.drawContours(img, self.dsp.contours_filtred, contourIdx, countour_color, thickness)
        
   
    def pickCountour(self,mpos, deselect=False, withCntl=False, withShift=False):
        contourIdx = 0        
        maxContoursinOneSelection = 1000000
        num_selected = 0
        selectedContour = self.dsp.contours_filtred[0]
        #result = re.match("\d+", self.label)
        if type(self.label) is int:
            colorIndex = clamp(1, int(self.label), len(color_tab1)) 
        else:
            colorIndex = 9
        removed_items = []        

        print(f'withCntl={withCntl}')
        # select \ deselect contour logic 
        # loop over all countours         
        for c in self.dsp.contours_filtred:
            x,y,w,h = cv2.boundingRect(c)
            area = w*h
            mouseInsideContour = x < mpos.x() and y < mpos.y() and (x + w) > mpos.x() and (y + h) > mpos.y()
            selectionPressure = len(self.selected_cntrs) > maxContoursinOneSelection
            xInGreenRect = ( (x) in range(self.selected_rect.left(), self.selected_rect.right()) ) 
            yInGreenREct = ( (y) in range(self.selected_rect.top(), self.selected_rect.bottom()) )
            
            # if countour alredy selected deselect                         
            modeString = self.modeLabel.text()
            if "single" in modeString:
                if mouseInsideContour and not withShift and not withCntl:
                    self.selected_cntrs.clear()
                    self.selected_cntrs.append((contourIdx, colorIndex))                    
                    selectedContour = c
                if mouseInsideContour and withShift:
                    self.selected_cntrs.append((contourIdx, colorIndex))
                if  mouseInsideContour and withCntl:
                    removed_items.append((contourIdx,colorIndex))

            if "multiple" in modeString:
                if (xInGreenRect and yInGreenREct):
                    self.selected_cntrs.append((contourIdx, colorIndex))
                    selectedContour = c
            
            contourIdx+=1

        
       # remove countour from selection if it alredy selected  
        for countourIdx,i in removed_items:
            self.selected_cntrs.remove((countourIdx,i))
            
        tmp = cv2.cvtColor(self.dsp.m_gradient, cv2.COLOR_GRAY2RGB)  
        self.drawSelectedContours(tmp, self.selected_cntrs, thickness=2)
        self.selected_contours_image = mat2img(tmp, 4)

        #cv2.imshow("w0", tmp)
        return selectedContour
        
    def pickRect(self, contour):        
        x,y,w,h = cv2.boundingRect(contour)
        rect = QRect(x,y,w,h)
        return rect
    
    def pickSample(self,deselect,withCntl,withShift):
        c = self.pickCountour(self.mpos, deselect, withCntl, withShift)
        rect = self.pickRect(c)
        self.selected_rects.append(rect)        
        return self.dsp.m_gradient 

    def mouseMoveEvent(self, event):
        self.mpos = event.pos()
            
    def mousePressEvent(self, event):
        withCntl  = (event.modifiers() == Qt.ControlModifier)
        withShift =  (event.modifiers() == Qt.ShiftModifier)
        if event.button() == Qt.LeftButton:
            m_piece = self.pickSample(True, withCntl, withShift) 
            return
        if event.button() == Qt.RightButton:
            m_piece = self.pickSample(False, withCntl, withShift) 
            return
        
    def showEvent(self, a0):
        rect2 = self.rect()
        self.rects = self.dsp.detectButtons(self.screen_num, 4)
        self.updateCntrImage()
        self.repaint()

        screen = QApplication.screens()[self.screen_num]
        self.setGeometry(screen.geometry())
        self.tipLabel.move(100, screen.geometry().bottom()-40)
        


    
    def closeEvent(self, a0):        
        cv2.destroyWindow("w0") 
        cv2.destroyWindow("w1") 
        
    def paintEvent(self, event):
        qp = QPainter()
        qp.begin(self)
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

        # Draw all rectangles
        # get minimal area rect under mouse cursor
        for r in self.dsp.rects:
            if r.contains(self.mpos):
                #self.selected_rects.append(r)
                self.selected_rect = r
                qp.fillRect(r, QColor(244,1,1,20))
            else:
                qp.fillRect(r, QColor(1,244,1,20))
                

        # Draw only thouse that recognized CNN as rectangle
        idx = 0
        for c in self.selected_cntrs:
            label = c[1]
            if label == 1:
                contour = self.dsp.contours_filtred[c[0]]
                x,y,w,h = cv2.boundingRect(contour)
                qp.fillRect(QRect(x,y,w,h), QColor(244,1,1,20))
                qp.drawText(x,y,str(idx))
                print(f"aaaaaaaaaaaaaaaaa")
            idx+=1
            
        # def area(r):
        #     return r.width() * r.height()
        
        # minRect = QRect(0,0,100000000000,100000000000)
        # for r in self.selected_rects:
        #     if area(r) < area(minRect):
        #         minRect = r
        # self.selected_rect = minRect
        qp.end()


def createDataDirs():
    max_labels = 10
    eng_alphabet='qwertyuiopasdfghjklzxcvbnm'
    numbers='1234567890'
    #special='!?><[];:$$%^&*()-=+#/'
    for c in eng_alphabet:
        os.makedirs(f"./data/ocr/eng/{c}", exist_ok = True)
    #for n in special:
    #    os.makedirs(f"./data/ocr/special/{n}", exist_ok = True)
    for n in numbers:
        os.makedirs(f"./data/ocr/numbers/{n}", exist_ok = True)
    for i in range(1,max_labels,1):
        os.makedirs(f"./data/{i}", exist_ok = True)
        


ex = None

def main2():
    app = QApplication(sys.argv)
    ex = Example()
    ex.showFullScreen()
    #im = cv2.imread("./data/text.png")
    #zm = ZommedTextWidget(im)
    #zm.show()
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


