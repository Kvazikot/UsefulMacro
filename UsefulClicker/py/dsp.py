/*
+ - - - + - + - -
+ - + - + copyright by Vladimir Baranov (Kvazikot)  <br>
+ - + - + email: vsbaranov83@gmail.com  <br>
+ - + - + github: https://github.com/Kvazikot/UsefulMacro/  <br>
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
import subprocess
# This is our shell command, executed by Popen.
import os
import sys
import cv2
import numpy as np
from  cv2 import Mat, connectedComponentsWithStats
from PyQt5.QtWidgets import QWidget, QApplication 
from PyQt5.QtGui import QPainter, QColor, QFont, QImage, QPixmap, QCursor  
from PyQt5.QtCore import Qt, QRect

class Dsp:
    def __init__(self):
        super().__init__()
        self.rects = []
        print("hello DSP!")
        self.detectButtons(0, 10, self.rects)
        
    def detectButtons(self, screen_num, kernel_size, rects):
        if len(QApplication.screens()) < screen_num :
           return
        print(len(QApplication.screens()))
        screen = QApplication.screens().pop(screen_num)
        print( QApplication.screens() )
        screenshot = QImage()
        #screenshot = screen.grabWindow().toImage()
        desktop = QApplication.desktop()
        screenId = desktop.screenNumber(QCursor.pos())
        geom = desktop.screenGeometry(screenId)
        x = geom.x()
        y = geom.y()
        screenshot = QApplication.screens()[0].grabWindow(
                 desktop.winId(), x, y, geom.width(), geom.height()).toImage()
        #areaImg = cv2.Mat((screenshot.height(), screenshot.width()), cv2.CV_8UC4, screenshot.bits())
        #im_gray = Mat()
        #canny_output = Mat()
        areaImg = np.zeros((screenshot.height(), screenshot.width() ,3), dtype=np.uint8)
        bufersize = screenshot.height() * screenshot.width() * 4
        print("wss " + str(screenshot.bits()))
        self.screenshot = screenshot
        b = screenshot.bits()        
        # sip.voidptr must know size to support python buffer interface
        channels_count = 4
        print(screenshot.bitPlaneCount())
        b.setsize(screenshot.height() * screenshot.width() * channels_count)
        areaImg = np.frombuffer(b, np.uint8).reshape((screenshot.height(), screenshot.width(), channels_count))
        im_gray = cv2.cvtColor(areaImg, cv2.COLOR_BGR2GRAY)
        im_gray = cv2.blur( im_gray, (3,3) );
        #cv2.imshow("im_gray", im_gray)
        thresh = 100
        canny_output = cv2.Canny(im_gray, thresh, thresh * 2 )
        rect_kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (kernel_size, kernel_size))
        labels = np.zeros((screenshot.height(), screenshot.width(), 3), dtype=np.uint8)
        stats = np.zeros((screenshot.height(), screenshot.width(), 3), dtype=np.uint8)
        centroids = np.zeros((screenshot.height(), screenshot.width(), 3), dtype=np.uint8)
        canny_output = cv2.dilate(canny_output, rect_kernel)
        #cv2.connectedComponentsWithStats(canny_output, labels, stats, centroids)
        output = cv2.connectedComponentsWithStats(canny_output, connectivity=4)
        (numLabels, labels, stats, centroids) = output
        im_gray = cv2.cvtColor(im_gray, cv2.COLOR_GRAY2RGB)
        print('numLabels ' + str(numLabels))
        
        #cv2.imshow("labels", labels)
        print(stats.shape)
        if stats.shape[1] == 5:
            for i in range(0, numLabels, 1):
                x = stats[i, cv2.CC_STAT_LEFT]
                y = stats[i, cv2.CC_STAT_TOP]
                w = stats[i, cv2.CC_STAT_WIDTH]
                h = stats[i, cv2.CC_STAT_HEIGHT]
                print(x)
                #if  ( w < maxRectWidth) and (h < maxRectHeight ) and (w > 0) and (h >0) :
                rects.append(QRect(x,y,w,h));
        


class Example(QWidget):

    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.dsp = Dsp()
        self.rects = []
        self.setWindowOpacity(0.8)
        self.dsp.detectButtons(0, 4, self.rects)
        self.image = QImage('./rect_images\\00.06.36.730.png')
        self.setGeometry(300, 300, 350, 300)
        self.setWindowTitle('Drawing')
        self.show()
        
    def paintEvent(self, event):
        qp = QPainter()
        qp.begin(self)
        qp.drawImage(0,0,self.dsp.screenshot)
        qp.fillRect(self.rect(), QColor(1,1,1,110))        
        
        for r in self.rects:
            qp.fillRect(r, QColor(1,244,1,110))
            
        qp.end()



def main():
    app = QApplication(sys.argv)
    ex = Example()
    ex.showFullScreen()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()

path = "./rect_images"

fname = []
for root,d_names,f_names in os.walk(path):
	for f in f_names:
		fname.append(os.path.join(root, f))

print("fname = %s" %fname)

#p = subprocess.Popen("dir", stdout=subprocess.PIPE, shell=True)
#print(p.communicate())



