import sys
from matplotlib import pyplot as plt
import torch 
import torch.nn as nn
import torchvision
import torchvision.transforms as transforms
from rect_gen_torch import GenerateImageDataset
from folder_dataset import FolderDataset

# Hyper parameters
num_epochs = 100
num_classes = 4
batch_size = 16
learning_rate = 0.01

# Convolutional neural network (two convolutional layers)
class ConvNet(nn.Module):
    def __init__(self, num_classes=10):
        super(ConvNet, self).__init__()
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

def StartTraining():
    # Device configuration
    device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
    #device = torch.device("cpu")
    
    #print(device)
    #print(torch.version.cuda)
    
    # MNIST dataset
    # train_dataset = torchvision.datasets.MNIST(root='../../data/',
    #                                              train=True, 
    #                                              transform=transforms.ToTensor(),
    #                                              download=True)
    
    #train_dataset = GenerateImageDataset(num_recs)
    train_dataset = FolderDataset(num_epochs*10)
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
    
    model = ConvNet(num_classes).to(device)
    
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