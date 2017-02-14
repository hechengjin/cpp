#include "mailtreeview.h"
#include "mailtreemodel.h"
#include "mailsortfilterproxymodel.h"
#include "dataDefine.h"
#include "mailtreeviewheader.h"
#include "mailitemdelegate.h"
#include <QMenu>
#include <QToolTip>
QMailTreeView::QMailTreeView(QWidget *parent)
    : QTreeView(parent)
{
    init();
    signalSlotConnection();
}

QMailTreeView::~QMailTreeView()
{

}

void QMailTreeView::init()
{

    QMailSortFilterProxyModel::instance()->setSourceModel(QMailTreeModel::instance());
    setModel(QMailSortFilterProxyModel::instance());
    setSortingEnabled(true);
    sortByColumn(MLMC_Date, Qt::DescendingOrder);

    setHeader(new QMailTreeViewHeader(this));
    setItemDelegate(new QMailItemDelegate(this));
    for (int column = 0; column < QMailTreeModel::instance()->columnCount(); ++column)
        resizeColumnToContents(column);
    setColumnHidden(MLMC_Priority, true);

    //�Ҽ��˵�����
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(slotCustomContextMenu(const QPoint &)));
    //֧�ֶ�ѡ ֧��shift, ctrl, �����ȷ�ʽ
    setSelectionMode(ExtendedSelection);
    connect(this, SIGNAL(entered(const QModelIndex &)), this, SLOT(slotEntered(const QModelIndex &)));
    //������ʾToolTip
    setMouseTracking(true);
    expandAll();
}


void QMailTreeView::signalSlotConnection()
{
}

void QMailTreeView::slotCustomContextMenu(const QPoint &pos)
{
    QMenu *menu = new QMenu;
    menu->addAction(tr("delete"), this, SLOT(slotDeleteMailClicked()));
    menu->exec(QCursor::pos());
    menu->deleteLater();
}

void QMailTreeView::slotEntered(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    int nColumn = index.column();
    if ((nColumn == MLMC_Size))
        QToolTip::showText(QCursor::pos(), index.data().toString());
}

void QMailTreeView::slotDeleteMailClicked()
{
    QAbstractItemModel *model = this->model();
    bool deletedSuccess = false;
    //��ѡ
    //QModelIndex index = this->selectionModel()->currentIndex();
    //if (model->removeRow(index.row(), index.parent()))
    //    deletedSuccess = true;
    //��ѡ ��ȡtreeview ѡ��Ľڵ㣨���Է��� QModelIndexList  ����˳������ѡ���˳�������еģ�
    QModelIndexList selectedList = this->selectionModel()->selectedRows();
    QListIterator<QModelIndex> i(selectedList);
    while (i.hasNext())
    {
        QModelIndex modelIndex = i.next();
        //һ��ֻɾ��1����û������ɾ������Ϊ��ѡ��������ѡ��
        if (model->removeRow(modelIndex.row(), modelIndex.parent()))
            deletedSuccess = true;
    }
    if (deletedSuccess)
    {
        int xx;
    }
}
