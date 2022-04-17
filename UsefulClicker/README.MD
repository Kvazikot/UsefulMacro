This project is licensed under the terms of the GNU General Public License v3.0

/*
+ - - - + - + - -
+ - + - + copyright by Vladimir Baranov (Kvazikot) <br>
+ - + - + email: vsbaranov83@gmail.com <br>
+ - + - + github: https://github.com/Kvazikot/UsefulMacro/UsefulClicker <br>
```
                          ) (
                         /( (\___/) )\
                        (#) \ ('')| (#
                         ||___c\ > '__||
                         ||**** ),_/ **'|
                   .__ |'* ___| |___*'|
                    \_\ |' ( ~ ,)'|
                     (( |' /(. ' .)\ |
                      \\_|_/ <_ _____> \______________
                       / '-, \ / ,-' ______ \
              b'ger/(//\\)__//\
                                          './_____/
```
*/
## About Useful Clicker
The UC program is intended for programming user actions.
For example, to automatically search for materials in youtube and download certain videos.
The program has a built-in computer vision functionality, i.e. it can identify the buttons on the screen by analyzing the pixels in the image.
In this sense, it works similar to how the retina of an animal's eye works.
The buttons are highlighted in green in the style of augmented reality.

![image](https://github.com/Kvazikot/UsefulMacro/blob/master/UsefulClicker/screenshots/buttons_detector_screenshot.png)

fig.1 Button detector

![image](https://github.com/Kvazikot/UsefulMacro/blob/master/UsefulClicker/screenshots/delay_widget.png)

fig.2 Widget for setting delays

![image](https://github.com/Kvazikot/UsefulMacro/blob/master/UsefulClicker/screenshots/xml_editor_screenshot.png)

Fig.3 Clicker program editor in the form of an xml tree.

![image](https://github.com/Kvazikot/UsefulMacro/blob/master/UsefulClicker/screenshots/mainwindow_0.92.png)

fig.4 The editor of the clicker program in the form of an xml tree with pictures on the right.

![image](https://github.com/Kvazikot/UsefulMacro/blob/master/UsefulClicker/screenshots/testform_0.92.png)

fig.5 Cool test program


## New concept for Useful Clicker (3/28/2022)
The program must recognize the context. Those. which window is currently on the screen, which buttons are on the screen.
It circles all the buttons in green, and the button to be clicked in red.
He also signs the sequence number of the action next to the button.
All this can be arranged in a full-screen semi-transparent widget.
The "Next Frame" and "Previous Frame" buttons at the top of the screen.
That is, the clicker also works in the clicker programming mode. To return the previous window e.g.

## The idea for an astronomical number of screenshots for reverse engineering human software (came from Marvell comics)
We need to create an astronomical number of screenshots for all sorts of programs and operating systems.
Each dialog box is unique to the program. Therefore, the clicker will be oriented towards reverse engineering of traditional software.
Soon, according to the idea of ​​Mask, all traditional software i.e. the expertise of some engineer will replace neural networks.
But we need to prepare a description of the functions of every program on Earth that has ever existed.
So that the future AGI can use these compiled programs for its calculations.
So that he does not need to invent the wheel, roughly speaking
Since AGI thinks orders of magnitude faster than humans, it will be able to use human software
in such interesting combinations that people never even dreamed of. But this information should be available.
In order not to waste time on reverse engineering.
Perhaps at some stage AGI will be able to explore various software written by people.
By disassembling it.
To do this, I provided the Function Description window, which a person must fill out.
  
This idea is explained in more detail in the next video.
https://youtu.be/BYM5G5CIgS8

## Disadvantages of Auto Mouse Clicker by MurGee

What would you like to improve in a clone of the program with the working name UsefulClicker?

0. Not free
1. works only under Windows (platform-dependent limitation of free will)
2. Lack of full export in csv format.
In particular, the inability to save Hot Key combinations is frightening.
2. You cannot run multiple scripts within the same process.
For example, viewing mail, then arbitrary switching of a circular search in YouTube, etc.
2.1 There is no concept of procedure or function in the program.
In the action table, I cannot collapse the actions into a closure and name it somehow.
And then make a place for the main loop at the bottom of the action table

3. There is no script export to any of the known programming languages, in particular
visual basic.
4. The action dropdown menu is too large. I would limit myself to the following (see [LA1]).
5. You cannot move multiple actions in the list.
6. You can not copy paste the lines of the table \ script
7. Actions go to the end of the list, not to the selection.
8. NOT GPU optimized
9. No image search at different scales.
10. You can not change comments directly in the table
