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

class CMemoryDBManager;
class MailTreeItem;

//! [0]
class QMailTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    QMailTreeModel(QObject *parent = 0);
    //TreeMailModel(const QStringList &headers, const QString &data,
    //          QObject *parent = 0);
    ~QMailTreeModel();
//! [0] //! [1]

    static QMailTreeModel* instance();
    void initRootItem();
    void loadData(int mailListDisplayMode);
    void clear();

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
    //bool setData(const QModelIndex &index, const QVariant &value,
    //             int role = Qt::EditRole) Q_DECL_OVERRIDE;
    //bool setHeaderData(int section, Qt::Orientation orientation,
    //                   const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

    //bool insertColumns(int position, int columns,
    //                   const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    //bool removeColumns(int position, int columns,
    //                   const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    //bool insertRows(int position, int rows,
    //                const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeRows(int position, int rows,
        const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

    void resetModel();
    bool deleteRecord(const MailListItemData & stItemData);
    bool updateRecord(const MailListItemData & stItemData);
    bool clearRecords();

private:
    //void setupModelData(const QStringList &lines, TreeMailItem *parent);
    MailTreeItem *getItem(const QModelIndex &index) const;
    MailTreeItem *getParentItem(const QString & groupName);
    void recursionClear(MailTreeItem *pItem);
    MailTreeItem *m_rootItem;
    int m_mailListDisplayMode;
    
    //QMutex  m_modelMutex;
};
//! [2]

#endif // QMAILTREEMODEL_H
