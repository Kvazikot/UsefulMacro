#include <QObject>
#include <QTreeView>
#include <QTimer>
#include <QLineEdit>
#include <QCoreApplication>
#include "model/simpledelegate.h"
#include "ui/areaselectordialog.h"
#include "ui/screenbuttonsdetector.h"
#include "ui/coordselector.h"
#include "ui/shelldialog.h"

QModelIndex  new_index;

static QLineEdit* edit;
static QAbstractItemDelegate* old_delegate;

SimpleDelegate::SimpleDelegate(QObject* pobj, QAbstractItemDelegate* _old_delegate, DialogType dialog) :
    QStyledItemDelegate(pobj)
{
   old_delegate = _old_delegate;
   switch( dialog )
   {
        case AREA_SELECTOR:
        {
            AreaSelectorDialog* dlg = new AreaSelectorDialog((QWidget*)pobj);
            connect(dlg, SIGNAL(sigSetAreaRect(QMap<QString,QString>)), this, SLOT(slotSetAttrs(QMap<QString,QString>)));
            dlg->show();
        } break;
        case SCREEN_BUTTONS_DETECTOR:
        {
           ScreenButtonsDetector* dlg2 = new ScreenButtonsDetector((QWidget*)pobj);
           connect(dlg2, SIGNAL(sigSetAttrs(QMap<QString,QString>)), this, SLOT(slotSetAttrs(QMap<QString,QString>)));
           dlg2->show();
        } break;
        case COORDINATES_SELECTOR:
        {
            CoordSelector* dlg2 = new CoordSelector((QWidget*)pobj);
            connect(dlg2, SIGNAL(sigSetAttrs(QMap<QString,QString>)), this, SLOT(slotSetAttrs(QMap<QString,QString>)));
            dlg2->show();
        } break;
        case SHELL_COMMAND_DIALOG:
        {
            ShellDialog* dlg3 = new ShellDialog((QWidget*)pobj);
            connect(dlg3, SIGNAL(sigSetAttrs(QMap<QString,QString>)), this, SLOT(editCurrentItem(QMap<QString,QString>)));
            dlg3->show();

        } break;
   }
}

void SimpleDelegate::editCurrentItem(QMap<QString,QString> _attrs)
{
    QTreeView* view = (QTreeView*)old_delegate->parent();
    QModelIndex index = view->currentIndex();
    view->edit(index);
    for(auto k : _attrs.keys())
        attrs[k] = _attrs[k];
    //edit->setText(getAttrsString());
    emit commitData(edit);

    QTimer::singleShot(500, this, SLOT(restoreDelegate()));

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

    //edit->setText(getAttrsString());
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
    //values << "Enabled" << "Disabled" << QString::number(index.column()) << QString(option.text);
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
    //qDebug() << "updateEditorGeometry " << editor->rect();
}
