#include <QObject>
#include "simpledelegate.h"

SimpleDelegate::SimpleDelegate(QObject* pobj) : QStyledItemDelegate(pobj)
{
}

QWidget*  SimpleDelegate::createEditor(QWidget *parent,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index)
{

    QStringList values;
    values << "Enabled" << "Disabled";

    QComboBox* comboBox = new QComboBox(parent);
    comboBox->addItems(values);
    return comboBox;

}

void  SimpleDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                         const QModelIndex &index)
{
    QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
    QString value = comboBox->currentText();
    model->setData(index, value, Qt::EditRole);
}

void  SimpleDelegate::setEditorData(QWidget *editor, const QModelIndex &index)
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
    comboBox->setCurrentIndex(comboBox->findText(value));
}
