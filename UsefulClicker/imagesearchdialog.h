#ifndef IMAGESEARCHDIALOG_H
#define IMAGESEARCHDIALOG_H

#include <QDialog>
#include <opencv2/opencv.hpp>

namespace Ui {
class ImageSearchDialog;
}

class ImageSearchDialog : public QDialog
{
    Q_OBJECT

public:
    QStringList labels_text_templ;
    QRect selectedTargetRect;
    QRect selectedAreaRect;
    QImage screenshot;
    cv::Mat* areaImg2;
    cv::Mat   targetImg, areaImg;
    int mouseX, mouseY;
    explicit ImageSearchDialog(QWidget *parent = nullptr);
    ~ImageSearchDialog();

public slots:
    void slotAreaSelected(QRect rect);
    void slotTargetSelected(QRect rect);

private slots:
    void on_screenAreaButton_clicked();
    void on_pushButton_5_clicked();
    void on_screenSelector_currentIndexChanged(int index);


    void on_findButton_clicked();

    void on_testClickButton_clicked();

private:
    Ui::ImageSearchDialog *ui;
};

#endif // IMAGESEARCHDIALOG_H
