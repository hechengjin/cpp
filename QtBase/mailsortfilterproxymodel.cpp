#include "mailsortfilterproxymodel.h"

Q_GLOBAL_STATIC(QMailSortFilterProxyModel, mailSortFilterProxyModel)
QMailSortFilterProxyModel *QMailSortFilterProxyModel::instance()
{
    return mailSortFilterProxyModel;
}


QMailSortFilterProxyModel::QMailSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

QMailSortFilterProxyModel::~QMailSortFilterProxyModel()
{

}

bool QMailSortFilterProxyModel::filterAcceptsRow(int sourceRow,
    const QModelIndex &sourceParent) const
{
    QModelIndex indexItemType = sourceModel()->index(sourceRow, MLMCE_ItemType, sourceParent);
    QModelIndex indexFolderId = sourceModel()->index(sourceRow, MLMCE_Folder, sourceParent);
    int itemType = sourceModel()->data(indexItemType).toInt();
    if (!m_queryConditions.query)
    {
        return true;
    }
    if (MLIT_GROUP == itemType)
    {
        return true;
    }
    if (MLIT_CONVERSATION == itemType)
    {
        return true;
    }
    return (sourceModel()->data(indexFolderId).toUInt() == m_queryConditions.folderId);
}

bool QMailSortFilterProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    if (!source_left.isValid() || !source_right.isValid())
        return false;

    //if ((source_left.column() == MLMC_Size) && (source_right.column() == MLMC_Size))
    //{
    //    // 这里我们所取得数据是用户源数据
    //    QVariant leftData = sourceModel()->data(source_left, UIROLE_ReadableSize);
    //    QVariant rightData = sourceModel()->data(source_right, UIROLE_ReadableSize);

    //    if (leftData.canConvert<qint64>() && rightData.canConvert<qint64>())
    //    {
    //        return leftData.toLongLong() < rightData.toLongLong();
    //    }
    //}
    switch (m_queryConditions.curSortColumn)
    {
        case MLMCE_Size:
        {
            QVariant leftData = sourceModel()->data(source_left, UIROLE_ReadableSize);
            QVariant rightData = sourceModel()->data(source_right, UIROLE_ReadableSize);

            if (leftData.canConvert<qint64>() && rightData.canConvert<qint64>())
            {
                return leftData.toLongLong() < rightData.toLongLong();
            }
        }
    default:
        break;
    }
    return QSortFilterProxyModel::lessThan(source_left, source_right);
}

void QMailSortFilterProxyModel::invalidProxyModel(const QueryConditions & stQueryConditions)
{
    m_queryConditions = stQueryConditions;
    invalidateFilter();
}