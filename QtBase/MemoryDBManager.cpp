#include "MemoryDBManager.h"
#include <QDate>
#include <QDebug>
Q_GLOBAL_STATIC(CMemoryDBManager, memoryDBManager)
CMemoryDBManager *CMemoryDBManager::instance()
{
    return memoryDBManager;
}

CMemoryDBManager::CMemoryDBManager()
: m_groupId(1)
{
}

CMemoryDBManager::~CMemoryDBManager()
{
}

void CMemoryDBManager::init()
{
    QTime timeConsuming;
    timeConsuming.start();
#pragma region 初始化邮件
    uint32_t inboxFolderId = 1;
    uint32_t oneServerId = 1;
    //今天
    QDate now = QDate::currentDate();

    // 昨天
    QDate yesterday = now;
    yesterday = yesterday.addDays(-1);

    //前天
    QDate beforeyesterday = yesterday;
    beforeyesterday = beforeyesterday.addDays(-1);
    MemoryMailData stMemoryMailData;
    for (int i = 0; i < 10; i++) //初始化邮件数据
    {
        MailHeaderInfo stMailHeaderInfo;
        stMailHeaderInfo.id = i + 1;
        stMailHeaderInfo.serverId = oneServerId;
        if (i%2 == 0)
        {
            stMailHeaderInfo.folderId = inboxFolderId;
        }
        else
            stMailHeaderInfo.folderId = 2;

        int size = qrand() % 5242880000 + 1; 
        stMailHeaderInfo.messageSize = size;
        if ( i>=1 && i<=5)
        {
            stMailHeaderInfo.conversationId = 1;
        }
        else
        {
            stMailHeaderInfo.conversationId = 2;
            if (i == 0)
            {
                stMailHeaderInfo.messageSize = 5242880000;
            }
        }
            
        
        //stMailHeaderInfo.messageId = messageID;
        stMailHeaderInfo.Subject = "Mail Subject:" + QString::number(i);
        //stMailHeaderInfo.uid = msgKey;
        //stMailHeaderInfo.changeKey = stFetchMessagesParam.changeKey;
        //stMailHeaderInfo.flags |= MF_Attachment;
        int hour = qrand() % 22 + 1;
        int minute = qrand() % 58 + 1;
        int sec = qrand() % 58 + 1;
        if (i % 2 == 0)
        {
            QDateTime mailDate(QDate(now.year(), now.month(), now.day()), QTime(hour, minute, sec));
            stMailHeaderInfo.date = mailDate.toTime_t();
        }
        else
        {
            QDateTime mailDate(QDate(yesterday.year(), yesterday.month(), yesterday.day()), QTime(hour, minute, sec));
            stMailHeaderInfo.date = mailDate.toTime_t();
        }

           
        int authorId = qrand() % 1000 + 1;
        stMailHeaderInfo.author = QString::number(authorId);
        QStringList tempAddress;
        int recipientId = qrand() % 1000 + 1;
        tempAddress << QString::number(recipientId);
        recipientId = qrand() % 1000 + 1;
        tempAddress << QString::number(recipientId);
        tempAddress.removeOne("0");
        stMailHeaderInfo.recipients = tempAddress.join(",");
        tempAddress.clear();
        //stMailHeaderInfo.ccList = tempAddress.join(",");
        //stMailHeaderInfo.bccList = tempAddress.join(",");
        //stMailHeaderInfo.referenceInfo = stFetchMessagesParam.references.join(",");
        stMailHeaderInfo.flags = DEFAULT_VALUE_ZERO;
        //stMailHeaderInfo.keyLocal = getKeyLocal(stMailHeaderInfo);
        stMemoryMailData.vecMailHeaderDatas.push_back(stMailHeaderInfo);
    }
    m_mapMailMemoryData[inboxFolderId] = stMemoryMailData;
#pragma endregion 初始化邮件

#pragma region 初始化会话数据
    MailConversationInfo stMailConversationInfo;
    stMailConversationInfo = m_mapMailMemoryData[inboxFolderId].vecMailHeaderDatas.at(1);
    stMailConversationInfo.id = 1;
    stMailConversationInfo.Subject = "Conversation Subject: 1";
    int hour = qrand() % 22 + 1;
    int minute = qrand() % 58 + 1;
    int sec = qrand() % 58 + 1;
    QDateTime mailDate(QDate(now.year(), now.month(), now.day()), QTime(hour, minute, sec));
    stMailConversationInfo.date = mailDate.toTime_t();
    //for (int i = 1; i <= 5; i++)
    //{
    //    stMailConversationInfo.listConversationMailIds.push_back(i);
    //}
    addConversation(stMailConversationInfo);

    stMailConversationInfo.Subject = "Conversation Subject: 2";
    stMailConversationInfo.id = 2;
    stMailConversationInfo.messageSize = 5242880000;
    QDateTime mailDate2(QDate(yesterday.year(), yesterday.month(), yesterday.day()), QTime(hour, minute, sec));
    stMailConversationInfo.date = mailDate2.toTime_t();
    //for (int i = 6; i <= 10; i++)
    //{
    //    stMailConversationInfo.listConversationMailIds.push_back(i);
    //}
    addConversation(stMailConversationInfo);

    QMapIterator<uint32_t, MemoryMailData> iter(m_mapMailMemoryData);
    int index = 0;
    while (iter.hasNext())
    {
        iter.next();
        for (int i = 0; i < iter.value().vecMailHeaderDatas.size(); ++i) {
            if (iter.value().vecMailHeaderDatas.at(i).conversationId == 1)
            {
                m_mapMailConversationData[1].conversationMailIds.insert(iter.value().vecMailHeaderDatas.at(i).id);
            }
            else
            {
                m_mapMailConversationData[2].conversationMailIds.insert(iter.value().vecMailHeaderDatas.at(i).id);
            }
        }
        index++;
    }

#pragma endregion 初始化会话数据

    QString consumingTime = " init data consume:" + QString::number(timeConsuming.elapsed());
    qDebug() << consumingTime;
}

MailHeaderInfo CMemoryDBManager::getMailHeader(uint64_t mailId)
{
    QMutexLocker locker(&m_mailMutex);
    QMapIterator<uint32_t, MemoryMailData> iter(m_mapMailMemoryData);
    int index = 0;
    while (iter.hasNext())
    {
        iter.next();
        for (int i = 0; i < iter.value().vecMailHeaderDatas.size(); ++i) {
            if (iter.value().vecMailHeaderDatas.at(i).id == mailId)
            {
                return iter.value().vecMailHeaderDatas.at(i);
            }
        }
        index++;
    }
    MailHeaderInfo stMailHeaderInfo;
    return stMailHeaderInfo;
}

uint32_t CMemoryDBManager::getFolderId(const MailListItemData & stItemData)
{
    if (stItemData.itemType == MLIT_MAIL)
    {
        return getMailHeader(stItemData.id).folderId;
    }
    return DEFAULT_VALUE_ZERO;
}

uint32_t CMemoryDBManager::getSize(const MailListItemData & stItemData)
{
    if (stItemData.itemType == MLIT_MAIL)
    {
        return getMailHeader(stItemData.id).messageSize;
    }
    else if (MLDM_CONVERSATION)
    {
        return getConversationHeader(stItemData.id).messageSize;
    }
    return DEFAULT_VALUE_ZERO;
}

uint64_t CMemoryDBManager::getTime(const MailListItemData & stItemData)
{
    if (stItemData.itemType == MLIT_MAIL)
    {
        return getMailHeader(stItemData.id).date;
    }
    else if (MLDM_CONVERSATION)
    {
        return getConversationHeader(stItemData.id).date;
    }
    return DEFAULT_VALUE_ZERO;
}

QString CMemoryDBManager::getSubject(const MailListItemData & stItemData)
{
    if (MLIT_MAIL == stItemData.itemType)
    {
        return getMailHeader(stItemData.id).Subject;
    }
    else if (MLIT_CONVERSATION == stItemData.itemType)
    {
        return getConversationHeader(stItemData.id).Subject;
    }
    else if (MLIT_GROUP == stItemData.itemType)
    {
        return getGroupHeader(stItemData.id).name;
    }
    return "";
}

MailConversationInfo CMemoryDBManager::getConversationHeader(uint32_t converId)
{
    QMutexLocker locker(&m_converMutex);
    if(m_mapMailConversationData.contains(converId))
        return m_mapMailConversationData[converId];
    MailConversationInfo stMailConversationInfo;
    return stMailConversationInfo;
    
}


bool CMemoryDBManager::deleteMailRecord(uint64_t mailId, uint32_t folderId)
{
    QMutexLocker locker(&m_mailMutex); //外面加个括号防止重新生成时死锁
    for (int i = 0; i < m_mapMailMemoryData[folderId].vecMailHeaderDatas.size(); ++i)
    {
        if (m_mapMailMemoryData[folderId].vecMailHeaderDatas.at(i).id == mailId)
        {
            m_mapMailMemoryData[folderId].vecMailHeaderDatas.erase(m_mapMailMemoryData[folderId].vecMailHeaderDatas.begin() + i);
            break;
        }
    }
    return true;
}

bool CMemoryDBManager::addMailRecord(MailHeaderInfo&  stMailInfo)
{
    QMutexLocker locker(&m_mailMutex);
    m_mapMailMemoryData[stMailInfo.folderId].vecMailHeaderDatas.push_back(stMailInfo);
    addConversationMail(stMailInfo.conversationId, stMailInfo.id);
    return true;
}

bool CMemoryDBManager::addConversation(const MailConversationInfo & stMailConversationInfo)
{
    QMutexLocker locker(&m_converMutex);
    m_mapMailConversationData[stMailConversationInfo.id] = stMailConversationInfo;
    return true;
}


bool CMemoryDBManager::addConversationMail(uint32_t converId, uint64_t mailId)
{
    QMutexLocker locker(&m_converMutex);
    m_mapMailConversationData[converId].conversationMailIds.insert(mailId);
    return true;
}


MailGroupInfo CMemoryDBManager::getGroupHeader(uint32_t groupId)
{
    QMutexLocker locker(&m_groupMutex);
    if (m_mapMailGroupData.contains(groupId))
    {
        return m_mapMailGroupData[groupId];
    }
    MailGroupInfo stMailGroupInfo;
    return stMailGroupInfo;
}

MailGroupInfo CMemoryDBManager::getGroupHeader(QString groupName)
{
    MailGroupInfo stMailGroupInfo;
    {
        QMutexLocker locker(&m_groupMutex);
        stMailGroupInfo.name = groupName;
        uint32_t groupId = existGroup(stMailGroupInfo);
        if (groupId != DEFAULT_VALUE_ZERO)
        {
            return m_mapMailGroupData[groupId];
        }
    }
    return addGroup(stMailGroupInfo);
}

MailGroupInfo CMemoryDBManager::addGroup(MailGroupInfo & stMailGroupInfo)
{
    QMutexLocker locker(&m_groupMutex);
    uint32_t groupId = existGroup(stMailGroupInfo);
    if (groupId != DEFAULT_VALUE_ZERO)
    {
        return m_mapMailGroupData[groupId];
    }
    stMailGroupInfo.id = m_groupId++;
    m_mapMailGroupData[stMailGroupInfo.id] = stMailGroupInfo;
    return m_mapMailGroupData[stMailGroupInfo.id];
}

uint32_t CMemoryDBManager::existGroup(const MailGroupInfo & stMailGroupInfo)
{
    QMapIterator<uint32_t, MailGroupInfo> iter(m_mapMailGroupData);
    while (iter.hasNext()) {
        iter.next();
        if (iter.value().name == stMailGroupInfo.name)
        {
            return iter.key();
        }
    }
    return DEFAULT_VALUE_ZERO;
}

void CMemoryDBManager::clearGroup()
{
    QMutexLocker locker(&m_groupMutex);
    m_mapMailGroupData.clear();
    m_groupId = 1;
}
