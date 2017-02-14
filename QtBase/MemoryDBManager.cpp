#include "MemoryDBManager.h"
#include <QDate>

Q_GLOBAL_STATIC(CMemoryDBManager, memoryDBManager)
CMemoryDBManager *CMemoryDBManager::instance()
{
    return memoryDBManager;
}

CMemoryDBManager::CMemoryDBManager()
{
}

CMemoryDBManager::~CMemoryDBManager()
{
}

void CMemoryDBManager::init()
{

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
        stMailHeaderInfo.Id = i + 1;
        stMailHeaderInfo.serverId = oneServerId;
        if (i%2 == 0)
        {
            stMailHeaderInfo.folderId = inboxFolderId;
        }
        else
            stMailHeaderInfo.folderId = 2;
        
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

        int size = qrand() % 5242880000 + 1; //500M内
        stMailHeaderInfo.messageSize = size;
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
    stMailConversationInfo = m_mapMailMemoryData[inboxFolderId].vecMailHeaderDatas.at(0);
    stMailConversationInfo.Id = 1;
    stMailConversationInfo.Subject = "Conversation Subject: 1";
    int hour = qrand() % 22 + 1;
    int minute = qrand() % 58 + 1;
    int sec = qrand() % 58 + 1;
    QDateTime mailDate(QDate(now.year(), now.month(), now.day()), QTime(hour, minute, sec));
    stMailConversationInfo.date = mailDate.toTime_t();
    for (int i = 1; i <= 5; i++)
    {
        stMailConversationInfo.listConversationMailIds.push_back(i);
    }
    m_listMemMailConversations.push_back(stMailConversationInfo);

    stMailConversationInfo.Subject = "Conversation Subject: 2";
    stMailConversationInfo.Id = 2;
    QDateTime mailDate2(QDate(yesterday.year(), yesterday.month(), yesterday.day()), QTime(hour, minute, sec));
    stMailConversationInfo.date = mailDate2.toTime_t();
    for (int i = 6; i <= 10; i++)
    {
        stMailConversationInfo.listConversationMailIds.push_back(i);
    }
    m_listMemMailConversations.push_back(stMailConversationInfo);

#pragma endregion 初始化会话数据

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
            if (iter.value().vecMailHeaderDatas.at(i).Id == mailId)
            {
                return iter.value().vecMailHeaderDatas.at(i);
            }
        }
        index++;
    }
    MailHeaderInfo stMailHeaderInfo;
    return stMailHeaderInfo;
}

bool CMemoryDBManager::deleteMailRecord(uint64_t mailId, uint32_t folderId)
{
    QMutexLocker locker(&m_mailMutex); //外面加个括号防止重新生成时死锁
    for (int i = 0; i < m_mapMailMemoryData[folderId].vecMailHeaderDatas.size(); ++i)
    {
        if (m_mapMailMemoryData[folderId].vecMailHeaderDatas.at(i).Id == mailId)
        {
            m_mapMailMemoryData[folderId].vecMailHeaderDatas.erase(m_mapMailMemoryData[folderId].vecMailHeaderDatas.begin() + i);
            break;
        }
    }
    return true;
}