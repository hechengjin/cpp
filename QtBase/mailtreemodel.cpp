/****************************************************************************
**
** Copyright (C) 2017 金山办公 All Rights Reserved.
** Contact: http://www.wps.cn/product/wpsmail/
**
****************************************************************************/

#include <QtWidgets>
#include <QDebug>

#include "mailtreemodel.h"
#include "mailsortfilterproxymodel.h"


Q_GLOBAL_STATIC(QMailTreeModel, treeMailModel)
QMailTreeModel *QMailTreeModel::instance()
{
    return treeMailModel;
}

QMailTreeModel::QMailTreeModel(QObject *parent)
: QAbstractItemModel(parent)
, m_rootItem(NULL)
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

void QMailTreeModel::initRootItem()
{
    m_rootItem = new MailTreeItem();
}

QMailTreeModel::~QMailTreeModel()
{
    clear();
}

void QMailTreeModel::clear()
{
   
    if (m_rootItem)
    {
        //clearRecords();
        removeRows(0, m_rootItem->childCount());
        //delete m_rootItem;
        //m_rootItem = NULL;
    }
}

bool QMailTreeModel::updateRecord(const MailListItemData & stItemData)
{
    bool change = false;
    for (int i = 0; i < m_rootItem->childCount(); i++) //遍历分组
    {
        MailTreeItem *groupItem = m_rootItem->child(i);
        for (int j = 0; j < groupItem->childCount(); j++)
        {
            MailTreeItem *conversationItem = groupItem->child(j);  //会话
            for (int m = 0; m < conversationItem->childCount(); m++)
            {
                MailTreeItem *mailItem = conversationItem->child(m); //邮件
                if (mailItem->stItemData.id == stItemData.id)
                {
                    //mailItem->stItemData.name = stItemData.name;
                    change = true;
                    break;
                }
            }
        }
    }
    if (change)
    {
        resetModel();
    }
    return change;
}

bool QMailTreeModel::clearRecords()
{
    if (MLDM_CONVERSATION == m_queryConditions.mailListDisplayMode)
    {
        for (int i = 0; i < m_rootItem->childCount(); i++) //遍历分组
        {
            MailTreeItem *groupItem = m_rootItem->child(i);
            for (int j = 0; j < groupItem->childCount(); j++)
            {
                MailTreeItem *conversationItem = groupItem->child(j);  //会话
                conversationItem->removeAllItems(); //会话下邮件删除
                if (conversationItem->childCount() <= 0)
                {
                    groupItem->removeItem(conversationItem->stItemData); //分组下会话删除
                }
            }
            if (groupItem->childCount() <= 0)
            {
                m_rootItem->removeItem(groupItem->stItemData); //分组删除
            }
        }
    }
    else if (MLDM_MAIL == m_queryConditions.mailListDisplayMode)
    {
        m_rootItem->removeAllItems();
    }
    return true;
}

bool QMailTreeModel::deleteRecord(const MailListItemData & stItemData)
{
    bool change = false;
    for (int i = 0; i < m_rootItem->childCount(); i++) //遍历分组
    {
        MailTreeItem *groupItem = m_rootItem->child(i);
        for (int j = 0; j < groupItem->childCount(); j++)
        {
            MailTreeItem *conversationItem = groupItem->child(j);  //会话
            for (int m = 0; m < conversationItem->childCount(); m++)
            {
                MailTreeItem *mailItem = conversationItem->child(m); //邮件
                if (mailItem->stItemData.id == stItemData.id)
                {
                    conversationItem->removeItem(stItemData);
                    change = true;
                    break;
                }
            }
            if (conversationItem->childCount() <= 0)
            {
                groupItem->removeItem(conversationItem->stItemData);
            }
        }
        if (groupItem->childCount() <= 0)
        {
            m_rootItem->removeItem(groupItem->stItemData);
        }
    }
    if (change)
    {
        resetModel();
    }
    return change;
}

void QMailTreeModel::resetModel()
{
    beginResetModel();
    endResetModel();
}


QString QMailTreeModel::querySizeGroupName(uint32_t messageSize)
{
    QString sizeGroupName;
    if (messageSize < MAIL_SIZE_25K)
    {
        sizeGroupName = QObject::tr("Minute (<25K)"); //微小(<25K)
    }
    else if (messageSize >= MAIL_SIZE_25K && messageSize < MAIL_SIZE_100K)
    {
        sizeGroupName = QObject::tr("Small (100K - 25K)");//"小(25K - 100K)"
    }
    else if (messageSize >= MAIL_SIZE_100K && messageSize < MAIL_SIZE_500K)
    {
        sizeGroupName = QObject::tr("Medium (500K - 100K)");//"中(100K - 500K)"
    }
    else if (messageSize >= MAIL_SIZE_500K && messageSize < MAIL_SIZE_1M)
    {
        sizeGroupName = QObject::tr("Big (1M - 500K)"); // "大(500K - 1M)"
    }
    else if (messageSize >= MAIL_SIZE_1M && messageSize <= MAIL_SIZE_5M)
    {
        sizeGroupName = QObject::tr("Great (5M - 1M)"); //很大(1M - 5M)
    }
    else if (messageSize > MAIL_SIZE_5M)
    {
        sizeGroupName = QObject::tr("Huge (>5M)");//巨大(>5M)
    }
    return sizeGroupName;
}

QString QMailTreeModel::generationGroupName(const MailHeaderInfo & stMailHeaderInfo)
{
    QString groupName;
    switch (m_queryConditions.curSortColumn)
    {
    case MLMC_Date:
    {
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
        uint64_t messageDate = stMailHeaderInfo.date;//CMemoryDBManager::instance()->getTime(stMailListItemData);
        if (messageDate <= todayEndTime && messageDate >= todayStartTime)
        {
            groupName = QObject::tr("today");
        }
        else if (messageDate <= yesterdayEndTime && messageDate >= yesterdayStartTime)
        {
            groupName = QObject::tr("yesterday");
        }
        break;
    }
    case MLMC_Size:
    {
        uint32_t messageSize = stMailHeaderInfo.messageSize;//CMemoryDBManager::instance()->getSize(stMailListItemData);
        groupName = querySizeGroupName(messageSize);
        break;
    }
    
    default:
        break;
    }
    
    return groupName;
}

QueryConditions QMailTreeModel::getQueryCondition()
{
    return m_queryConditions;
}

void QMailTreeModel::queryData(const QueryConditions& queryInfo)
{
    m_queryConditions = queryInfo;
    stepQueryData();
}

void QMailTreeModel::queryData()
{
    stepQueryData();
}

bool QMailTreeModel::stepQueryData()
{
    queryInMemoryResultSet();
    generateQueryResultSet();
    regenerateMailListModelData();
    return true;
}

void QMailTreeModel::generateQueryResultSet()
{
    QTime timeConsuming;
    timeConsuming.start();
    if (m_queryConditions.needAsynQuery)
    {
        m_setQueryResult = m_setQueryResult_Memory.intersect(m_setQueryResult_DB);
    }
    else
    {
        m_setQueryResult.swap(m_setQueryResult_Memory);
    }
    if (MLDM_CONVERSATION == m_queryConditions.mailListDisplayMode)
    {
        QSet<QuerySummaryInfo>::const_iterator iter = m_setQueryResult.constBegin();
        while (iter != m_setQueryResult.constEnd())
        {
            m_setQueryResult_Conversation.insert((*iter).conversationId);
            ++iter;
        }
    }
    else if (MLDM_MAIL == m_queryConditions.mailListDisplayMode)
    {

    }
    QString consumingTime = " generateQueryResultSet consume:" + QString::number(timeConsuming.elapsed());
    qDebug() << consumingTime;
}


void QMailTreeModel::regenerateMailListModelData()
{
    QTime timeConsuming;
    timeConsuming.start();
    clear();
    initRootItem();
    QString consumingTime = " regenerateMailListModelData  1. consume:" + QString::number(timeConsuming.elapsed());
    qDebug() << consumingTime;
    MailListItemData stMailListItemData;
    if (MLDM_CONVERSATION == m_queryConditions.mailListDisplayMode)
    {
        //1. 生成一级分组信息
        CMemoryDBManager::instance()->clearGroup();
        MailHeaderInfo stMailHeaderInfo;
        MailConversationInfo stMailConversationInfo;
        QSet<uint32_t>::const_iterator iter = m_setQueryResult_Conversation.constBegin();
        while (iter != m_setQueryResult_Conversation.constEnd())
        {
            stMailConversationInfo = CMemoryDBManager::instance()->getConversationHeader(*iter);
            MailGroupInfo stMailGroupInfo;
            stMailGroupInfo.name = generationGroupName(stMailConversationInfo);
            stMailGroupInfo = CMemoryDBManager::instance()->addGroup(stMailGroupInfo);
            stMailListItemData.itemType = MLIT_GROUP;
            stMailListItemData.id = stMailGroupInfo.id;
            //stMailListItemData.messageDate = stMailConversationInfo.date;
            //stMailListItemData.messageSize = stMailConversationInfo.messageSize;
            //stMailListItemData.name = generationGroupName(stMailListItemData);
            m_rootItem->insertChildren(m_rootItem->childCount(), stMailListItemData);
            ++iter;
        }
        consumingTime = " regenerateMailListModelData  2 consume:" + QString::number(timeConsuming.elapsed());
        qDebug() << consumingTime;
        //2. 生成会话信息 和 其它下邮件信息
        uint64_t mailId = DEFAULT_VALUE_ZERO;
        MailListItemData stParentMailListItemData;
        QSet<uint32_t>::const_iterator iter2 = m_setQueryResult_Conversation.constBegin();
        while (iter2 != m_setQueryResult_Conversation.constEnd())
        {
            stMailConversationInfo = CMemoryDBManager::instance()->getConversationHeader(*iter2);
            stMailListItemData.itemType = MLIT_CONVERSATION;
            //stMailListItemData.messageDate = stMailConversationInfo.date;
            //stMailListItemData.name = stMailConversationInfo.Subject;
            stMailListItemData.id = stMailConversationInfo.id;
            //stMailListItemData.messageSize = stMailConversationInfo.messageSize;
            QString groupName = generationGroupName(stMailConversationInfo);
            MailGroupInfo stMailGroupInfo = CMemoryDBManager::instance()->getGroupHeader(groupName);
            stParentMailListItemData.id = stMailGroupInfo.id;
            stParentMailListItemData.itemType = MLIT_GROUP;
            MailTreeItem *parent = getParentItem(stParentMailListItemData);
            if (parent)
            {
                MailTreeItem * converItem = parent->insertChildren(parent->childCount(), stMailListItemData);
                if (converItem) //在会话下添加所有邮件
                {
                    QSet<uint64_t>::const_iterator iter3 = stMailConversationInfo.conversationMailIds.constBegin();
                    while (iter3 != stMailConversationInfo.conversationMailIds.constEnd()) {
                        mailId = *iter3;
                        if (converMailLegal(mailId))
                        {
                            stMailHeaderInfo = CMemoryDBManager::instance()->getMailHeader(mailId);
                            stMailListItemData.itemType = MLIT_MAIL;
                            //stMailListItemData.messageDate = stMailHeaderInfo.date;
                            //stMailListItemData.name = stMailHeaderInfo.Subject;
                            stMailListItemData.id = stMailHeaderInfo.id;
                            //stMailListItemData.messageSize = stMailHeaderInfo.messageSize;
                            //stMailListItemData.folderId = stMailHeaderInfo.folderId;
                            converItem->insertChildren(converItem->childCount(), stMailListItemData);
                        }
                        ++iter3;
                    }
                }
            }
            ++iter2;
        }
        consumingTime = " regenerateMailListModelData  3 consume:" + QString::number(timeConsuming.elapsed());
        qDebug() << consumingTime;
    }
    else if (MLDM_MAIL == m_queryConditions.mailListDisplayMode)
    {
        MailHeaderInfo stMailHeaderInfo;
        QSet<QuerySummaryInfo>::const_iterator iter = m_setQueryResult.constBegin();
        while (iter != m_setQueryResult.constEnd())
        {
            //stMailHeaderInfo = CMemoryDBManager::instance()->getMailHeader((*iter).id);
            stMailListItemData.itemType = MLIT_MAIL;
            stMailListItemData.id = (*iter).id;//stMailHeaderInfo.id;
            //stMailListItemData.messageDate = stMailHeaderInfo.date;
            //stMailListItemData.messageSize = stMailHeaderInfo.messageSize;
            //stMailListItemData.name = stMailHeaderInfo.Subject;
            m_rootItem->insertChildren(m_rootItem->childCount(), stMailListItemData);
            ++iter;
        }
        consumingTime = " regenerateMailListModelData  2 consume:" + QString::number(timeConsuming.elapsed());
        qDebug() << consumingTime;
    }
    
  
    updateProxyModelData();
    consumingTime = " regenerateMailListModelData consume:" + QString::number(timeConsuming.elapsed());
    qDebug() << consumingTime;
}

void QMailTreeModel::updateProxyModelData()
{
    QTime timeConsuming;
    timeConsuming.start();
    QMailSortFilterProxyModel::instance()->setSourceModel(this);
    QString consumingTime = " updateProxyModelData consume:" + QString::number(timeConsuming.elapsed());
    qDebug() << consumingTime;
    //int sortColumn = QMailSortFilterProxyModel::instance()->sortColumn();
    //Qt::SortOrder order = QMailSortFilterProxyModel::instance()->sortOrder();
    //int xx;
    //xx++;
    //QMailSortFilterProxyModel::instance()->invalidProxyModel(m_queryConditions);
}

bool QMailTreeModel::converMailLegal(uint64_t mailId)
{
    bool legal = false;
    QSet<QuerySummaryInfo>::const_iterator iter = m_setQueryResult.constBegin();
    while (iter != m_setQueryResult.constEnd())
    {
        if (mailId == (*iter).id)
        {
            legal = true;
            break;
        }
        ++iter;
    }
    return legal;
}



void QMailTreeModel::queryInMemoryResultSet()
{
    QTime timeConsuming;
    timeConsuming.start();
    QMutexLocker locker(&m_queryResultSetMutex);
    m_setQueryResult.clear();
    m_setQueryResult_Memory.clear();
    m_setQueryResult_DB.clear();
    m_setQueryResult_Conversation.clear();
    QMapIterator<uint64_t, MailHeaderInfo> iter(CMemoryDBManager::instance()->m_mapMailMemoryData);
    while (iter.hasNext()) {
        iter.next();
        if (whetherNeedToDisplay(iter.value()))
        {
            addToQuerySet(iter.value());
        }
    }
    QString consumingTime = " queryInMemoryResultSet consume:" + QString::number(timeConsuming.elapsed());
    qDebug() << consumingTime;
}


bool QMailTreeModel::whetherNeedToDisplay(const MailHeaderInfo & stMailHeaderInfo)
{
    uint32_t queryFlags = QMF_NONE;
    uint32_t passQueryFlags = QMF_NONE;
    //查询邮件夹过滤
    uint32_t folderId = m_queryConditions.folderId;
    if (folderId != DEFAULT_VALUE_ZERO)
    {
        queryFlags |= QMF_FOLDER;
        if (folderId == stMailHeaderInfo.folderId)
        {
            passQueryFlags |= QMF_FOLDER;
        }
    }
    //标题过滤
    QString subject = m_queryConditions.subject;
    if (!subject.isEmpty())
    {
        queryFlags |= QMF_SUBJECT;
        if (stMailHeaderInfo.Subject.contains(subject))
        {
            passQueryFlags |= QMF_SUBJECT;
        }
    }
    //发件人过滤
    if (m_queryConditions.authors.size() > 0)
    {
        queryFlags |= QMF_AUTHOR;
        if (m_queryConditions.authors.contains(stMailHeaderInfo.author.toULongLong()))
        {
            passQueryFlags |= QMF_AUTHOR;
        }
    }
    //收件人过滤
    if (m_queryConditions.recipients.size() > 0)
    {
        queryFlags |= QMF_RECIPIENTS;
        uint64_t contactId = DEFAULT_VALUE_ZERO;
        QStringList recsList = stMailHeaderInfo.recipients.split(",");
        for (int i = 0; i < recsList.size(); i++)
        {
            contactId = recsList.at(i).toULongLong();
            if (m_queryConditions.recipients.contains(contactId))
            {
                passQueryFlags |= QMF_RECIPIENTS;
                break;
            }
        }
    }
    //附件过滤
    if (m_queryConditions.attachmentOption != QOA_UNLIMITED)
    {
        queryFlags |= QMF_ATTACHMENT;
        if (m_queryConditions.attachmentOption == QOA_EXIST && (stMailHeaderInfo.flags & MF_Attachment) == MF_Attachment)
        {
            passQueryFlags |= QMF_ATTACHMENT;
        }
        else if (m_queryConditions.attachmentOption == QOA_WITHOUT && (stMailHeaderInfo.flags & MF_Attachment) != MF_Attachment)
        {
            passQueryFlags |= QMF_ATTACHMENT;
        }
    }
    //时间过滤
    if (m_queryConditions.timeOption != QOT_UNLIMITED)
    {
        queryFlags |= QMF_TIME;
        if (stMailHeaderInfo.date >= m_queryConditions.startTime && stMailHeaderInfo.date <= m_queryConditions.endTime)
        {
            passQueryFlags |= QMF_TIME;
        }
    }
    //
    if (passQueryFlags == queryFlags/* && queryFlags != QMF_NONE*/)
    {
        return true;
    }

    return false;
}


void QMailTreeModel::addToQuerySet(const MailHeaderInfo & stMailHeaderInfo)
{
    QuerySummaryInfo stQuerySummaryInfo;
    stQuerySummaryInfo.id = stMailHeaderInfo.id;
    stQuerySummaryInfo.conversationId = stMailHeaderInfo.conversationId;
    ///stQuerySummaryInfo.date = stMailHeaderInfo.date;
    //stQuerySummaryInfo.messageSize = stMailHeaderInfo.messageSize;
    m_setQueryResult_Memory.insert(stQuerySummaryInfo);
}

MailTreeItem * QMailTreeModel::getParentItem(const MailListItemData & stMailListItemData)
{
    for (int i = 0; i < m_rootItem->childCount(); i++)
    {
        if (m_rootItem->child(i)->stItemData.id == stMailListItemData.id && m_rootItem->child(i)->stItemData.itemType == stMailListItemData.itemType)
        {
            return m_rootItem->child(i);
        }
    }
    return NULL;
}
//! [2]
int QMailTreeModel::columnCount(const QModelIndex & /* parent */) const
{
    return MLMC_Count;
    //return m_rootItem->columnCount();
}
//! [2]

QVariant QMailTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    //if (role != Qt::DisplayRole && role !=UIROLE_ReadableSize)
    //    return QVariant();
    MailTreeItem *item = getItem(index);

    return item->data(index.column(), role);
}

//! [3]
Qt::ItemFlags QMailTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    //return Qt::ItemIsEditable | QAbstractItemModel::flags(index); //可编辑
    return QAbstractItemModel::flags(index);
}
//! [3]

//! [4]
MailTreeItem *QMailTreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        MailTreeItem *item = static_cast<MailTreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return m_rootItem;
}
//! [4]

QVariant QMailTreeModel::headerData(int section, Qt::Orientation orientation,
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
                rv = tr("    Size    ");
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

QModelIndex QMailTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();
    
    MailTreeItem *parentItem = getItem(parent);
    if (NULL == parentItem)
    {
        return QModelIndex();
    }

    MailTreeItem *childItem = parentItem->child(row);
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

bool QMailTreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    MailTreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    MailListItemData stMailListItemData;
    success = parentItem->insertChildren(position, stMailListItemData);
    endInsertRows();

    return success;
}

QModelIndex QMailTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    MailTreeItem *childItem = getItem(index);
    MailTreeItem *parentItem = childItem->parent();

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

bool QMailTreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    if (rows <= 0)
    {
        return false;
    }
    MailTreeItem *parentItem = getItem(parent);
    bool success = true;
    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();
    return success;
}

//! [8]
int QMailTreeModel::rowCount(const QModelIndex &parent) const
{
    MailTreeItem *parentItem = getItem(parent);
    if (NULL == parentItem)
    {
        return DEFAULT_VALUE_ZERO;
    }
    if (parentItem->stItemData.itemType == MLIT_CONVERSATION)
    {
        int xx;
        xx =1;
        xx++;
    }
    return parentItem->childCount();
}

bool QMailTreeModel::setData(const QModelIndex &index, const MailListItemData &stMailListItemData)
{

    MailTreeItem *item = getItem(index);
    bool result = item->setData(stMailListItemData);

    if (result)
        emit dataChanged(index, index);

    return result;
}

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
