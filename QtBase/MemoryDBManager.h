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
    QList<MailHeaderInfo> m_listMemMailHeaders;
    QList<MailConversationInfo> m_listMemMailConversations;
    QMutex  m_mailMutex;
};

#endif // MEMORYDBMANAGER_H