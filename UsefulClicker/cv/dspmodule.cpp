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

#include <QObject>
#include <QScreen>
#include <QDir>
#include <QDateTime>
#include <cmath>
#include <QGuiApplication>
#include <QDebug>
#include <QFileInfo>
#include <QPainter>
#include <vector>
#include <xmmintrin.h>
#include "cv/dspmodule.h"
#include "settings/clickersettings.h"
#include <malloc.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/shape/shape_distance.hpp>

float a[256] __attribute__((aligned(16)));
float b[256] __attribute__((aligned(16)));
float rv[256] __attribute__((aligned(16)));


unsigned int N = 0;
using namespace cv;
using namespace std;

DspModule::DspModule()
{

}

void print_vector(char* name, float* a, int len)
{
    QString str= QString(name) + "= {";
    for( int i = 0; i < len; i++)
    {
        str += QString::number(a[i]) + ",";
    }
}

// forward decl for very smart multistepthinking shit
void drawCounters(Size image_size, vector<vector<Point> >& contours, Mat background = Mat::zeros( 0, 0, CV_8UC3 ));

vector<vector<Point> > getCounters(Mat& TargetIn, bool andDraw)
{
    Mat canny_output, src, src_gray;
    src = TargetIn;

    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );
    int thresh = 100;
    Canny( src_gray, canny_output, thresh, thresh*2 );
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours( canny_output, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE );
    imwrite("canny_output.bmp", canny_output);

    if(andDraw) drawCounters(canny_output.size(), contours);
    return contours;
}

void drawCounters(Size image_size, vector<vector<Point> >& contours, Mat background )
{
    RNG rng(12345);
    Mat drawing = Mat::zeros( image_size, CV_8UC3 );
    if ( background.size().width != 0)
         drawing = background;
    for( size_t i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
        drawContours( drawing, contours, (int)i, color, 2, LINE_8, noArray(), 0 );
    }
}

QImage DspModule::saveImage(QRect roi, QString& filename)
{
    QDateTime dt;
    dt = dt.currentDateTime();
    //QString clickerPath = qEnvironmentVariable("UsefulClicker");
    //if(clickerPath.size() == 0)
    //    clickerPath = QDir::currentPath();
    QString clickerPath = "$(UsefulClicker)";
    filename = "\"" + clickerPath + "/images/" + dt.toString("hh.mm.ss.zzz.png") + "\"";
    //last_screenshot
    QImage outputImage(roi.width(),roi.height(), last_screenshot.format());
    outputImage = last_screenshot.copy(roi);
    clickerPath = QDir::currentPath();
    outputImage.save(clickerPath + "/images/" + dt.toString("hh.mm.ss.zzz.png"));
    return outputImage;
}

void DspModule::detectButtons(int screen_num, int kernel_size, vector<QRect>& rects)
{
    //makeScreenshot();
    QScreen* screen = QGuiApplication::screens()[screen_num];
    QImage screenshot = last_screenshot;
    if( last_screenshot.width() != screen->geometry().width() )
    {
        screenshot = screen->grabWindow(0,0,0,screen->geometry().width(), screen->geometry().height()).toImage();
        last_screenshot = screenshot;
    }
    Mat areaImg;
    areaImg.create(screenshot.height(), screenshot.width(), CV_8UC4);
    Mat mat(screenshot.height(), screenshot.width(),CV_8UC4, screenshot.bits());
    QRect r = screen->geometry();
    Rect rect1(r.left(),r.top(),r.width(),r.height());
    areaImg = Mat(mat, rect1);

    Mat im_gray,canny_output;
    cvtColor(areaImg, im_gray, COLOR_RGB2GRAY);
    //imwrite("out.png", im_gray);

    blur( im_gray, im_gray, Size(3,3) );
    int thresh = DEFAULT("canny_threshold").toInt();
    Canny( im_gray, canny_output, thresh, thresh*2 );
    //imwrite("canny.png", im_gray);
    Mat rect_kernel = getStructuringElement(MORPH_RECT, Size(kernel_size, kernel_size));
    dilate(canny_output, canny_output, rect_kernel, Point(-1, -1), 1);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours( canny_output, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE );

    vector<double> areas;
    //for(uint i=0; i < contours.size(); i++)
     //   areas.push_back( contourArea(contours[i]) );
    cvtColor(im_gray, im_gray, COLOR_GRAY2RGB);
    RNG rng(12345);
    for( size_t i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 100), rng.uniform(0,100), rng.uniform(0,100) );
        //drawContours( canny_output, contours, (int)i, color, 2, LINE_8, noArray(), 0 );
        cv::Rect r = minAreaRect(contours[i]).boundingRect();
        rectangle(im_gray, r, color, 4);
        rects.push_back(QRect(r.x,r.y,r.width,r.height));
    }

    //in_out_image = QImage((uchar*) drawing->data, drawing->cols, drawing->rows, drawing->step, QImage::Format_ARGB32);
    //imwrite("out.png", im_gray);

}

QRect DspModule::searchImage(std::string TargetIn_path, std::string SearchIn_path)
{
    Mat3b SearchIn = Mat3b::zeros(80,80);
    Mat3b TargetIn = Mat3b::zeros(80,80);
    QFileInfo fi;
    QString f1 = TargetIn_path.c_str();
    if(!fi.exists(f1)) return QRect();
    f1 = SearchIn_path.c_str();
    if(!fi.exists(f1)) return QRect();
    //if(fi.exists(TargetIn_path)) return QRect();
    //if(fi.exists(SearchIn_path)) return QRect();

    SearchIn = imread(SearchIn_path);
    TargetIn = imread(TargetIn_path);

    vector<vector<Point> > contours1 = getCounters(TargetIn, false);
    vector<vector<Point> > contours2 = getCounters(SearchIn, false);
    vector<vector<Point> > contours3;
    vector<double> areas1;
    vector<double> areas2;
    for(uint i=0; i < contours1.size(); i++)
        areas1.push_back( contourArea(contours1[i]) );
    for(uint i=0; i < contours2.size(); i++)
        areas2.push_back( contourArea(contours2[i]) );

    for(uint i=0; i < contours1.size(); i++)
        for(uint j=0; j < contours2.size(); j++)
        {
          // if( contours1[i].size() == contours2[j].size() )
            {
                vector<Point> v1, v2;
                float area_diff = qAbs(areas1[i] - areas2[j]);
                if(  area_diff < 3  )
                {
                    RotatedRect rect1 = minAreaRect(contours2[j]);
                    RotatedRect rect2 = minAreaRect(contours1[i]);
                    int delta_width = qAbs(rect1.boundingRect().width - rect2.boundingRect().width);
                    int delta_height = qAbs(rect1.boundingRect().height - rect2.boundingRect().height);
                    if(rect1.boundingRect().width < 15) continue;
                    if(rect1.boundingRect().height < 15) continue;
                    if(rect2.boundingRect().width < 15) continue;
                    if(rect2.boundingRect().height < 15) continue;

                    Mat cutfromSearch = Mat(SearchIn, rect1.boundingRect());
                    Mat cutfromTarget = Mat(TargetIn, rect2.boundingRect());
                    Mat hsv_base1, hsv_base2;
                    cvtColor( cutfromSearch, hsv_base1, COLOR_BGR2HSV );
                    cvtColor( cutfromTarget, hsv_base2, COLOR_BGR2HSV );
                    if(hsv_base1.size[0] == 0) continue;
                    if(hsv_base2.size[0] == 0) continue;
                    int h_bins = 50, s_bins = 60;
                    int histSize[] = { h_bins, s_bins };
                    // hue varies from 0 to 179, saturation from 0 to 255
                    float h_ranges[] = { 0, 180 };
                    float s_ranges[] = { 0, 256 };
                    const float* ranges[] = { h_ranges, s_ranges };
                    // Use the 0-th and 1-st channels
                    int channels[] = { 0, 1 };
                    Mat hist_base1, hist_base2;
                    calcHist( &hsv_base1, 1, channels, Mat(), hist_base1, 2, histSize, ranges, true, false );
                    normalize( hist_base1, hist_base1, 0, 1, NORM_MINMAX, -1, Mat() );
                    calcHist( &hsv_base2, 2, channels, Mat(), hist_base2, 2, histSize, ranges, true, false );
                    normalize( hist_base2, hist_base2, 0, 1, NORM_MINMAX, -1, Mat() );
                    double base_base = compareHist( hist_base1, hist_base2, 2 );
                    if(base_base > 1 )
                    {
                      contours3.push_back(contours2[j]);
                      if(int(area_diff) == 0)
                      {
                        X = rect1.boundingRect().x;
                        Y = rect1.boundingRect().y;
                        int w = rect1.boundingRect().width;
                        int h = rect1.boundingRect().height;
                        matchedRectangle = QRect(X,Y,w,h);
                        return QRect(X,Y,w,h);
                      }

                      qDebug("area_diff %f delta_width %d delta_height %d hist_compare %f %d %d", area_diff, delta_width, delta_height, base_base, i, j);

                    }


                }


            }
        }

    //drawCounters(SearchIn.size(), contours3, SearchIn);
    //drawCounters(TargetIn.size(), contours1, TargetIn);
    return  matchedRectangle;

}

void DspModule::computeHaudorf()
{
    Mat3b SearchIn = Mat3b::zeros(80,80);
    Mat3b TargetIn = Mat3b::zeros(80,80);

    SearchIn = imread("areaImg.bmp");
    TargetIn = imread("targetImg.bmp");

    vector<vector<Point> > contours1 = getCounters(TargetIn, false);
    vector<vector<Point> > contours2 = getCounters(SearchIn, false);
    vector<vector<Point> > contours3;
    vector<double> areas1;
    vector<double> areas2;
    for(uint i=0; i < contours1.size(); i++)
        areas1.push_back( contourArea(contours1[i]) );
    for(uint i=0; i < contours2.size(); i++)
        areas2.push_back( contourArea(contours2[i]) );

    for(uint i=0; i < contours1.size(); i++)
        for(uint j=0; j < contours2.size(); j++)
        {
          // if( contours1[i].size() == contours2[j].size() )
            {
                vector<Point> v1, v2;
                float area_diff = qAbs(areas1[i] - areas2[j]);
                if(  area_diff < 3  )
                {
                    RotatedRect rect1 = minAreaRect(contours2[j]);
                    RotatedRect rect2 = minAreaRect(contours1[i]);
                    int delta_width = qAbs(rect1.boundingRect().width - rect2.boundingRect().width);
                    int delta_height = qAbs(rect1.boundingRect().height - rect2.boundingRect().height);
                    if(rect1.boundingRect().width < 15) continue;
                    if(rect1.boundingRect().height < 15) continue;
                    if(rect2.boundingRect().width < 15) continue;
                    if(rect2.boundingRect().height < 15) continue;

                    Mat cutfromSearch = Mat(SearchIn, rect1.boundingRect());
                    Mat cutfromTarget = Mat(TargetIn, rect2.boundingRect());
                    Mat hsv_base1, hsv_base2;
                    cvtColor( cutfromSearch, hsv_base1, COLOR_BGR2HSV );
                    cvtColor( cutfromTarget, hsv_base2, COLOR_BGR2HSV );
                    if(hsv_base1.size[0] == 0) continue;
                    if(hsv_base2.size[0] == 0) continue;
                    int h_bins = 50, s_bins = 60;
                    int histSize[] = { h_bins, s_bins };
                    // hue varies from 0 to 179, saturation from 0 to 255
                    float h_ranges[] = { 0, 180 };
                    float s_ranges[] = { 0, 256 };
                    const float* ranges[] = { h_ranges, s_ranges };
                    // Use the 0-th and 1-st channels
                    int channels[] = { 0, 1 };
                    Mat hist_base1, hist_base2;
                    calcHist( &hsv_base1, 1, channels, Mat(), hist_base1, 2, histSize, ranges, true, false );
                    normalize( hist_base1, hist_base1, 0, 1, NORM_MINMAX, -1, Mat() );
                    calcHist( &hsv_base2, 2, channels, Mat(), hist_base2, 2, histSize, ranges, true, false );
                    normalize( hist_base2, hist_base2, 0, 1, NORM_MINMAX, -1, Mat() );
                    double base_base = compareHist( hist_base1, hist_base2, 2 );
                    if(base_base > 1 )
                    {
                      contours3.push_back(contours2[j]);
                      if(int(area_diff) == 0)
                      {
                        X = rect1.boundingRect().x;
                        Y = rect1.boundingRect().y;
                      }

                      qDebug("area_diff %f delta_width %d delta_height %d hist_compare %f %d %d", area_diff, delta_width, delta_height, base_base, i, j);

                    }


                }


            }
        }

    drawCounters(SearchIn.size(), contours3, SearchIn);
    drawCounters(TargetIn.size(), contours1, TargetIn);
}
