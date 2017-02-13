/****************************************************************************
**
** Copyright (C) 2017 金山办公 All Rights Reserved.
** Contact: http://www.wps.cn/product/wpsmail/
**
****************************************************************************/

#ifndef MAILTREEITEM_H
#define MAILTREEITEM_H
#include "dataDefine.h"

#include <QList>
#include <QVariant>
#include <QVector>

class MailTreeItem
{
public:
    //explicit TreeMailItem(const QVector<QVariant> &data, TreeMailItem *parent = 0);
    explicit MailTreeItem(MailTreeItem *parent = 0);
    ~MailTreeItem();

    MailTreeItem *child(int number);
    int childCount() const;
    //int columnCount() const;
    QVariant data(int column, int role) const;
    //bool insertChildren(int position, int count, int columns);
    MailTreeItem *insertChildren(int position, const MailListItemData & stMailListItemData);
    MailTreeItem *childExist(const MailListItemData & stMailListItemData);
    //bool insertColumns(int position, int columns);
    MailTreeItem *parent();
    bool removeChildren(int position, int count);
    //bool removeColumns(int position, int columns);
    int childNumber() const;
    //bool setData(int column, const QVariant &value);
    bool setData(const MailListItemData & stMailListItemData);

public:
    MailListItemData stItemData;
private:
    QList<MailTreeItem*> childItems; //所有子行数据
    //QVector<QVariant> itemData;  //当前行每列的数据  itemData[column] = value; //排序如何处理？  //重新加载一次
    

    MailTreeItem *parentItem;
};

#endif // MAILTREEITEM_H
