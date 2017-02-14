#ifndef MEMORYDBMANAGER_H
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
    MailHeaderInfo getMailHeader(uint64_t mailId);
    bool deleteMailRecord(uint64_t mailId, uint32_t folderId = 1);
public:
    void init();

private:
    //QList<MailHeaderInfo> m_listMemMailHeaders;
    QMap<uint32_t, MemoryMailData> m_mapMailMemoryData;
    QMutex  m_mailMutex;

    QList<MailConversationInfo> m_listMemMailConversations;
    
};

#endif // MEMORYDBMANAGER_H