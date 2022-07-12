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
import random
import torch
import torchvision
from torch.utils.data import Dataset
from torch.utils.data import DataLoader , TensorDataset
from torchvision import transforms

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
import torch.nn as nn
import numpy as np
import string
#import jquery_rc
from xml.dom.minidom import parseString
import matplotlib.pyplot as plt

   

class LettersDataset(Dataset):
    def __init__(self):
        self.img_labels = []
        self.img_tensors = []

    def __len__(self):
       return len(self.img_tensors)

    def save(self, dsp, alphabet, sample_dim):
        print("saving training samples...")
            
        csv_lines=[]
        n_letter = 0
        # saving part of image that is filtered using TextMask filter 
        prev_x = 0
        sorted_by_x = []
        #for countour in dsp.contours_filtred:
        #    x,y,w,h = cv2.boundingRect(countour)

        sorted_by_x = sorted(dsp.contours_filtred, key=lambda x: cv2.boundingRect(x)[0], reverse=False)


        for countour in sorted_by_x:
            x,y,w,h = cv2.boundingRect(countour)
            delta_x = x - prev_x
            if delta_x < 0:
                n_letter = 0
            print(f'saving rect {x} {y} {w} {h}')
            roi=dsp.areaImg[y:y+h,x:x+w]
            resized = cv2.resize(roi, sample_dim, interpolation = cv2.INTER_AREA)
            number = random.randint(0,100000)
            label = ord(alphabet[n_letter])
            trs = transforms.ToTensor()
            image_tensor = trs(  (np.asarray(resized)) / 255.0).type(torch.FloatTensor)
            print(f"label = {label} code={label} letter = {alphabet[n_letter]}")
            print('tensor size ' + str(image_tensor.size()))
            #print(image_tensor.size())
            self.img_tensors.append(image_tensor)
            self.img_labels.append(label)
            n_letter+=1
            print(n_letter)
            prev_x = x
   
        

    def __getitem__(self, idx):        
       image = self.img_tensors[idx]
       label = self.img_labels[idx]
       
       return image, label

#-----------------------------------------------------------------------------
#-----------------------------------------------------------------------------


class OcrWebSpyder(QMainWindow):
    def generateHTML(self):
        modes = {'html':0, 'image':1}
        lang_code = {'eng':0, 'ukr': 1, 'jp':2, 'sw':5, 'sp': 4, 'rus': 6, 'can': 7}
    
        def letter_range(start, stop="{", step=1):
            """Yield a range of lowercase letters.""" 
            for ord_ in range(ord(start.lower()), ord(stop.lower())+1, step):
                yield chr(ord_)
    
    
        self.eng_alphabet = string.ascii_lowercase
        self.rus_aphabet =  list(letter_range("а", "я"))
        self.rus_aphabet = "".join(self.rus_aphabet)
    
        print(self.eng_alphabet)
        print(self.rus_aphabet)
    
        letter_spacing = 5
        font_size = 24
        link_additional_fonts = "<link href=\"https://fonts.googleapis.com/css2?family=Lobster&display=swap\" rel=\"stylesheet\">"
        html_code=f"<div align=\"left\" style=\"font-family: 'Lobster'; letter-spacing:{letter_spacing}px\">{self.rus_aphabet}<br/>"
        database = QFontDatabase()
        #html_code=f"<div style=\"font-family: 'Lobster'; letter-spacing:{letter_spacing}px\">{rus_aphabet}<br/>"
        #for family in database.families():
        #    html_code+=f"<div style=\"font-size:{font_size}px; font-family: '{family}'; letter-spacing:{letter_spacing}px\">{rus_aphabet}<br/>"
            #print(family)
        html_code+="</div>"
        #html_code+=f"<div style=\"letter-spacing:{letter_spacing}px\">{eng_alphabet}<br/></div>"
        style_block = "<style>  hr.new1 {   border-top: 1px solid red; }  </style>"       
        html_template=""
        html_template = f"<!DOCTYPE html><html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">{link_additional_fonts}{style_block}<title>title</title></head><body>{html_code}</body></html>"
        with open(".\saved_web_pages\myfile.html", "wb") as html_file:
            html_file.write(html_template.encode("utf-8"))
            html_file.close()
           

    
    def __init__(self, url):
        super(OcrWebSpyder, self).__init__()

        self.progress = 0
        self.dsp = Dsp()
        self.sample_dim = (28, 28)
        self.generateHTML()

        QNetworkProxyFactory.setUseSystemConfiguration(True)

        self.view = QWebEngineView(self)
        self.view.load(url)
        self.view.loadProgress.connect(self.setProgress)
        self.view.loadFinished.connect(self.finishLoading)

        self.setCentralWidget(self.view)
        
    
    
    def finishLoading(self):
        self.progress = 100
        screen = QApplication.screens()[0]
        windowGeometry = screen.geometry()
        self.view.move(windowGeometry.topLeft());
        self.view.resize(windowGeometry.size());

        QTimer.singleShot(1000, self.DrawDetectedContours)

    def setProgress(self, p):
        self.progress = p
    


    
    def DrawDetectedContours(self):
        self.dsp.detectButtons(0, kernel_size=4)
        img, contours = self.dsp.detectSymbols(self.dsp.areaImg)
        w = self.dsp.areaImg.shape[1]
        h = self.dsp.areaImg.shape[0]
        img = np.zeros((w,h,3), dtype=np.uint8)
        for c in contours:
            cv2.drawContours(img, [c], 0, (random.randint(1,55),0,random.randint(134,224)), thickness=1)
        test_dataset = LettersDataset()
        test_dataset.save(self.dsp, self.rus_aphabet, (28, 28))
        grid = torchvision.utils.make_grid(test_dataset.img_tensors, nrow=len(self.rus_aphabet), padding=10)
        npimg = grid.numpy()
        plt.imshow(np.transpose(npimg, (1,2,0)), interpolation='nearest')

        
        #cv2.imshow("w0", img)

    def closeEvent(self, a0):        
        cv2.destroyWindow("w0") 
        cv2.destroyWindow("w1") 


#-----------------------------------------------------------------------------
#-----------------------------------------------------------------------------

# Hyper parameters
num_epochs = 100
num_classes = 33
batch_size = 16
learning_rate = 0.01

# Convolutional neural network (two convolutional layers)
class LetterNet(nn.Module):
    def __init__(self, num_classes=10):
        super(LetterNet, self).__init__()
        self.layer1 = nn.Sequential(
            nn.Conv2d(1, 16, kernel_size=5, stride=1, padding=2),
            nn.BatchNorm2d(16),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2, stride=2))
        self.layer2 = nn.Sequential(
            nn.Conv2d(16, 32, kernel_size=5, stride=1, padding=2),
            nn.BatchNorm2d(32),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2, stride=2))
        self.fc = nn.Linear(7*7*32, num_classes)
        
    def forward(self, x):
        out = self.layer1(x)
        out = self.layer2(out)
        out = out.reshape(out.size(0), -1)
        out = self.fc(out)
        return out

#-----------------------------------------------------------------------------
#-----------------------------------------------------------------------------

def StartTraining():
    # Device configuration
    device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
    #device = torch.device("cpu")
    
    #print(device)
    #print(torch.version.cuda)
    
    train_dataset = LettersDataset(num_epochs*10)
    #testloader = torch.utils.data.DataLoader(rect_dataset, batch_size=16, shuffle=True)
    
    # Data loader
    train_loader = torch.utils.data.DataLoader(dataset=train_dataset,
                                               batch_size=batch_size, 
                                               shuffle=True)
    #print(next(iter(train_dataset)))
    print('------------------------------------')
    print('------------------------------------')
    print('------------------------------------')
    #print(train_dataset.img_labels)
    #sys.exit(0)
    
    model = LetterNet(num_classes).to(device)
    
    # Loss and optimizer
    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
    
    
    # variables for drawing loss curve
    x_epoch = []
    y_loss = []
    running_loss = 0
    
    # Train the model
    total_step = len(train_loader)
    for epoch in range(num_epochs):
        for i, (images, labels) in enumerate(train_loader):
            images = images.to(device)        
            labels = labels.to(device)
            print(f'images size = {images.size()}')
            
            # Forward pass
            outputs = model(images)
            #print(labels)
            loss = criterion(outputs, labels)
            
            # Backward and optimize
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
            
            # statistics
            running_loss += loss.item() * batch_size
            
            y_loss.append(running_loss/(epoch+1))
            x_epoch.append(epoch)    
            
            if (i+1) % 10 == 0:    
                plt.plot(x_epoch, y_loss)
                plt.show()
            
            #if (i+1) % 100 == 0:
                print ('Epoch [{}/{}], Step [{}/{}], Loss: {:.4f}' 
                       .format(epoch+1, num_epochs, i+1, total_step, loss.item()))
    
    # Test the model
    # model.eval()  # eval mode (batchnorm uses moving mean/variance instead of mini-batch mean/variance)
    # with torch.no_grad():
    #     correct = 0
    #     total = 0
    #     for images, labels in test_loader:
    #         images = images.to(device)
    #         labels = labels.to(device)
    #         outputs = model(images)
    #         _, predicted = torch.max(outputs.data, 1)
    #         total += labels.size(0)
    #         correct += (predicted == labels).sum().item()
    
    #     print('Test Accuracy of the model on the 10000 test images: {} %'.format(100 * correct / total))
    
    # Save the model checkpoint
    torch.save(model.state_dict(), 'model.ckpt')

if __name__ == '__main__':

    import sys
    
    app = QApplication(sys.argv)
    page1 = 'file:///C:/Projects/UsefulClicker/py/saved_web_pages/myfile.html'
    url = QUrl(page1)   

    browser = OcrWebSpyder(url)
    scr=app.screens()[0]
    browser.setGeometry(scr.geometry())

    browser.showFullScreen()

    sys.exit(app.exec_())