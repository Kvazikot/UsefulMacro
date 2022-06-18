# https://pytorch.org/tutorials/beginner/blitz/cifar10_tutorial.html
# INSTALLING C++ DISTRIBUTIONS OF PYTORCH
# https://pytorch.org/cppdocs/installing.html
import sys
import torch
import torchvision
from torchvision import transforms
import torchvision.transforms as transforms
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import torch.nn as nn
import torch.nn.functional as F
import os
import pandas as pd
from torchvision.io import read_image
from torch.utils.data import Dataset
from rect_gen_torch import GenerateImageDataset
from torch.utils.data import DataLoader , TensorDataset

# CNN implementation
class Net(nn.Module):
    def __init__(self):
        super().__init__()
        self.conv1 = nn.Conv2d(1, 16, 7)
        self.pool = nn.MaxPool2d(2, 2)
        self.conv2 = nn.Conv2d(16, 32, 7)
        self.fc1 = nn.Linear(32, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)

    def forward(self, x):
        x = self.pool(F.relu(self.conv1(x)))
        x = self.pool(F.relu(self.conv2(x)))
        x = torch.flatten(x, 1) # flatten all dimensions except batch
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc3(x)
        return x


net = Net()
criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(net.parameters(), lr=0.001, momentum=0.9)

rect_dataset = GenerateImageDataset(16*100)
#testloader = torch.utils.data.DataLoader(rect_dataset, batch_size=16, shuffle=True)
trainloader =  torch.utils.data.DataLoader(rect_dataset, batch_size = 16, shuffle=True)

if __name__ ==  '__main__':
    
    for epoch in range(2):  # loop over the dataset multiple times
    
        running_loss = 0.0
        for i, data in enumerate(rect_dataset, 0):
            # get the inputs; data is a list of [inputs, labels]
            inputs, labels = data
            
            print(labels)
    
            # continue
            # zero the parameter gradients
            optimizer.zero_grad()
    
            # forward + backward + optimize
            outputs = net(inputs)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()
    
            # print statistics
            running_loss += loss.item()
            if i % 2000 == 1999:    # print every 2000 mini-batches
                print(f'[{epoch + 1}, {i + 1:5d}] loss: {running_loss / 2000:.3f}')
                running_loss = 0.0

print('Finished Training')

# Let’s quickly save our trained model:
#PATH = './cifar_net.pth'
#torch.save(net.state_dict(), PATH)


#sys.exit(0)
    
# TEST THE NETWORK
#dataiter = iter(testloader)
#images, labels = dataiter.next()

# print images
#imshow(torchvision.utils.make_grid(images))
#print('GroundTruth: ', ' '.join(f'{classes[labels[j]]:5s}' for j in range(4)))