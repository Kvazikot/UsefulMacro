#ifndef COMBOEDIT_H
#define COMBOEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>

class ComboEdit : public QLineEdit
{
    Q_OBJECT
public:
    QString sequence;
    QHBoxLayout* hbox;
    int hbox_width;

    explicit ComboEdit(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent* event);
    void mouseMoveEvent(QMouseEvent *ev) override;
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void setMouseState(int button);
    void setKeyboardState(int state);

signals:
    void sigSetSequence(QString sequence);

public slots:
    void slotCrossClick();
    void slotKeyboardClick();
    void slotSetSequence(QString sequence);
    void slotAccepted();
    void slotFocusChanged(QWidget* old, QWidget* now);

//    void paintEvent(QPaintEvent *) override;

};


#endif // COMBOEDIT_H
