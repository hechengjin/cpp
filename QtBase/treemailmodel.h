/****************************************************************************
**
** Copyright (C) 2017 金山办公 All Rights Reserved.
** Contact: http://www.wps.cn/product/wpsmail/
**
****************************************************************************/

#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class CMemoryDBManager;
class TreeMailItem;

//! [0]
class TreeMailModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeMailModel(QObject *parent = 0);
    //TreeMailModel(const QStringList &headers, const QString &data,
    //          QObject *parent = 0);
    ~TreeMailModel();
//! [0] //! [1]

    static TreeMailModel* instance();
    void initRootItem();
    void loadData(int mailListDisplayMode);

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
    //bool removeRows(int position, int rows,
    //                const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

private:
    //void setupModelData(const QStringList &lines, TreeMailItem *parent);
    TreeMailItem *getItem(const QModelIndex &index) const;
    TreeMailItem *getParentItem(const QString & groupName);
    TreeMailItem *m_rootItem;
    int m_mailListDisplayMode;
};
//! [2]

#endif // TREEMODEL_H
