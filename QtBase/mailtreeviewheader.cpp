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
, m_preSortColumn(MLMCE_Date)
, m_mailListDisplayMode(MLDM_MAIL)
{
}

QMailTreeViewHeader::~QMailTreeViewHeader()
{

}

void QMailTreeViewHeader::setDisplayMode(int displayMode)
{
    m_mailListDisplayMode = displayMode;
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
    if (column == MLMCE_Fold)  //禁止此列排序
    {
        return;
    }
    if (m_preSortColumn != column && m_mailListDisplayMode != MLDM_MAIL)
    {
        QMailTreeModel::instance()->clear();
        QueryConditions stQueryConditions = QMailTreeModel::instance()->getQueryCondition();
        stQueryConditions.curSortColumn = column;
        QMailTreeModel::instance()->queryData(stQueryConditions);
        //QMailTreeModel::instance()->setSort(column, Qt::DescendingOrder);
        switch (column) {
        case MLMCE_Date:
        {
            int xx;
            xx++;
            break;
        }
        case MLMCE_Size:
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