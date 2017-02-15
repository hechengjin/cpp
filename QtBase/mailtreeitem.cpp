/****************************************************************************
**
** Copyright (C) 2017 金山办公 All Rights Reserved.
** Contact: http://www.wps.cn/product/wpsmail/
**
****************************************************************************/

/*
    treeitem.cpp

    A container for items of data supplied by the simple tree model.
*/

#include "mailtreeitem.h"
#include <QDateTime>
#include <QStringList>
#include <QColor>
#include "MemoryDBManager.h"

//TreeMailItem::TreeMailItem(const QVector<QVariant> &data, TreeMailItem *parent)
//{
//    parentItem = parent;
//    itemData = data;
//}
MailTreeItem::MailTreeItem(MailTreeItem *parent)
{
    parentItem = parent;
}

MailTreeItem::~MailTreeItem()
{
    QMutexLocker locker(&m_childItemMutex);
    qDeleteAll(childItems);
}

MailTreeItem *MailTreeItem::child(int number)
{
    //QMutexLocker locker(&m_childItemMutex);
    return childItems.value(number);
}

int MailTreeItem::childCount() const
{
    //QMutexLocker locker(&m_childItemMutex);
    return childItems.count();
}

int MailTreeItem::childNumber() const
{
    //QMutexLocker locker(&m_childItemMutex);
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<MailTreeItem*>(this));

    return 0;
}

void MailTreeItem::clearChildItems()
{
    QMutexLocker locker(&m_childItemMutex);
    childItems.clear();
}

void MailTreeItem::removeItem(const MailListItemData & itemData)
{
    QMutexLocker locker(&m_childItemMutex);
    for (auto it = childItems.begin(); it != childItems.end(); /* don't increment here */) {
        if ((*it)->stItemData.id == itemData.id)
        {
            delete (*it);
            it = childItems.erase(it);
            break;
        }
        else
        {
            ++it;
        }
    }
}

void MailTreeItem::removeAllItems()
{
    QMutexLocker locker(&m_childItemMutex);
    for (auto it = childItems.begin(); it != childItems.end(); /* don't increment here */)
    {
        delete (*it);
        it = childItems.erase(it);
    }
}

//int TreeMailItem::columnCount() const
//{
//    return itemData.count();
//}

QVariant MailTreeItem::data(int column, int role) const
{
    //return itemData.value(column);
    QVariant rv;
    switch (role)
    {
        case Qt::TextColorRole:
            return QColor(Qt::black);
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
        case Qt::DisplayRole:
        {
            switch (column) {
                case MLMC_Id:
                    rv = stItemData.id;
                    break;

                case MLMC_ItemType:
                    rv = stItemData.itemType;
                    break;

                case MLMC_Subject:
                    rv = CMemoryDBManager::instance()->getSubject(stItemData);
                    break;

                case MLMC_Date:
                {
                    QDateTime maillDateTime;
                    uint64_t messageDate = CMemoryDBManager::instance()->getTime(stItemData);
                    maillDateTime.setTime_t(messageDate);
                    rv = maillDateTime;
                    break;
                }
                case MLMC_Size:
                    rv = CMemoryDBManager::instance()->getSize(stItemData);
                    break;
                case MLMC_Folder:
                    //rv = stItemData.folderId;
                    rv = CMemoryDBManager::instance()->getFolderId(stItemData);
                    break;
                default:
                    break;
            }
        }
        case UIROLE_ReadableSize:
        {
            if (MLMC_Size == column)
            {
                rv = CMemoryDBManager::instance()->getSize(stItemData);
            }
        }
    }

    return rv;
}

//bool TreeMailItem::insertChildren(int position, int count, int columns)
//{
//    if (position < 0 || position > childItems.size())
//        return false;
//
//    for (int row = 0; row < count; ++row) {
//        QVector<QVariant> data(columns);
//        TreeMailItem *item = new TreeMailItem(data, this);
//        childItems.insert(position, item);
//    }
//
//    return true;
//}

MailTreeItem * MailTreeItem::insertChildren(int position, const MailListItemData & stMailListItemData)
{
    
    if (position < 0 || position > childItems.size())
        return NULL;
    MailTreeItem *item = childExist(stMailListItemData);
    //QMutexLocker locker(&m_childItemMutex);
    if (!item)
    {
        item = new MailTreeItem(this);
        item->setData(stMailListItemData);
        childItems.insert(position, item);
    }
    return item;
}
MailTreeItem *MailTreeItem::childExist(const MailListItemData & stMailListItemData)
{
    for (int i = 0; i < childCount(); i++)
    {
        if (child(i)->stItemData.itemType == stMailListItemData.itemType && child(i)->stItemData.id == stMailListItemData.id)
        {
            return child(i);
        }
    }
    //if (stMailListItemData.itemType == MLIT_GROUP)
    //{
    //    for (int i = 0; i < childCount(); i++)
    //    {
    //        if (child(i)->stItemData.itemType == stMailListItemData.itemType && child(i)->stItemData.name == stMailListItemData.name)
    //        {
    //            return child(i);
    //        }
    //    }
    //}
    //else if (stMailListItemData.itemType == MLIT_MAIL)
    //{
    //    for (int i = 0; i < childCount(); i++)
    //    {
    //        if (child(i)->stItemData.itemType == stMailListItemData.itemType && child(i)->stItemData.id == stMailListItemData.id)
    //        {
    //            return child(i);
    //        }
    //    }
    //}
    return NULL;
}

//bool TreeMailItem::insertColumns(int position, int columns)
//{
//    if (position < 0 || position > itemData.size())
//        return false;
//
//    for (int column = 0; column < columns; ++column)
//        itemData.insert(position, QVariant());
//
//    foreach (TreeMailItem *child, childItems)
//        child->insertColumns(position, columns);
//
//    return true;
//}

MailTreeItem *MailTreeItem::parent()
{
    return parentItem;
}

bool MailTreeItem::removeChildren(int position, int count)
{
    QMutexLocker locker(&m_childItemMutex);
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);
    return true;
}


//bool TreeMailItem::removeColumns(int position, int columns)
//{
//    if (position < 0 || position + columns > itemData.size())
//        return false;
//
//    for (int column = 0; column < columns; ++column)
//        itemData.remove(position);
//
//    foreach (TreeMailItem *child, childItems)
//        child->removeColumns(position, columns);
//
//    return true;
//}


//bool TreeMailItem::setData(int column, const QVariant &value)
//{
//    if (column < 0 || column >= itemData.size())
//        return false;
//
//    itemData[column] = value;
//    return true;
//}

bool MailTreeItem::setData(const MailListItemData & stMailListItemData)
{
    stItemData = stMailListItemData;
    return true;
}
