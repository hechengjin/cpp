/****************************************************************************
**
** Copyright (C) 2017 金山办公 All Rights Reserved.
** Contact: http://www.wps.cn/product/wpsmail/
**
****************************************************************************/

#include <QtWidgets>

#include "treemailitem.h"
#include "treemailmodel.h"
#include "MemoryDBManager.h"

Q_GLOBAL_STATIC(TreeMailModel, treeMailModel)
TreeMailModel *TreeMailModel::instance()
{
    return treeMailModel;
}

TreeMailModel::TreeMailModel(QObject *parent)
: QAbstractItemModel(parent)
, m_mailListDisplayMode(MLDM_CONVERSATION)
{
}

//TreeMailModel::TreeMailModel(const QStringList &headers, const QString &data, QObject *parent)
//    : QAbstractItemModel(parent)
//{
//    QVector<QVariant> rootData;
//    foreach (QString header, headers)
//        rootData << header;
//
//    rootItem = new TreeMailItem(rootData);
//    setupModelData(data.split(QString("\n")), rootItem);
//}

void TreeMailModel::initRootItem()
{
    m_rootItem = new TreeMailItem();
}

TreeMailModel::~TreeMailModel()
{
    delete m_rootItem;
}

QString generationGroupName(/*int dayOfWeek, */uint64_t mailDate)
{
    QString groupName;
    groupName = QObject::tr("early");
    //今天
    QDate now = QDate::currentDate();
    QDateTime todayStartDate(QDate(now.year(), now.month(), now.day()), QTime(0, 0, 0, 1));
    QDateTime todayEndDate(QDate(now.year(), now.month(), now.day()), QTime(23, 59, 59, 998));
    uint64_t todayStartTime = todayStartDate.toTime_t();
    uint64_t todayEndTime = todayEndDate.toTime_t();
    // 昨天
    QDate yesterday = now;
    yesterday = yesterday.addDays(-1);
    QDateTime yesterdayStartDate(QDate(yesterday.year(), yesterday.month(), yesterday.day()), QTime(0, 0, 0, 1));
    QDateTime yesterdayEndDate(QDate(yesterday.year(), yesterday.month(), yesterday.day()), QTime(23, 59, 59, 998));
    uint64_t yesterdayStartTime = yesterdayStartDate.toTime_t();
    uint64_t yesterdayEndTime = yesterdayEndDate.toTime_t();

    if (mailDate <= todayEndTime && mailDate >= todayStartTime)
    {
        groupName = QObject::tr("today");
    }
    else if (mailDate <= yesterdayEndTime && mailDate >= yesterdayStartTime)
    {
        groupName = QObject::tr("yesterday");
    }
    return groupName;
}

void TreeMailModel::loadData(int mailListDisplayMode)
{
#pragma region 初始化模型数据
    m_mailListDisplayMode = mailListDisplayMode;
    MailListItemData stMailListItemData;
    MailHeaderInfo stMailHeaderInfo;
    if (m_mailListDisplayMode == MLDM_CONVERSATION)
    {
        //1. 生成一级分组信息
        int groupId = 1;
        MailConversationInfo stMailConversationInfo;
        for (int i = 0; i < CMemoryDBManager::instance()->m_listMemMailConversations.size(); i++)
        {
            stMailConversationInfo = CMemoryDBManager::instance()->m_listMemMailConversations.at(i);
            stMailListItemData.itemType = MLIT_GROUP;
            stMailListItemData.id = groupId++;
            stMailListItemData.messageDate = stMailConversationInfo.date;
            stMailListItemData.name = generationGroupName(stMailListItemData.messageDate);            
            m_rootItem->insertChildren(m_rootItem->childCount(), stMailListItemData);
        }

        //2. 生成会话信息 和 其它下邮件信息
        for (int i = 0; i < CMemoryDBManager::instance()->m_listMemMailConversations.size(); i++)
        {
            stMailConversationInfo = CMemoryDBManager::instance()->m_listMemMailConversations.at(i);
            QString groupName = generationGroupName(stMailConversationInfo.date);
            stMailListItemData.itemType = MLIT_CONVERSATION;
            stMailListItemData.messageDate = stMailConversationInfo.date;
            stMailListItemData.name = stMailConversationInfo.Subject;
            stMailListItemData.id = stMailConversationInfo.Id;
            TreeMailItem *parent = getParentItem(groupName);
            if (parent)
            {
                TreeMailItem * converItem = parent->insertChildren(parent->childCount(), stMailListItemData);
                if (converItem) //在会话下添加所有邮件
                {
                    for (int i = 0; i < stMailConversationInfo.listConversationMailIds.size(); i++)
                    {
                        stMailHeaderInfo = CMemoryDBManager::instance()->getMailHeader(stMailConversationInfo.listConversationMailIds.at(i));
                        stMailListItemData.itemType = MLIT_MAIL;
                        stMailListItemData.messageDate = stMailHeaderInfo.date;
                        stMailListItemData.name = stMailHeaderInfo.Subject;
                        stMailListItemData.id = stMailHeaderInfo.Id;
                        converItem->insertChildren(converItem->childCount(), stMailListItemData);
                    }
                    
                }
            }
        }
    }
#pragma endregion 初始化模型数据
}

TreeMailItem * TreeMailModel::getParentItem(const QString & groupName)
{
    for (int i = 0; i < m_rootItem->childCount(); i++)
    {
        if (m_rootItem->child(i)->stItemData.name == groupName)
        {
            return m_rootItem->child(i);
        }
    }
    return NULL;
}
//! [2]
int TreeMailModel::columnCount(const QModelIndex & /* parent */) const
{
    return MLMC_Count;
    //return m_rootItem->columnCount();
}
//! [2]

QVariant TreeMailModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeMailItem *item = getItem(index);

    return item->data(index.column());
}

//! [3]
Qt::ItemFlags TreeMailModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    //return Qt::ItemIsEditable | QAbstractItemModel::flags(index); //可编辑
    return QAbstractItemModel::flags(index); //可编辑
}
//! [3]

//! [4]
TreeMailItem *TreeMailModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeMailItem *item = static_cast<TreeMailItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return m_rootItem;
}
//! [4]

QVariant TreeMailModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    QVariant rv;
    //if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    //    return m_rootItem->data(section);
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section) {
            case MLMC_Fold:
                rv = tr("        ");
                break;
            case MLMC_Id:
                rv = tr("ID");
                break;

            case MLMC_ItemType:
                rv = tr("ItemType");
                break;

            case MLMC_Priority:
                rv = tr("Priority");
                break;

            case MLMC_Attachment:
                rv = tr("Attachment");
                break;
            case MLMC_From:
                rv = tr("From");
                break;
            case MLMC_To:
                rv = tr("To");
                break;
            case MLMC_Subject:
                rv = tr("            Subject            ");
                break;
            case MLMC_Date:
                rv = tr("Date");
                break;
            case MLMC_Size:
                rv = tr("Size");
                break;
            case MLMC_Folder:
                rv = tr("Folder");
                break;
            case MLMC_Uid:
                rv = tr("UID");
                break;

            default:
                break;
        }
    }
    return rv;
}

QModelIndex TreeMailModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();


    TreeMailItem *parentItem = getItem(parent);

    TreeMailItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

//bool TreeMailModel::insertColumns(int position, int columns, const QModelIndex &parent)
//{
//    bool success;
//
//    beginInsertColumns(parent, position, position + columns - 1);
//    success = m_rootItem->insertColumns(position, columns);
//    endInsertColumns();
//
//    return success;
//}

//bool TreeMailModel::insertRows(int position, int rows, const QModelIndex &parent)
//{
//    TreeMailItem *parentItem = getItem(parent);
//    bool success;
//
//    beginInsertRows(parent, position, position + rows - 1);
//    success = parentItem->insertChildren(position, rows, m_rootItem->columnCount());
//    endInsertRows();
//
//    return success;
//}

//! [7]
QModelIndex TreeMailModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeMailItem *childItem = getItem(index);
    TreeMailItem *parentItem = childItem->parent();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}
//! [7]

//bool TreeMailModel::removeColumns(int position, int columns, const QModelIndex &parent)
//{
//    bool success;
//
//    beginRemoveColumns(parent, position, position + columns - 1);
//    success = m_rootItem->removeColumns(position, columns);
//    endRemoveColumns();
//
//    if (m_rootItem->columnCount() == 0)
//        removeRows(0, rowCount());
//
//    return success;
//}

//bool TreeMailModel::removeRows(int position, int rows, const QModelIndex &parent)
//{
//    TreeMailItem *parentItem = getItem(parent);
//    bool success = true;
//
//    beginRemoveRows(parent, position, position + rows - 1);
//    success = parentItem->removeChildren(position, rows);
//    endRemoveRows();
//
//    return success;
//}

//! [8]
int TreeMailModel::rowCount(const QModelIndex &parent) const
{
    TreeMailItem *parentItem = getItem(parent);
    if (parentItem->stItemData.itemType == MLIT_CONVERSATION)
    {
        int xx;
        xx =1;
        xx++;
    }
    return parentItem->childCount();
}
//! [8]

//bool TreeMailModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (role != Qt::EditRole)
//        return false;
//
//    TreeMailItem *item = getItem(index);
//    bool result = item->setData(index.column(), value);
//
//    if (result)
//        emit dataChanged(index, index);
//
//    return result;
//}

//bool TreeMailModel::setHeaderData(int section, Qt::Orientation orientation,
//                              const QVariant &value, int role)
//{
//    if (role != Qt::EditRole || orientation != Qt::Horizontal)
//        return false;
//
//    bool result = m_rootItem->setData(section, value);
//
//    if (result)
//        emit headerDataChanged(orientation, section, section);
//
//    return result;
//}

//void TreeMailModel::setupModelData(const QStringList &lines, TreeMailItem *parent)
//{
//    QList<TreeMailItem*> parents;
//    QList<int> indentations;
//    parents << parent;
//    indentations << 0;
//
//    int number = 0;
//
//    while (number < lines.count()) {
//        int position = 0;
//        while (position < lines[number].length()) {
//            if (lines[number].mid(position, 1) != " ")
//                break;
//            ++position;
//        }
//
//        QString lineData = lines[number].mid(position).trimmed();
//
//        if (!lineData.isEmpty()) {
//            // Read the column data from the rest of the line.
//            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
//            QVector<QVariant> columnData;
//            for (int column = 0; column < columnStrings.count(); ++column)
//                columnData << columnStrings[column];
//
//            if (position > indentations.last()) {
//                // The last child of the current parent is now the new parent
//                // unless the current parent has no children.
//
//                if (parents.last()->childCount() > 0) {
//                    parents << parents.last()->child(parents.last()->childCount()-1);
//                    indentations << position;
//                }
//            } else {
//                while (position < indentations.last() && parents.count() > 0) {
//                    parents.pop_back();
//                    indentations.pop_back();
//                }
//            }
//
//            // Append a new item to the current parent's list of children.
//            TreeMailItem *parent = parents.last();
//            parent->insertChildren(parent->childCount(), 1, m_rootItem->columnCount());
//            for (int column = 0; column < columnData.size(); ++column)
//                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
//        }
//
//        ++number;
//    }
//}
