#include "mailitemdelegate.h"
#include <QApplication>
#include "dataDefine.h"
#include "mailtreemodel.h"
#include "mailsortfilterproxymodel.h"
#include <QPainter>
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
    MailTreeItem *item = QMailTreeModel::instance()->getItem(QMailSortFilterProxyModel::instance()->mapToSource(index));
    if (item->stItemData.itemType == MLIT_GROUP)
    {
        painter->fillRect(option.rect, QBrush(QColor("#fcfcfc")));
        paintGrid(painter, option.rect);

        if (index.column() == MLMCE_Fold) {
            QStyledItemDelegate::paint(painter, viewOption, index);
            return;
        }
        else if (index.column() == MLMCE_Subject)
        {
            viewOption.font.setBold(false);
            viewOption.rect.setLeft(20);
            painter->setFont(viewOption.font);
            painter->setPen(QPen(QColor("#333333")));
            painter->drawText(viewOption.rect,
                Qt::AlignVCenter | Qt::AlignLeft,
                index.data().toString());
        }
        
    }
    else
    {
        initStyleOption(&viewOption, index);
        if (option.state.testFlag(QStyle::State_HasFocus))
            viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

        // 进行大小转换
        if (index.column() == MLMCE_Size)
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
}

void QMailItemDelegate::paintGrid(QPainter *painter, const QRect &rect) const
{
    painter->setPen(QColor("#eeeeee"));
    painter->drawLine(QLine(QPoint(rect.x(),
        rect.y() + rect.height()),
        rect.bottomRight()));
}