# -*- coding: utf-8 -*-
"""
Created on Fri Jun 17 14:35:39 2022

@author: HP
"""
import torch
import torchvision
from torch.utils.data import Dataset
from torch.utils.data import DataLoader , TensorDataset
from torchvision import transforms
import os
import numpy as np
from PIL import Image
from PIL import ImageOps
import matplotlib.pyplot as plt
# This is our shell command, executed by Popen.

def is_int(value):
  try:
    int(value)
    return True
  except:
    return False
#------------------------------------------------------------------------------
class FolderDataset(Dataset):
    def __init__(self):
        self.img_labels = []
        self.img_tensors = []
        trs = transforms.ToTensor()
        # traverse root directory, and list directories as dirs and files as files
        for root, dirs, files in os.walk("./data/."):
            path = root.split(os.sep)
            label = -1
            
            if len(path) == 2:
                if is_int(path[1]):
                    label = path[1]
                    
            #print((len(path) - 1) * '---', os.path.basename(root))
            for file in files:
                if label!=-1:
                    print(str(label) + '---' + str(file))
                    self.img_labels.append(label)
                    #self.img_tensors
                    im = Image.open(root+'/'+file) 
                    gray_image = ImageOps.grayscale(im)
                    trs = transforms.ToTensor()
                    image_tensor = trs( (255 - np.asarray(gray_image)) / 255.0).type(torch.FloatTensor)
                    self.img_tensors.append(image_tensor)

                
        # load images fromm 'data' folder

    def __len__(self):
        return len(self.img_tensors)

    def __getitem__(self, idx):        
        image = self.img_tensors[idx]
        label = self.img_labels[idx]
        return image, label


test_dataset = FolderDataset()
grid = torchvision.utils.make_grid(test_dataset.img_tensors, nrow=10, padding=10)
npimg = grid.numpy()
plt.imshow(np.transpose(npimg, (1,2,0)), interpolation='nearest')

