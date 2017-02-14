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

    //右键菜单设置
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(slotCustomContextMenu(const QPoint &)));
    //支持多选 支持shift, ctrl, 鼠标框框等方式
    setSelectionMode(ExtendedSelection);
    connect(this, SIGNAL(entered(const QModelIndex &)), this, SLOT(slotEntered(const QModelIndex &)));
    //用于显示ToolTip
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
    //单选
    //QModelIndex index = this->selectionModel()->currentIndex();
    //if (model->removeRow(index.row(), index.parent()))
    //    deletedSuccess = true;
    //多选 获取treeview 选择的节点（调试发现 QModelIndexList  排列顺序是以选择的顺序来排列的）
    QModelIndexList selectedList = this->selectionModel()->selectedRows();
    QListIterator<QModelIndex> i(selectedList);
    while (i.hasNext())
    {
        QModelIndex modelIndex = i.next();
        //一次只删除1个，没法连着删除，因为多选不是连着选的
        if (model->removeRow(modelIndex.row(), modelIndex.parent()))
            deletedSuccess = true;
    }
    if (deletedSuccess)
    {
        int xx;
    }
}
