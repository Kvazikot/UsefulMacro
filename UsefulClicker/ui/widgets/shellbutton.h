#ifndef SHELLBUTTON_H
#define SHELLBUTTON_H

#include <QLabel>
#include <QMouseEvent>

class ShellButton : public QLabel
{
    Q_OBJECT
public:
    explicit ShellButton(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *ev) override;
signals:
    void click(QString button);
    void clicked();
};


#endif // CROSSBUTTON_H
