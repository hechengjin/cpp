#include "mailtreeview.h"
#include "mailtreemodel.h"
#include "mailsortfilterproxymodel.h"
#include "dataDefine.h"
#include "mailtreeviewheader.h"
#include "mailitemdelegate.h"
#include <QMenu>
#include <QToolTip>
#include <QDebug>

class MailTreeItem;

QMailTreeView::QMailTreeView(QWidget *parent)
    : QTreeView(parent)
    , m_pMailTreeViewHeader(NULL)
{
    qRegisterMetaType<MailListSelectItemData>("MailListSelectItemData");
    qRegisterMetaType<MailListSelectData>("MailListSelectData");
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
    sortByColumn(MLMCE_Date, Qt::DescendingOrder);
    m_pMailTreeViewHeader = new QMailTreeViewHeader(this);
    setHeader(m_pMailTreeViewHeader);
    connect(m_pMailTreeViewHeader, SIGNAL(refreshAccountsMailList()), this, SLOT(onRefreshAccountMails()));
    
    setItemDelegate(new QMailItemDelegate(this));
    for (int column = 0; column < QMailTreeModel::instance()->columnCount(); ++column)
        resizeColumnToContents(column);
    setColumnHidden(MLMCE_Priority, true);

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
    connect(this, &QAbstractItemView::clicked, this, &QMailTreeView::slotClicked);
}

void QMailTreeView::slotCustomContextMenu(const QPoint &pos)
{
    QMenu *menu = new QMenu;
    menu->addAction(tr("delete"), this, SLOT(slotDeleteMailClicked()));
    menu->exec(QCursor::pos());
    menu->deleteLater();
}

void QMailTreeView::onRefreshAccountMails()
{
   expandAll();
}

void QMailTreeView::slotEntered(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    int nColumn = index.column();
    if ((nColumn == MLMCE_Size))
        QToolTip::showText(QCursor::pos(), index.data().toString());
}

void QMailTreeView::slotClicked(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    MailListSelectData stMailListSelectData;
    //QModelIndexList indexs = this->selectionModel()->selectedIndexes(); //这里选中一行返回多个数据，代表的是多列
    QModelIndexList selectedList = this->selectionModel()->selectedRows(); //这样就是一行了
    foreach(const QModelIndex &index, selectedList) {
        MailListSelectItemData stMailListSelectItemData;
        //QString text = QString("(%1,%2)").arg(index.row()).arg(index.column());
        //qDebug() << text;
        MailTreeItem *item = QMailTreeModel::instance()->getItem(QMailSortFilterProxyModel::instance()->mapToSource(index));
        stMailListSelectItemData.itemType = item->stItemData.itemType;
        stMailListSelectItemData.id = item->stItemData.id;
        stMailListSelectData.vecselectItemDatas.push_back(stMailListSelectItemData);
    }
    emit signalMailSelectionChanged(stMailListSelectData);

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
    //QListIterator<QModelIndex> i(selectedList);
    //while (i.hasNext())
    //{
    //    QModelIndex modelIndex = i.next();
    //    QModelIndex modelIndexParent = modelIndex.parent();
    //    //QString text = QString("(%1,%2)").arg(modelIndex.row()).arg(modelIndex.column());
    //    //qDebug() << text;
    //    //一次只删除1个，没法连着删除，因为多选不是连着选的
    //    if (model->removeRow(modelIndex.row(), modelIndexParent))
    //    {
    //        deletedSuccess = true;
    //    }
    //}
    QVector<MailListItemData> vecSelItems;
    QListIterator<QModelIndex> i(selectedList);
    while (i.hasNext())
    {
        QModelIndex modelIndex = i.next();
        MailListItemData stItemData;
        MailTreeItem *item = QMailTreeModel::instance()->getItem(QMailSortFilterProxyModel::instance()->mapToSource(modelIndex));
        stItemData.itemType = item->stItemData.itemType;
        if (stItemData.itemType == MLIT_MAIL)
        {
            stItemData.id = item->stItemData.id;
            vecSelItems.push_back(stItemData);
        }
    }
    for (int i = 0; i < vecSelItems.length(); i++)
    {
        if (QMailTreeModel::instance()->deleteRecord(vecSelItems.at(i)))
            deletedSuccess = true;
    }
    if (deletedSuccess)
    {
        QMailTreeModel::instance()->resetModel();
        expandAll();
    }
}

void QMailTreeView::setDisplayMode(int displayMode)
{
    if (m_pMailTreeViewHeader)
    {
        m_pMailTreeViewHeader->setDisplayMode(displayMode);
    }
}

void QMailTreeView::saveStatusInfo()
{
    m_itemSelection = selectionModel()->selection();
    QString text;
    foreach(QModelIndex index, m_itemSelection.indexes())
    {
        text = QString("(%1,%2)").arg(index.row()).arg(index.column());
        //MailListItemData stMailListItemData;
        //stMailListItemData.id = 2;
        //QMailTreeModel::instance()->setData(index, stMailListItemData);//QMailSortFilterProxyModel::instance()
        //qDebug() << text;
    }
    qDebug() << text;
    QModelIndexList selectedList = this->selectionModel()->selectedRows();
    QListIterator<QModelIndex> i(selectedList);
    while (i.hasNext())
    {
        QModelIndex modelIndex = i.next();
        MailTreeItem *item = QMailTreeModel::instance()->getItem(QMailSortFilterProxyModel::instance()->mapToSource(modelIndex));
        m_selMailListItemData.itemType = item->stItemData.itemType;
        m_selMailListItemData.id = item->stItemData.id;
    }
    qDebug() << m_selMailListItemData.itemType << " " << m_selMailListItemData.id;
    
}

void QMailTreeView::recoveryStatusInfo()
{
    foreach(QModelIndex index, m_itemSelection.indexes())
    {
        QString text = QString("(%1,%2)")
            .arg(index.row() + 1).arg(index.column() + 1);
        //QMailSortFilterProxyModel::instance()->setData(index, text);
        //qDebug() << text;
    }
    //int topLeftRow = indexList[0].row();
    //int bottomRightRow = indexList[indexList.count() - 1].row();
    //QModelIndex topLeft = QMailSortFilterProxyModel::instance()->index(topLeftRow, 0, QModelIndex());
    //QModelIndex bottomRight = QMailSortFilterProxyModel::instance()->index(bottomRightRow, 0, QModelIndex());
    qDebug() << "recovery:" << m_selMailListItemData.itemType << " " << m_selMailListItemData.id;
    QModelIndex rowPosIndex = QMailTreeModel::instance()->itemToIndex(m_selMailListItemData);
    QString sorceInfo = QString("(%1,%2)").arg(rowPosIndex.row()).arg(rowPosIndex.column());
    qDebug() << "source:" << sorceInfo;
    QModelIndex proxyIndex = QMailSortFilterProxyModel::instance()->mapFromSource(rowPosIndex);
    QString proxyInfo = QString("(%1,%2)").arg(proxyIndex.row()).arg(proxyIndex.column());
    qDebug() << "proxy:" << proxyInfo;
    m_itemSelection.select(proxyIndex, proxyIndex);
    //selectionModel()->select(m_itemSelection, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);

    setCurrentIndex(proxyIndex);
}