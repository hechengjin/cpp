/****************************************************************************
**
** Copyright (C) 2017 金山办公 All Rights Reserved.
** Contact: http://www.wps.cn/product/wpsmail/
**
****************************************************************************/

#ifndef QMAILTREEMODEL_H
#define QMAILTREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "MemoryDBManager.h"
#include "mailtreeitem.h"
class CMemoryDBManager;


//! [0]
class QMailTreeModel : public QAbstractItemModel
{
    Q_OBJECT
    friend class QMailTreeView;
    friend class QMailItemDelegate;
public:
    QMailTreeModel(QObject *parent = 0);
    //TreeMailModel(const QStringList &headers, const QString &data,
    //          QObject *parent = 0);
    ~QMailTreeModel();

public:
    static QMailTreeModel* instance();
    QueryConditions getQueryCondition();
    void queryData(const QueryConditions& queryInfo);
    void queryData();
    void clear();
    bool deleteRecord(const MailListItemData & stItemData);
    bool updateRecord(const MailListItemData & stItemData);

private:
    void initRootItem();
    void resetModel();
    bool clearRecords();

    bool stepQueryData();
    void queryInMemoryResultSet(); //内存查询
    bool whetherNeedToDisplay(const MailHeaderInfo & stMailHeaderInfo); //判断是否需要显示，即是否是要查询的记录
    void addToQuerySet(const MailHeaderInfo & stMailHeaderInfo); //添加到查询结果集
    void generateQueryResultSet(); //生成查询结果集
    void regenerateMailListModelData(); // 生成Model数据
    void updateProxyModelData();//更新排序用视图数据
    //会话中的邮件是否符合查询条件
    bool converMailLegal(uint64_t mailId);
    QString generationGroupName(const MailHeaderInfo & stMailHeaderInfo);
    QString querySizeGroupName(uint32_t messageSize);
public:

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
//! [1]

//! [2]
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const MailListItemData &stMailListItemData);
    //bool setData(const QModelIndex &index, const QVariant &value,
    //             int role = Qt::EditRole) Q_DECL_OVERRIDE;
    //bool setHeaderData(int section, Qt::Orientation orientation,
    //                   const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

    //bool insertColumns(int position, int columns,
    //                   const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    //bool removeColumns(int position, int columns,
    //                   const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool insertRows(int position, int rows,
        const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeRows(int position, int rows,
        const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;



private:
    //void setupModelData(const QStringList &lines, TreeMailItem *parent);
    MailTreeItem *getItem(const QModelIndex &index) const;
    MailTreeItem *getParentItem(const MailListItemData & stMailListItemData);
    MailTreeItem *m_rootItem;
    QueryConditions  m_queryConditions;

    //QMutex  m_modelMutex;

    //查询结果集合 只记录合法的mailId,否则跨邮件夹或账号排序不能全局排
    QSet<QuerySummaryInfo> m_setQueryResult; //所有合法的邮件就在这里面
    QSet<uint32_t> m_setQueryResult_Conversation;//所有合法的会话在这里面
    QSet<QuerySummaryInfo> m_setQueryResult_Memory;
    QSet<QuerySummaryInfo> m_setQueryResult_DB;
    //QList<QuerySummaryInfo> m_listQueryResult; //由上面转换而来
    QMutex  m_queryResultSetMutex;
};
//! [2]

#endif // QMAILTREEMODEL_H
