#include "mailsortfilterproxymodel.h"
#include "dataDefine.h"

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

bool QMailSortFilterProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    if (!source_left.isValid() || !source_right.isValid())
        return false;

    if ((source_left.column() == MLMC_Size) && (source_right.column() == MLMC_Size))
    {
        // ����������ȡ���������û�Դ����
        QVariant leftData = sourceModel()->data(source_left, UIROLE_ReadableSize);
        QVariant rightData = sourceModel()->data(source_right, UIROLE_ReadableSize);

        if (leftData.canConvert<qint64>() && rightData.canConvert<qint64>())
        {
            return leftData.toLongLong() < rightData.toLongLong();
        }
    }

    return QSortFilterProxyModel::lessThan(source_left, source_right);
}