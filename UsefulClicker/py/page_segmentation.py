
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

from cnn1 import ConvNet
import subprocess
import torch 
import torch.nn as nn
import torchvision
import torchvision.transforms as transforms
import numpy as np

# Device configuration
#device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')

class PageSegmentor():
    def __init__(self, num_classes=4):
        self.model = ConvNet(num_classes).to(device)
        self.model.load_state_dict(torch.load('model_cnn_text_rect_segmentation.ckpt'))
        self.model.eval()

    def predict(self, image):
        trs = transforms.ToTensor()                    
        image_tensor = trs(  image / 255.0).type(torch.FloatTensor)
        #print(f'tensor size = {image_tensor.size()}')
        image_tensor = image_tensor.to(device)
        my_list = []
        for i in range(0,16,1):
            my_list.append(image_tensor.reshape(1,1,28,28))
        my_tensor = torch.cat(my_list, dim=0)
        #print(f'my_tensor size = {my_tensor.size()}')
        
        #I = torch.Tensor([16, image_tensor])
        outputs = self.model(my_tensor)
        _, predicted = torch.max(outputs.data, 1)
        return predicted[0].item()
        



# a = torch.arange(8).reshape(1, 1, 1)
# b = torch.arange(12).reshape(2, 2, 3)
# my_list = [a, b]
# my_tensor = torch.cat([a, b], dim=2)