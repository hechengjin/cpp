/****************************************************************************
**
** Copyright (C) 2017 ��ɽ�칫 All Rights Reserved.
** Contact: http://www.wps.cn/product/wpsmail/
**
****************************************************************************/

#ifndef TREEMAILITEM_H
#define TREEMAILITEM_H
#include "dataDefine.h"

#include <QList>
#include <QVariant>
#include <QVector>

class TreeMailItem
{
public:
    //explicit TreeMailItem(const QVector<QVariant> &data, TreeMailItem *parent = 0);
    explicit TreeMailItem(TreeMailItem *parent = 0);
    ~TreeMailItem();

    TreeMailItem *child(int number);
    int childCount() const;
    //int columnCount() const;
    QVariant data(int column) const;
    //bool insertChildren(int position, int count, int columns);
    TreeMailItem *insertChildren(int position, const MailListItemData & stMailListItemData);
    TreeMailItem *childExist(const MailListItemData & stMailListItemData);
    //bool insertColumns(int position, int columns);
    TreeMailItem *parent();
    bool removeChildren(int position, int count);
    //bool removeColumns(int position, int columns);
    int childNumber() const;
    //bool setData(int column, const QVariant &value);
    bool setData(const MailListItemData & stMailListItemData);

public:
    MailListItemData stItemData;
private:
    QList<TreeMailItem*> childItems; //������������
    //QVector<QVariant> itemData;  //��ǰ��ÿ�е�����  itemData[column] = value; //������δ���  //���¼���һ��
    

    TreeMailItem *parentItem;
};

#endif // TREEMAILITEM_H
