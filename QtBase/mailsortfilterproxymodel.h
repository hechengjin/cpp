#ifndef MAILSORTFILTERPROXYMODEL_H
#define MAILSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "dataDefine.h"


class QMailSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    QMailSortFilterProxyModel(QObject *parent = NULL);
    ~QMailSortFilterProxyModel();
    static QMailSortFilterProxyModel* instance();

    void setQueryCondition(const QueryConditions & stQueryConditions);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    virtual bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;
private:
    QueryConditions m_stQueryConditions;
};

#endif // MAILSORTFILTERPROXYMODEL_H
