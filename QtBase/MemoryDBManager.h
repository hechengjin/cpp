﻿#ifndef MEMORYDBMANAGER_H
#define MEMORYDBMANAGER_H
#include "dataDefine.h"

class CMemoryDBManager
{
    friend class QMailTreeModel;
public:
    CMemoryDBManager();
    ~CMemoryDBManager();

    static CMemoryDBManager* instance();

public:
#pragma region 邮件列表
    MailHeaderTable getMailHeader(uint64_t mailId);
    MailConversationTable getConversationHeader(uint32_t converId);
    bool deleteMailRecord(uint64_t mailId, uint32_t folderId = 1);
    bool addMailRecord(MailHeaderTable&  stMailInfo);
    bool addConversation(const MailConversationTable & stMailConversationInfo);
    bool addConversationMail(uint32_t converId, uint64_t mailId);
    uint32_t getFolderId(const MailListItemData & stItemData);
    uint32_t getSize(const MailListItemData & stItemData);
    uint64_t getTime(const MailListItemData & stItemData);
    QString getSubject(const MailListItemData & stItemData);

    MailGroupVTable addGroup(MailGroupVTable & stMailGroupInfo);
    uint32_t existGroup(const MailGroupVTable & stMailGroupInfo);
    MailGroupVTable getGroupHeader(uint32_t groupId);
    MailGroupVTable getGroupHeader(QString groupName);
    void clearGroup();
#pragma endregion 邮件列表

public:
    void init();

private:
    QMap<uint64_t, MailHeaderTable> m_mapMailMemoryData;
    QMutex  m_mailMutex;

    QMap<uint32_t, MailConversationTable> m_mapMailConversationData;
    QMutex  m_converMutex;

    QMap<uint32_t, MailGroupVTable> m_mapMailGroupData;
    uint32_t m_groupId;
    QMutex  m_groupMutex;
    
};

#endif // MEMORYDBMANAGER_H