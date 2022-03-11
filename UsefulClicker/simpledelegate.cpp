#include <QObject>
#include <QTreeView>
#include <QTimer>
#include <QLineEdit>
#include <QCoreApplication>
#include "simpledelegate.h"
#include "areaselectordialog.h"

QModelIndex  new_index;
static QMap<QString, QString> attrs;
static QLineEdit* edit;
static AreaSelectorDialog* dlg;
static QAbstractItemDelegate* old_delegate;

SimpleDelegate::SimpleDelegate(QObject* pobj, QAbstractItemDelegate* _old_delegate) :
    QStyledItemDelegate(pobj)
{
   old_delegate = _old_delegate;
   AreaSelectorDialog* dlg = new AreaSelectorDialog((QWidget*)pobj);
   connect(dlg, SIGNAL(sigSetAreaRect(QMap<QString,QString>)), this, SLOT(slotSetAttrs(QMap<QString,QString>)));
   dlg->show();
}

void SimpleDelegate::restoreDelegate()
{
    QTreeView* view = (QTreeView*)old_delegate->parent();
    view->setItemDelegate(old_delegate);
}

void SimpleDelegate::slotSetAttrs(QMap<QString, QString> _attrs)
{
    for(auto k : _attrs.keys())
        attrs[k] = _attrs[k];


//    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
//    QCoreApplication::sendEvent(edit->parent()->parent(), &keyEvent);
    emit commitData(edit);

    QTimer::singleShot(100, this, SLOT(restoreDelegate()));

    qDebug() << "SimpleDelegate::slotSetAttrs " << getAttrsString();
}

QString SimpleDelegate::getAttrsString() const
{
    QString attr_str;
    for(auto k : attrs.keys())
        attr_str+=k+"="+""""+attrs[k]+"""" + " ";
    return attr_str;
}


QWidget*  SimpleDelegate::createEditor(QWidget *parent,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index) const
{

    QStringList values;
    values << "Enabled" << "Disabled";
    QLineEdit* w = new QLineEdit(parent);
    edit = w;


    //dlg->selectTargetImage();
    //QRect curernt_geometry = dlg->geometry();
//    curernt_geometry.setWidth(curernt_geometry.width()/2);
//    curernt_geometry.setHeight(curernt_geometry.height()/2);
//    dlg->setGeometry(curernt_geometry);
//    dlg->prevMouseCoords = curernt_geometry.center();
//    dlg->repaint();

    //connect(dlg, SIGNAL(sigSetAreaRect(QMap<QString, QString>)), main_window, SLOT(slotSetAttrs(QMap<QString, QString>)));


    return w;

}

void  SimpleDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                         const QModelIndex &index) const
{
    if(index.column()==1)
    {
        //QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
        QString value = getAttrsString();
        //new_index = model->index(index.row(), 2);
        model->setData(index, value, Qt::EditRole);
        qDebug() << "SimpleDelegate::setModelData " << value;
    }
}

void  SimpleDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column()==1)
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        value+=getAttrsString();
        //QLineEdit* editor2 = qobject_cast<QLineEdit*>(editor);
        //editor2->setText(value);
    }
}

void SimpleDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex& index/* index */) const
{
    //editor->setGeometry(QRect(0,0,1,1));
    edit = (QLineEdit*)editor;
    qDebug() << "updateEditorGeometry " << editor->rect();
}
