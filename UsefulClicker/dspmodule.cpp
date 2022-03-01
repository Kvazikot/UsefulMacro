#include <QObject>
#include <cmath>
#include <QDebug>
#include <QPainter>
#include <vector>
#include <xmmintrin.h>
#include "dspmodule.h"
#include <malloc.h>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
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
    qDebug() << str << "}\n" << "computed!";
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
    findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );
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
        //qDebug() << i << ". npts = " << " " << contours.size();
    }
    QString name = "Contours" + QString::number(rng.uniform(0, 25611));
    imshow( name.toStdString(), drawing );
}


void DspModule::computeHaudorf()
{
    cv::Mat3b SearchIn = Mat3b::zeros(80,80);
    cv::Mat3b TargetIn = Mat3b::zeros(80,80);

    SearchIn = imread("C:\\Images to Search On Screen\\areaImg.bmp");
    TargetIn = imread("C:\\Images to Search On Screen\\targetImg.bmp");

    vector<vector<Point> > contours1 = getCounters(TargetIn, false);
    vector<vector<Point> > contours2 = getCounters(SearchIn, false);
    vector<vector<Point> > contours3;
    vector<double> areas1;
    vector<double> areas2;
    for(int i=0; i < contours1.size(); i++)
        areas1.push_back( cv::contourArea(contours1[i]) );
    for(int i=0; i < contours2.size(); i++)
        areas2.push_back( cv::contourArea(contours2[i]) );

    for(int i=0; i < contours1.size(); i++)
        for(int j=0; j < contours2.size(); j++)
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

int DspModule::computeDiscreteCorrelation(QImage& SearchIn, QImage& TargetIn, QImage& outImage)
{
    unsigned int i;

    __m128 X, Y, Z;

    print_vector("a", a, 128);
    print_vector("b", b, 128);

    float* aa = a;
    float* bb = b;
    float* rrv = rv;

    // произведение 2 массивов через sse
    for( i = 0; i < 2; i++)
    {
        X = _mm_load_ps(aa);
        Y = _mm_load_ps(bb);
        Z = _mm_mul_ps(X, Y);
        _mm_store_ps(rrv,Z);
        aa+=4; // 4 floats per cycle
        bb+=4; // 4 floats per cycle
        rrv+=4; // 4 floats per cycle
    }
    print_vector("r", rv, 128);


    // scan images
    QImage SearchInSk = SearchIn;//SearchIn.scaled(SearchIn.width()/6, SearchIn.height()/6);
    QImage TargetInSk = TargetIn;//TargetIn.scaled(TargetIn.width()/6, TargetIn.height()/6);

    // создать из TargetIn изображение по размерам равное SearchIn
    // но с размерам пиксела таким жем т.е. добавиь как бы нулевые пикселы

    SearchInSk = SearchIn.scaled(SearchIn.width()/2, SearchIn.height()/2,  Qt::KeepAspectRatio, Qt::FastTransformation);
    TargetInSk = TargetIn.scaled(TargetIn.width()/2, TargetIn.height()/2,  Qt::KeepAspectRatio, Qt::FastTransformation);

    //if(TargetInSk.size().width() < 16)
    //    TargetInSk = TargetIn.scaledToWidth(16);
    SearchInSk.save("1.bmp");
    TargetInSk.save("2.bmp");
    //return 1;


    qDebug() << "SearchInSk w=" << SearchInSk.width() << " h=" << SearchInSk.height();
    qDebug() << "TargetInSk w=" << TargetInSk.width() << " h=" << TargetInSk.height();
  //  qDebug() << "TargetIn w=" << TargetIn.width() << " h=" << TargetIn.height();


    //emit sigSendImage(TargetInSk, 1);
    //emit sigSendImage(SearchInSk, 0);

    //return 1;
    int bytesPerLine1 = SearchIn.bytesPerLine();
    int bytesPerLine2 = TargetIn.bytesPerLine();
    int h = TargetIn.height();
    int w = TargetIn.width();
    outImage = SearchIn;
    outImage.fill(255);
    for(int j = h; j < SearchIn.height() - h; j++)
    {
        aa = (float*)SearchIn.scanLine(j);
        bb = (float*)TargetIn.scanLine(j%h);
        rrv = (float*)outImage.scanLine(j);
        for(int i = w; i < SearchIn.width() - w; i++)
        {
            double correlation = 0;
            double max = 0.11;
            for(int jj = 0; jj < TargetIn.height(); jj++)
            {
                for(int ii = 0; ii < TargetIn.width(); ii++)
                {
                    QRgb target_pixel = TargetIn.pixel(ii, jj);
                    QRgb search_pixel = SearchIn.pixel(i, j);
                    //correlation+= target_pixel * search_pixel; /// (w*h);
                    float val = qAbs((qRed(target_pixel) - qRed(search_pixel)));
                    if(val = 0) val = 0.9;
                    correlation+=255./val;
                    val = qAbs((qGreen(target_pixel) - qGreen(search_pixel)));
                    if(val = 0) val = 0.9;
                    correlation+=255./val;
                    val = qAbs((qBlue(target_pixel) - qBlue(search_pixel)));
                    if(val = 0) val = 0.9;
                    correlation+=255./val;
                }
            }
            correlation = correlation / (3 * h * w );
            if( correlation > 255) correlation = 255;
            if( correlation < 0) correlation = 0;
            max = qMax(correlation, max);
            //if( correlation > 0 )
            //    qDebug() << "ixj " << i << " " << j;
            outImage.setPixel(i, j, qRgb(correlation,correlation,correlation));

            /*
            X = _mm_load_ps(aa);
            Y = _mm_load_ps(bb);
            Z = _mm_mul_ps(X, Y);
            _mm_store_ps(rrv,Z);
            aa+=4; // 4 floats per cycle
            bb+=4; // 4 floats per cycle
            rrv+=4; // 4 floats per cycle
            */
        }
    }
    outImage.save("correlation.bmp");
    emit sigSendImage(outImage, 0);
    return 1;
}
