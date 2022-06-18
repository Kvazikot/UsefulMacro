# -*- coding: utf-8 -*-
"""
Created on Fri Jun 17 14:35:39 2022

@author: HP
"""
import random
import sys
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
    def __init__(self, num_extra=400):
        self.img_labels = []
        self.img_tensors = []
        trs = transforms.ToTensor()
        # traverse root directory, and list directories as dirs and files as files
        for root, dirs, files in os.walk("./data/."):
            path = root.split(os.sep)
            label = -1
            
            if len(path) == 2:
                if is_int(path[1]):
                    label = int(path[1])
                else:
                    continue
            else:
              continue
                    
            #print((len(path) - 1) * '---', os.path.basename(root))
            for file in files:
                if label!=-1:
                    #print(str(label) + '---' + str(file))
                    #self.img_tensors
                    im = Image.open(root+'/'+file) 
                    gray_image = ImageOps.grayscale(im)                    
                    trs = transforms.ToTensor()                    
                    image_tensor = trs(  (np.asarray(gray_image)) / 255.0).type(torch.FloatTensor)
                    #print('tensor size ' + str(image_tensor.size()))

                    #print(image_tensor.size())
                    self.img_tensors.append(image_tensor)
                    self.img_labels.append(label)
          
           # make clones of loaded images with affine transforms
        
        add_images = []
        add_labels = []
        trns_functions = [transforms.GaussianBlur(3), 
                          transforms.RandomInvert(0.3),
                          transforms.RandomHorizontalFlip()]
        
        for i in range(0,num_extra,1):
            choice = random.randint(0, len(self.img_labels)-1)
            l = self.img_labels[choice]
            im = self.img_tensors[choice]
            choice2 = random.randint(0,len(trns_functions)-1) 
            fun = trns_functions[choice2]
            add_images.append(fun(im))
            add_labels.append(l)
           
        
        for im,l in zip(add_images, add_labels):
            self.img_tensors.append(im)       
            self.img_labels.append(l)
        
        print(f'Folder dataset is loaded: {len(self.img_labels)} ' )

                
        # load images fromm 'data' folder

    def __len__(self):
        return len(self.img_tensors)

    def __getitem__(self, idx):        
        image = self.img_tensors[idx]
        label = self.img_labels[idx]
        return image, label


def GenerateFolderDataset():
    test_dataset = FolderDataset(10)
    grid = torchvision.utils.make_grid(test_dataset.img_tensors, nrow=10, padding=10)
    npimg = grid.numpy()
    plt.imshow(np.transpose(npimg, (1,2,0)), interpolation='nearest')
    return test_dataset

#------------------------------------------------------------------------------
#GenerateFolderDataset()

# train_dataset = torchvision.datasets.MNIST(root='../../data/',
#                                              train=True, 
#                                              transform=transforms.ToTensor(),
#                                              download=True)

# tmp_list = []
# for i in range(0,10,1):
# #for i in range(0,train_dataset.train_data.shape[0],1):
#     img=train_dataset.train_data[i,:,:]
#     #img = np.random.normal(size=(100,150))
#     plt.figure(1); plt.clf()
#     plt.imshow(img)
#     plt.title('Number ' + str(i))
#     #plt.pause(3)
#     #print(img.shape)
#     #transform=transforms.ToTensor()
#     tmp_list.append(img)

# grid = torchvision.utils.make_grid(tmp_list, nrow=10, padding=10)
# npimg = grid.numpy()
# plt.imshow(np.transpose(npimg, (1,2,0)), interpolation='nearest')
