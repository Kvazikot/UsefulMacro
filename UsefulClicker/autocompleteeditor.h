#ifndef AUTOCOMPLETEEDITOR_H
#define AUTOCOMPLETEEDITOR_H

#include <QLabel>
#include <QVector>
#include <QHBoxLayout>
#include <QWidget>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QComboBox>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QLineEdit>
#include <QTimerEvent>
#include <QKeyEvent>


class KeyboardButton : public QLabel
{
    Q_OBJECT
public:
    QImage icon_enabled, icon_disabled;
    explicit KeyboardButton(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void timerEvent(QTimerEvent* event) override;
    void setDisable();
    bool mouseOverFlag;
    bool state;
    void setIcon(QString filename, bool invert_pixels=true, bool init_state=false);
    virtual void paintEvent(QPaintEvent *) override;
signals:
    void clicked();
    void sendAttrs(QMap<QString,QString> attrs);
    void accept();
    void updateSequence();

};

class MouseButton : public KeyboardButton
{
    Q_OBJECT
public:
    Qt::MouseButton button;
    explicit MouseButton(QWidget *parent = nullptr);
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *ev) override;
signals:
    void click(QString button);
};

class AreaButton : public KeyboardButton
{
    Q_OBJECT
public:
    explicit AreaButton(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *ev) override;
public slots:
    void areaSelected(QRect rect, QImage& rect_image);

signals:
    void click(QString button);
};

class CrossButton : public KeyboardButton
{
    Q_OBJECT
public:
    explicit CrossButton(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *ev) override;
signals:
    void click(QString button);
};

class ComboEdit : public QLineEdit
{
    Q_OBJECT
public:
    QString sequence;
    KeyboardButton* keyboard_but;
    CrossButton* cross_but;
    MouseButton* mouse_but;
    AreaButton* area_but;
    QHBoxLayout* hbox;
    int hbox_width;

    explicit ComboEdit(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent* event);
    void mouseMoveEvent(QMouseEvent *ev) override;
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *ev) override;

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

class AutocompleteEditor : public QComboBox
{
    Q_OBJECT
public:
    QVector<QString> completion_list;

    explicit AutocompleteEditor(QWidget *parent = nullptr);
    void setValue(QString value);
    void keyPressEvent(QKeyEvent* event);

    //void paintEvent(QPaintEvent* event);
    ~AutocompleteEditor();
public slots:
    void updateSequence(QString sequence);

};

#endif // AUTOCOMPLETEEDITOR_H
