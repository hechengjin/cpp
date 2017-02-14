#include "mailitemdelegate.h"
#include <QApplication>
#include "dataDefine.h"
QMailItemDelegate::QMailItemDelegate(QObject *parent)
: QStyledItemDelegate(parent)
{

}

QMailItemDelegate::~QMailItemDelegate()
{

}


void QMailItemDelegate::paint(QPainter *painter,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);
    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

    // 进行大小转换
    if (index.column() == MLMC_Size)
    {
        qint64 bytes = index.data().toLongLong();
        viewOption.text = bytesToGBMBKB(bytes);
        QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &viewOption, painter, viewOption.widget);
    }
    else
    {
        QStyledItemDelegate::paint(painter, viewOption, index);
    }
}