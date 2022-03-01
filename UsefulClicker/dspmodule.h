#ifndef DSPMODULE_H
#define DSPMODULE_H

#include <QObject>
#include <QImage>

class DspModule : public QObject
{
    Q_OBJECT
public:

    DspModule();
    int computeDiscreteCorrelation(QImage& SearchIn, QImage& TargetIn, QImage& outImage);
    void computeHaudorf();
    int X, Y;

signals:
    void sigSendImage(QImage& image, int n_screen);
};

#endif // DSPMODULE_H
