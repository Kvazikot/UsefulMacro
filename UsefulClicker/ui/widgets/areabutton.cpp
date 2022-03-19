#include <QTreeView>
#include <QPainter>
#include "model/simpledelegate.h"
#include "ui/widgets/areabutton.h"

//---------------------------------------------------------------------------------

AreaButton::AreaButton(QWidget *parent)
    : KeyboardButton(parent)
{
    setContextMenuPolicy(Qt::PreventContextMenu);
    setIcon(":/images/area_icon.png", true, true);
    repaint();
}

void AreaButton::areaSelected(QRect rect, QImage& rect_image)
{
    QPainter painter(&rect_image);
    painter.drawImage(geometry(), rect_image);
    QMap<QString,QString> attrs;
    QString v = QString("QRect(%1,%2,%3,%4)").arg(rect.left())
                                             .arg(rect.top())
                                             .arg(rect.width())
                                             .arg(rect.height());
    attrs["areaRect"] = v;
    emit sendAttrs(attrs);


}

void AreaButton::mousePressEvent(QMouseEvent *ev)
{
    if ( ev->button() == Qt::MouseButton::LeftButton )
    {
        QTreeView*  view = (QTreeView*)this->parent()->parent()->parent();
        SimpleDelegate* delegate = new SimpleDelegate(view, view->itemDelegate());
        view->setItemDelegate(delegate);
        connect(delegate, SIGNAL(activated(const QModelIndex&)), view, SLOT(update(const QModelIndex&)) );
    }

}
