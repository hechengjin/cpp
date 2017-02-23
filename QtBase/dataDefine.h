/** 
* @file  dataDefine.h
* @brief �����������Ͷ���
*
* Copyright (c) 2016
*
* kingsoft
*
* @author 
*
* @version 
*
*/

#ifndef __DATADEFINE_H__
#define __DATADEFINE_H__
#include <QString>
#include <QList>
#include <QVector>
#include <QMap>
#include <QSet>
#include "dataType.h"
#include <QTime>

#pragma region ��������

#define DEFAULT_VALUE_ZERO    0
#define NOT_SET_VALUE    4294967295 //-1 99999999  4294967295


// ����GB��MB��KB�ļ��㳣��
const int GB = 1024 * 1024 * 1024;
const int MB = 1024 * 1024;
const int KB = 1024;


#define MAIL_SIZE_25K (25 * 1024)
#define MAIL_SIZE_100K (100 * 1024)
#define MAIL_SIZE_500K (500 * 1024)
#define MAIL_SIZE_1M (1 * 1024 * 1024)
#define MAIL_SIZE_5M (5 * 1024 * 1024)

#pragma endregion ��������





#pragma region �ڴ������ݿ���Ӧ�ṹ����
/**
*�ʼ�ͷ�ṹ�� ----mail_header
*/
struct MailHeaderTable
{
    MailHeaderTable()
    :id(DEFAULT_VALUE_ZERO) //64λ������
    , serverId(DEFAULT_VALUE_ZERO)
    , folderId(DEFAULT_VALUE_ZERO)
    , indexPop(NOT_SET_VALUE)
    , conversationId(DEFAULT_VALUE_ZERO)
    , date(NOT_SET_VALUE)
    , messageSize(NOT_SET_VALUE)
    , flags(NOT_SET_VALUE)
    , priority(NOT_SET_VALUE)
    , messageId("")
    {
    }

    uint64_t id; //�ʼ�id��Ựid
    uint32_t serverId;
    uint32_t folderId;
    QString messageId;
    QString uid;
    uint32_t indexPop;
    QString keyLocal; //MD5ֵ
    uint32_t conversationId;
    uint64_t date;
    uint32_t messageSize;
    QString Subject;
    QString author;
    QString recipients;
    QString ccList;
    QString bccList;
    uint32_t flags;
    QString referenceInfo;
    uint32_t priority;
    QString remarks;
    QString changeKey;
    void clear()
    {
        id = DEFAULT_VALUE_ZERO;
        Subject.clear();
        author.clear();
        recipients.clear();
        ccList.clear();
        bccList.clear();
        changeKey.clear();
    }

    MailHeaderTable& operator=(const MailHeaderTable &rhs)
    {
        id = rhs.id;
        serverId = rhs.serverId;
        folderId = rhs.folderId;
        messageId = rhs.messageId;
        uid = rhs.uid;
        keyLocal = rhs.keyLocal;
        indexPop = rhs.indexPop;
        conversationId = rhs.conversationId;
        date = rhs.date;
        messageSize = rhs.messageSize;
        Subject = rhs.Subject;
        author = rhs.author;
        recipients = rhs.recipients;
        ccList = rhs.ccList;
        bccList = rhs.bccList;
        flags = rhs.flags;
        referenceInfo = rhs.referenceInfo;
        priority = rhs.priority;
        remarks = rhs.remarks;
        changeKey = rhs.changeKey;
        return *this;
    }
};

struct MailConversationTable : MailHeaderTable
{
    MailConversationTable()
    :MailHeaderTable() 
    {
    }
    QSet<uint64_t> mailIds;
    uint64_t newestMailId;
    uint64_t oldestMailId;
    MailConversationTable& operator=(const MailHeaderTable &rhs)
    {
        id = rhs.id;
        serverId = rhs.serverId;
        folderId = rhs.folderId;
        messageId = rhs.messageId;
        uid = rhs.uid;
        keyLocal = rhs.keyLocal;
        indexPop = rhs.indexPop;
        conversationId = rhs.conversationId;
        date = rhs.date;
        messageSize = rhs.messageSize;
        Subject = rhs.Subject;
        author = rhs.author;
        recipients = rhs.recipients;
        ccList = rhs.ccList;
        bccList = rhs.bccList;
        flags = rhs.flags;
        referenceInfo = rhs.referenceInfo;
        priority = rhs.priority;
        remarks = rhs.remarks;
        changeKey = rhs.changeKey;
        return *this;
    }
};


struct MailGroupVTable
{
    MailGroupVTable()
    {
    }
    uint32_t id;
    QString name;
};

#pragma endregion �ڴ������ݿ���Ӧ�ṹ����

#pragma region �ڴ�����


/**
* �ʼ���־λ
*/
enum MailFlag : uint32_t
{
    MF_Read = 0x00000001,
    MF_Replied = 0x00000002,
    MF_Starred = 0x00000004,
    MF_Expunged = 0x00000008,
    MF_LocalKeep = 0x00000010,
    MF_NoSync = 0x00000020,
    MF_CacheData = 0x00000040,
    MF_Offline = 0x0000080,
    MF_Queued = 0x00000100,
    MF_Forwarded = 0x00000200,
    MF_New = 0x00000400,
    MF_MDNReportNeeded = 0x00000800,
    MF_MDNReportSent = 0x00001000,
    MF_Template = 0x00002000,
    MF_Attachment = 0x00004000,
    MF_Preview = 0x00008000,
    MF_DateOnly = 0x00010000,
    MF_Deleted = 0x00020000,
    MF_Hidden = 0x00040000,
    MF_Stick = 0x00080000   //�ʼ��ö�
};


//struct MemoryMailData
//{
//    MemoryMailData()
//    {
//    }
//
//    //uint32_t latestTime; //��̬�����
//    //uint32_t oldestTime;  //����
//    QString listPathName;
//    uint32_t numberOfMessagesOnServer;
//
//    QVector<MailHeaderInfo> vecMailHeaderDatas;
//};

#pragma endregion �ڴ�����


#pragma region �ʼ��б���ض���

/**
* ������ؽ�ɫ����
*/

enum UIRoleDefine
{
    UIROLE_ReadableSize = Qt::UserRole,
    UIROLE_xx
};

enum MailListModelColumnEx {
    //headers << tr("Id") << tr("ItemType") << tr("Priority") << tr("Attachment") << tr("From") << tr("To") << tr("Subject") << tr("Date") << tr("Size") << tr("Folder") << tr("Uid");
    MLMCE_Fold, //�۵�ռλ
    MLMCE_Id,
    MLMCE_ItemType,
    MLMCE_Priority,
    MLMCE_Attachment,
    MLMCE_From,
    MLMCE_To,
    MLMCE_Subject,
    MLMCE_Date,
    MLMCE_Size,
    MLMCE_Folder,
    MLMCE_Uid,
    MLMCE_Count
};

enum MailListDisplayMode
{
    MLDM_UNKNOWN = 0, //δ֪
    MLDM_MAIL,  //�ʼ�ģʽ ֻ��ʾ�ʼ�
    MLDM_GROUP, //����ģʽ ������ʼ�
    MLDM_CONVERSATION //�Ựģʽ  ���� �Ự �ʼ�����ʾ
};


enum MailListItemType
{
    MLIT_UNKNOWN = 0, //δ֪
    MLIT_GROUP,  //������
    MLIT_CONVERSATION, /*�Ự*/
    MLIT_MAIL   //�ʼ�
};

/**
*
*/
struct MailListItemData
{
    MailListItemData()
    :id(DEFAULT_VALUE_ZERO) //64λ������
    , itemType(MLIT_MAIL)
    //, messageDate(NOT_SET_VALUE)
    //, messageSize(NOT_SET_VALUE)
    //, itemType(MLIT_UNKNOWN)
    //, folderId(DEFAULT_VALUE_ZERO)
    {
    }
    int itemType;
    uint64_t id;   //itemType��ͬ����ͬ����id
    //uint64_t messageDate; //�ʼ�ʱ��
    //�Ự��������µ��ʼ�����һ��������ʼ���Ϊ�Ự��ʾ���Ự�ʼ���������Ϣ��������ʼ������ϣ�
    //�磺5��������ͬ���ʼ� �²���һ����Ϊ�����������ʾ���
    //һ���Ự��ֻ��һ���ʼ�Ҳ�����һ�����Ự�ʼ�������Ϣ���ʼ�������ͬ �����ͬ�ʼ�
    //QString name; //������ ������
    //uint64_t newestMailId;
    //uint64_t oldestMailId;
    //messageIds �Ự�е������ʼ�
    //uint32_t flags; //��Ϊ�Ự����������������ʼ�������ã�����һ���и�����������Ự���и���
    //uint32_t messageSize; //�ʼ���С  �ỰҪȡ��
    //����ʱ�䷶Χ
    //uint64_t startTime; //��ʼʱ��
    //uint64_t endTime; //����ʱ��
    //uint32_t folderId;

    //bool operator == (const MailListItemData &right) const
    //{
    //    return (mailId == right.mailId);
    //}
};


/**
*
*/
struct MailListSelectItemData
{
    MailListSelectItemData()
    : id(DEFAULT_VALUE_ZERO) //64λ������
    , itemType(MLIT_UNKNOWN)
    {
    }
    int itemType;
    uint64_t id;   //itemType��ͬ����ͬ����id
};

struct MailListSelectData
{
    MailListSelectData()
    {
    }
    QVector<MailListSelectItemData> vecselectItemDatas;
};

#pragma endregion �ʼ��б���ض���

#pragma region ��ѯ

enum QueryOptionAttachment
{
    QOA_UNLIMITED = 0, //������
    QOA_EXIST,    //�и���
    QOA_WITHOUT // �޸���
};

enum QueryOptionTime
{
    QOT_UNLIMITED = 0, //������
    QOT_TODAY,    //����
    QOT_IN3DAYS,    //������
    QOT_INAWIIK,    //һ����
    QOT_INAMONTH,    //һ������
    QOT_INAYEAR,    //һ����
    QOT_SPECIFY    //�Զ���
};


struct QueryConditions
{
    QueryConditions()
    : folderId(DEFAULT_VALUE_ZERO)
    , query(false)
    , attachmentOption(QOA_UNLIMITED)
    , timeOption(QOT_UNLIMITED)
    , displayMode(MLDM_CONVERSATION)
    , needAsynQuery(false)
    , curSortColumn(MLMCE_Date)
    {
    }
    uint32_t folderId;
    QString subject;
    QString content;
    QSet<uint64_t> authors;
    QSet<uint64_t> recipients;
    int attachmentOption;
    QString attachmentName;
    int timeOption;
    uint64_t startTime;
    uint64_t endTime;
    int displayMode;
    int curSortColumn;
    bool needAsynQuery;
    bool query;//�Ƿ�ͨ�����ѯ��ť��ȡ������

    void reset()
    {
        folderId = DEFAULT_VALUE_ZERO;
    }
};


struct QuerySummaryInfo
{
    QuerySummaryInfo()
    : id(DEFAULT_VALUE_ZERO)
    , conversationId(DEFAULT_VALUE_ZERO)
    //, date(DEFAULT_VALUE_ZERO)
    //, messageSize(DEFAULT_VALUE_ZERO)
    {
    }
    uint64_t id;
    uint32_t conversationId;
    //uint64_t date; //ʱ��
    //uint32_t messageSize; //��С
    bool operator == (const QuerySummaryInfo &right) const
    {
        return (id == right.id/* && date == right.date && messageSize == right.messageSize*/);
    }
};


/**
* ��ѯ��־λ
*/
enum QueryMailFlag : uint32_t
{
    QMF_NONE = 0x00000000,
    QMF_FOLDER = 0x00000001,  //�ʼ��в�ѯ�����ж�
    QMF_SUBJECT = 0x00000002, //����
    QMF_AUTHOR = 0x00000004, //������
    QMF_RECIPIENTS = 0x00000008, //�ռ���
    QMF_TIME = 0x00000010, //ʱ��
    QMF_NoSync = 0x00000020,
    QMF_CacheData = 0x00000040,
    QMF_Offline = 0x0000080,
    QMF_Queued = 0x00000100,
    QMF_Forwarded = 0x00000200,
    QMF_New = 0x00000400,
    QMF_MDNReportNeeded = 0x00000800,
    QMF_MDNReportSent = 0x00001000,
    QMF_Template = 0x00002000,
    QMF_ATTACHMENT = 0x00004000,  //����
    QMF_Preview = 0x00008000,
    QMF_DateOnly = 0x00010000,
    QMF_Deleted = 0x00020000,
    QMF_Hidden = 0x00040000
};

#pragma endregion ��ѯ

#pragma region ��������

QString bytesToGBMBKB(qint64 size);
uint qHash(const QuerySummaryInfo key);
#pragma endregion ��������


#endif	//__DATADEFINE_H__