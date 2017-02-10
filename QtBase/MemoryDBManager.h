#ifndef MEMORYDBMANAGER_H
#define MEMORYDBMANAGER_H
#include "dataDefine.h"

class CMemoryDBManager
{
    friend class TreeMailModel;
public:
    CMemoryDBManager();
    ~CMemoryDBManager();

    static CMemoryDBManager* instance();

public:
    MailHeaderInfo getMailHeader(uint64_t mailId);

public:
    void init();

private:
    //QList<MailHeaderInfo> m_listMemMailHeaders;
    QMap<uint32_t, MemoryMailData> m_mapMailMemoryData;
    QMutex  m_mailMutex;

    QList<MailConversationInfo> m_listMemMailConversations;
    
};

#endif // MEMORYDBMANAGER_H