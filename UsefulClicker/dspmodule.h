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

#ifndef DSPMODULE_H
#define DSPMODULE_H

#include <QObject>
#include <QImage>
#include <vector>
#include <opencv.hpp>

class DspModule : public QObject
{
    Q_OBJECT
public:
    std::vector<cv::Rect> text_areas;

    DspModule();
    void computeHaudorf();
    void detectButtons(int screen_num, QImage& in_out_image, std::vector<QRect>& rects);
    void findTextAreas();
    int X, Y;

signals:
    void sigSendImage(QImage& image, int n_screen);
};

#endif // DSPMODULE_H
