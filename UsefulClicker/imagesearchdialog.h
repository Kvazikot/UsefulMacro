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
    explicit ImageSearchDialog(QWidget *parent = nullptr);
    ~ImageSearchDialog();

private slots:
    void on_screenAreaButton_clicked();

private:
    Ui::ImageSearchDialog *ui;
};

#endif // IMAGESEARCHDIALOG_H
