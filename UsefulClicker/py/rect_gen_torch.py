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
from PIL import ImageFilter, ImageOps
from PIL import Image, ImageDraw, ImageFont, ImageFilter
import numpy as np
from torch.utils.data import Dataset
#from torchvision import datasets
#from torchvision.transforms import ToTensor
from torch.utils.data import DataLoader , TensorDataset

alphabet = 'zxcvbnmasdfghjkqwertyui'

def rand_string(min_l, max_l):
    out=""
    n_symbols = random.randint(min_l, max_l)
    while n_symbols > 0:
        n = random.randint(0, len(alphabet)-1 )
        out+=alphabet[n] 
        n_symbols-=1
    return out

    

def gen_rect(image_size):
    canvas = Image.new('RGB', image_size, (255, 255, 255))
    draw = ImageDraw.Draw(canvas)
    w = random.randint(0, image_size[0])
    h = random.randint(0, image_size[0])
    #print(f'w={w} h={h}')
    #draw.rectangle([0,0,w,h])
    r = 100 / random.randint(1, 10)  
    canvas1 = canvas
    label = 0
    if r < 20:    
        draw.ellipse([0,0,w,h],fill="rgb(25,30,150)", outline="rgb(255,255,150)", width=5)
        label = 1
    if r > 20 and r < 80:
        draw.rectangle([0,0,w,h],fill="rgb(25,30,150)", outline="rgb(255,255,150)", width=5)
        label = 2
    if r > 60:
        canvas1 = text_phantom(canvas, rand_string(1,10), image_size[0])
        label = 3
    
    canvas2 = canvas1.filter(ImageFilter.GaussianBlur(3))
    gray_image = ImageOps.grayscale(canvas2)
    #plt.imshow(canvas1)
    trs = transforms.ToTensor()
    image_tensor = trs( (255 - np.asarray(gray_image)) / 255.0).type(torch.FloatTensor)
    #print(image_tensor.)
    return image_tensor, label

def text_phantom(canvas, text, size):
    # Availability is platform dependent
    font = 'arial'
    # Create font
    pil_font = ImageFont.truetype(font + ".ttf", size=size //2,
                                  encoding="unic")   
    text_width, text_height = pil_font.getsize(text)
    # create a blank canvas with extra space between lines
    # draw the text onto the canvas
    draw = ImageDraw.Draw(canvas)
    offset = ((size - text_width) // 2,
              (size - text_height) // 2)
    white = "#0004AA"
    draw.text(offset, text, font=pil_font, fill=white)
    # Convert the canvas into an array with values in [0, 1]
    #return (255 - np.asarray(canvas)) / 255.0
    return canvas

def show(img):
    npimg = img.numpy()
    plt.imshow(np.transpose(npimg, (1,2,0)), interpolation='nearest')



class ImageDataset(Dataset):
    def __init__(self, rect_tensors, img_labels, transform=None, target_transform=None):
        self.img_labels = img_labels
        self.rect_tensors = rect_tensors
        self.transform = transform
        self.target_transform = target_transform

    def __len__(self):
        return len(self.rect_tensors)

    def __getitem__(self, idx):        
        image = self.rect_tensors[idx]
        label = self.img_labels[idx]
        if self.transform:
            image = self.transform(image)
        if self.target_transform:
            label = self.target_transform(label)
        return image, label

def GenerateImageDataset(n):
    num_rects = n
    image_size = [28,28]
    rect_tensors = []
    labels = []
    for i in range(0,num_rects,1):
        rect, label = gen_rect(image_size)            
        rect_tensors.append(rect)
        labels.append(label)
    dataset = ImageDataset(rect_tensors, labels)
    grid = torchvision.utils.make_grid(rect_tensors, nrow=10, padding=10)
    show(grid)    
    return dataset


dataset=GenerateImageDataset(1000)
#print(next(iter(dataset)))
