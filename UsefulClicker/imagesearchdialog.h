#ifndef IMAGESEARCHDIALOG_H
#define IMAGESEARCHDIALOG_H

#include <QDialog>

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
    explicit ImageSearchDialog(QWidget *parent = nullptr);
    ~ImageSearchDialog();

public slots:
    void slotAreaSelected(QRect rect);
    void slotTargetSelected(QRect rect);

private slots:
    void on_screenAreaButton_clicked();
    void on_pushButton_5_clicked();
    void on_screenSelector_currentIndexChanged(int index);


private:
    Ui::ImageSearchDialog *ui;
};

#endif // IMAGESEARCHDIALOG_H
