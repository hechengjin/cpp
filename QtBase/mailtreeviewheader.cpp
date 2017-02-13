#include "mailtreeviewheader.h"
#include <QMouseEvent>
QMailTreeViewHeader::QMailTreeViewHeader(QWidget *parent)
: QHeaderView(Qt::Horizontal, parent)
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
    QHeaderView::mousePressEvent(event);
}