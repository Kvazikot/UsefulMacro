# -*- coding: utf-8 -*-
"""
Created on Sun Jun  5 12:36:19 2022

@author: HP
"""
import torch
import torchvision
import matplotlib.pyplot as plt
import random
import numpy as np
from torchvision import transforms
from PIL.ImageFilter import *
from PIL import ImageFilter
from PIL import Image, ImageDraw, ImageFont, ImageFilter
import numpy as np

def gen_rect(image_size):
    canvas = Image.new('RGB', image_size, (255, 255, 255))
    draw = ImageDraw.Draw(canvas)
    w = random.randint(0, image_size[0])
    h = random.randint(0, image_size[0])
    print(f'w={w} h={h}')
    #draw.rectangle([0,0,w,h])
    draw.ellipse([0,0,w,h],fill="rgb(25,30,150)", outline="rgb(255,255,150)", width=5)
    canvas1 = canvas.filter(ImageFilter.GaussianBlur(3))
    plt.imshow(canvas1)
    trs = transforms.ToTensor()
    return trs( (255 - np.asarray(canvas)) / 255.0)

def text_phantom(text, size):
    # Availability is platform dependent
    font = 'arial'
    
    # Create font
    pil_font = ImageFont.truetype(font + ".ttf", size=size // len(text),
                                  encoding="unic")
    
    text_width, text_height = pil_font.getsize(text)

    # create a blank canvas with extra space between lines
    canvas = Image.new('RGB', [size, size], (255, 255, 255))

    # draw the text onto the canvas
    draw = ImageDraw.Draw(canvas)
    draw.ellipse([0,0,size/2,size/2],"rgb(255,0,0)" )
    offset = ((size - text_width) // 2,
              (size - text_height) // 2)
    white = "#0000AA"
    draw.text(offset, text, font=pil_font, fill=white)

    # Convert the canvas into an array with values in [0, 1]
    return (255 - np.asarray(canvas)) / 255.0

def show(img):
    npimg = img.numpy()
    plt.imshow(np.transpose(npimg, (1,2,0)), interpolation='nearest')

w = torch.randn(10,3,200,640)
trs = transforms.ToTensor()
t1 = trs(text_phantom('dar',100))
t2 = trs(text_phantom('ar',100))
num_rects = 10
image_size = [128,128]
rect_tensors = []
for i in range(0,num_rects,1):
    t = gen_rect(image_size)    
    rect_tensors.append(t)
    
#text_phantom()
#plt.imshow(text_phantom('A', 200))
#plt.imshow(text_phantom('Longer text', 200))
grid = torchvision.utils.make_grid(rect_tensors, nrow=10, padding=10)
#show(grid)