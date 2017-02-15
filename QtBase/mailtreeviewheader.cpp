#include "mailtreeviewheader.h"
#include <QMouseEvent>
#include "mailtreemodel.h"

//Q_GLOBAL_STATIC(QMailTreeViewHeader, mailTreeViewHeader)
//QMailTreeViewHeader *QMailTreeViewHeader::instance()
//{
//    return mailTreeViewHeader;
//}


QMailTreeViewHeader::QMailTreeViewHeader(QWidget *parent)
: QHeaderView(Qt::Horizontal, parent)
, m_preSortColumn(MLMC_Date)
{
}

QMailTreeViewHeader::~QMailTreeViewHeader()
{

}

void QMailTreeViewHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    QHeaderView::paintSection(painter, rect, logicalIndex);
}

void QMailTreeViewHeader::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    //int y = event->pos().y();
    int column = visualIndexAt(x);
    if (m_preSortColumn != column)
    {
        QMailTreeModel::instance()->clear();
        QueryConditions stQueryConditions = QMailTreeModel::instance()->getQueryCondition();
        stQueryConditions.curSortColumn = column;
        QMailTreeModel::instance()->queryData(stQueryConditions);

        //QMailTreeModel::instance()->setSort(column, Qt::DescendingOrder);
        switch (column) {
        case MLMC_Date:
        {
            int xx;
            xx++;
            break;
        }
        case MLMC_Size:
        {
            int xx;
            xx++;
            break;
        }

        default:
            break;
        }
        m_preSortColumn = column;
        emit refreshAccountsMailList();
    }
    
    QHeaderView::mousePressEvent(event);
}