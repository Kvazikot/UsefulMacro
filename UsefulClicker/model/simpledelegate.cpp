#include <QObject>
#include <QTreeView>
#include <QTimer>
#include <QLineEdit>
#include <QCoreApplication>
#include "model/simpledelegate.h"
#include "ui/areaselectordialog.h"

QModelIndex  new_index;

static QLineEdit* edit;
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
    values << "Enabled" << "Disabled" << QString::number(index.column()) << QString(option.text);
    QLineEdit* w = new QLineEdit(parent);
    edit = w;
    return w;

}

void  SimpleDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                         const QModelIndex &index) const
{
    if(index.column()==1)
    {
        QString value = getAttrsString();
        editor->geometry();
        model->setData(index, value, Qt::EditRole);
        qDebug() << "SimpleDelegate::setModelData " << value;
    }
}

