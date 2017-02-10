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

    for (int i = 0; i < 10; i++) //初始化邮件数据
    {
        MailHeaderInfo stMailHeaderInfo;
        stMailHeaderInfo.Id = i + 1;
        stMailHeaderInfo.serverId = oneServerId;
        stMailHeaderInfo.folderId = inboxFolderId;
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
        m_listMemMailHeaders.push_back(stMailHeaderInfo);
    }
#pragma endregion 初始化邮件

#pragma region 初始化会话数据
    MailConversationInfo stMailConversationInfo;
    stMailConversationInfo = m_listMemMailHeaders.at(0);
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
    for (int i = 0; i < m_listMemMailHeaders.size(); i++)
    {
        if (m_listMemMailHeaders.at(i).Id == mailId)
        {
            return m_listMemMailHeaders.at(i);
        }
    }
    MailHeaderInfo stMailHeaderInfo;
    return stMailHeaderInfo;
}