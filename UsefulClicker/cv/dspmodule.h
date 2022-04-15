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
    QImage last_screenshot;

    DspModule();
    void computeHaudorf();
    QRect searchImage(std::string TargetIn_path, std::string SearchIn_path);
    void detectButtons(int screen_num, int kernel_size, std::vector<QRect>& rects);
    QImage saveImage(QRect roi, QString& filename);
    void findTextAreas();
    int X, Y;
    QRect matchedRectangle;


signals:
    void sigSendImage(QImage& image, int n_screen);
};

#endif // DSPMODULE_H
