/****************************************************************************
**
** Copyright (C) 2017 ��ɽ�칫 All Rights Reserved.
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
    void queryInMemoryResultSet(); //�ڴ��ѯ
    bool whetherNeedToDisplay(const MailHeaderInfo & stMailHeaderInfo); //�ж��Ƿ���Ҫ��ʾ�����Ƿ���Ҫ��ѯ�ļ�¼
    void addToQuerySet(const MailHeaderInfo & stMailHeaderInfo); //��ӵ���ѯ�����
    void generateQueryResultSet(); //���ɲ�ѯ�����
    void regenerateMailListModelData(); // ����Model����
    void updateProxyModelData();//������������ͼ����
    //�Ự�е��ʼ��Ƿ���ϲ�ѯ����
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

    //��ѯ������� ֻ��¼�Ϸ���mailId,������ʼ��л��˺�������ȫ����
    QSet<QuerySummaryInfo> m_setQueryResult; //���кϷ����ʼ�����������
    QSet<uint32_t> m_setQueryResult_Conversation;//���кϷ��ĻỰ��������
    QSet<QuerySummaryInfo> m_setQueryResult_Memory;
    QSet<QuerySummaryInfo> m_setQueryResult_DB;
    //QList<QuerySummaryInfo> m_listQueryResult; //������ת������
    QMutex  m_queryResultSetMutex;
};
//! [2]

#endif // QMAILTREEMODEL_H
