#ifndef SIMPLEDELEGATE
#define SIMPLEDELEGATE

#include <QWidget>
#include <QStyledItemDelegate>
#include <QComboBox>
#include <QObject>

class SimpleDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    SimpleDelegate(QObject* pobj = 0);
    QWidget* createEditor(QWidget *parent,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index);

    void setModelData(QWidget *editor, QAbstractItemModel *model,
                                             const QModelIndex &index);
    void setEditorData(QWidget *editor, const QModelIndex &index);
};
#endif // SIMPLEDELEGATE
