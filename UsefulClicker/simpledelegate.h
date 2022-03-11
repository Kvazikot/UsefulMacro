#ifndef SIMPLEDELEGATE
#define SIMPLEDELEGATE

#include <QWidget>
#include <QStyledItemDelegate>
#include <QComboBox>
#include <QObject>
#include <QAbstractItemDelegate>
#include "areaselectordialog.h"

class SimpleDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    SimpleDelegate(QObject* pobj = 0, QAbstractItemDelegate* _old_delegate = 0);
    QString getAttrsString() const;
    QWidget* createEditor(QWidget *parent,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index)    const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model,
                                             const QModelIndex &index)   const override;
    void setEditorData(QWidget *editor, const QModelIndex &index)     const  override;
    void updateEditorGeometry(QWidget *editor,
                                               const QStyleOptionViewItem &option,
                                               const QModelIndex& index/* index */) const override;

public slots:
    void slotSetAttrs(QMap<QString,QString> attrs);
    void restoreDelegate();
signals:
    void activated(const QModelIndex &index);
};
#endif // SIMPLEDELEGATE
