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
    for (int i = 0; i < 10; i++) //初始化邮件数据
    {
        MailHeaderTable stMailHeaderInfo;
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
        if ( i>=2 && i<=5)
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
        if (i == 2)
        {
            stMailHeaderInfo.flags |= MF_Stick;
        }
        //stMailHeaderInfo.keyLocal = getKeyLocal(stMailHeaderInfo);
        m_mapMailMemoryData.insert(stMailHeaderInfo.id, stMailHeaderInfo);
    }
#pragma endregion 初始化邮件

#pragma region 初始化会话数据
    MailConversationTable stMailConversationInfo;
    stMailConversationInfo = m_mapMailMemoryData[1];
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

    QMapIterator<uint64_t, MailHeaderTable> iter(m_mapMailMemoryData);
    while (iter.hasNext())
    {
        iter.next();
        if (iter.value().conversationId == 1)
        {
            m_mapMailConversationData[1].mailIds.insert(iter.value().id);
        }
        else
        {
            m_mapMailConversationData[2].mailIds.insert(iter.value().id);
        }
    }

#pragma endregion 初始化会话数据

    QString consumingTime = " init data consume:" + QString::number(timeConsuming.elapsed());
    qDebug() << consumingTime;
}

MailHeaderTable CMemoryDBManager::getMailHeader(uint64_t mailId)
{
    QMutexLocker locker(&m_mailMutex);
    if(m_mapMailMemoryData.contains(mailId))
        return m_mapMailMemoryData[mailId];
    MailHeaderTable stMailHeaderInfo;
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

MailConversationTable CMemoryDBManager::getConversationHeader(uint32_t converId)
{
    QMutexLocker locker(&m_converMutex);
    if(m_mapMailConversationData.contains(converId))
        return m_mapMailConversationData[converId];
    MailConversationTable stMailConversationInfo;
    return stMailConversationInfo;
    
}


bool CMemoryDBManager::deleteMailRecord(uint64_t mailId, uint32_t folderId)
{
    QMutexLocker locker(&m_mailMutex);
    for (auto it = m_mapMailMemoryData.begin(); it != m_mapMailMemoryData.end(); /* don't increment here */) {
        if (it.value().id == mailId) {
            it = m_mapMailMemoryData.erase(it);
            break;
        }
        else {
            ++it;
        }
    }
    return true;
}

bool CMemoryDBManager::addMailRecord(MailHeaderTable&  stMailInfo)
{
    QMutexLocker locker(&m_mailMutex);
    m_mapMailMemoryData.insert(stMailInfo.id, stMailInfo);
    addConversationMail(stMailInfo.conversationId, stMailInfo.id);
    return true;
}

bool CMemoryDBManager::addConversation(const MailConversationTable & stMailConversationInfo)
{
    QMutexLocker locker(&m_converMutex);
    m_mapMailConversationData[stMailConversationInfo.id] = stMailConversationInfo;
    return true;
}


bool CMemoryDBManager::addConversationMail(uint32_t converId, uint64_t mailId)
{
    QMutexLocker locker(&m_converMutex);
    m_mapMailConversationData[converId].mailIds.insert(mailId);
    return true;
}


MailGroupVTable CMemoryDBManager::getGroupHeader(uint32_t groupId)
{
    QMutexLocker locker(&m_groupMutex);
    if (m_mapMailGroupData.contains(groupId))
    {
        return m_mapMailGroupData[groupId];
    }
    MailGroupVTable stMailGroupInfo;
    return stMailGroupInfo;
}

MailGroupVTable CMemoryDBManager::getGroupHeader(QString groupName)
{
    MailGroupVTable stMailGroupInfo;
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

MailGroupVTable CMemoryDBManager::addGroup(MailGroupVTable & stMailGroupInfo)
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

uint32_t CMemoryDBManager::existGroup(const MailGroupVTable & stMailGroupInfo)
{
    QMapIterator<uint32_t, MailGroupVTable> iter(m_mapMailGroupData);
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
