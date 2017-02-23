/** 
* @file  dataDefine.h
* @brief 程序级数组类型定义
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

#pragma region 常量定义

#define DEFAULT_VALUE_ZERO    0
#define NOT_SET_VALUE    4294967295 //-1 99999999  4294967295


// 定义GB、MB、KB的计算常量
const int GB = 1024 * 1024 * 1024;
const int MB = 1024 * 1024;
const int KB = 1024;


#define MAIL_SIZE_25K (25 * 1024)
#define MAIL_SIZE_100K (100 * 1024)
#define MAIL_SIZE_500K (500 * 1024)
#define MAIL_SIZE_1M (1 * 1024 * 1024)
#define MAIL_SIZE_5M (5 * 1024 * 1024)

#pragma endregion 常量定义





#pragma region 内存与数据库表对应结构定义
/**
*邮件头结构体 ----mail_header
*/
struct MailHeaderTable
{
    MailHeaderTable()
    :id(DEFAULT_VALUE_ZERO) //64位的整数
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

    uint64_t id; //邮件id或会话id
    uint32_t serverId;
    uint32_t folderId;
    QString messageId;
    QString uid;
    uint32_t indexPop;
    QString keyLocal; //MD5值
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

#pragma endregion 内存与数据库表对应结构定义

#pragma region 内存数据


/**
* 邮件标志位
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
    MF_Stick = 0x00080000   //邮件置顶
};


//struct MemoryMailData
//{
//    MemoryMailData()
//    {
//    }
//
//    //uint32_t latestTime; //动态算出来
//    //uint32_t oldestTime;  //不用
//    QString listPathName;
//    uint32_t numberOfMessagesOnServer;
//
//    QVector<MailHeaderInfo> vecMailHeaderDatas;
//};

#pragma endregion 内存数据


#pragma region 邮件列表相关定义

/**
* 界面相关角色定义
*/

enum UIRoleDefine
{
    UIROLE_ReadableSize = Qt::UserRole,
    UIROLE_xx
};

enum MailListModelColumnEx {
    //headers << tr("Id") << tr("ItemType") << tr("Priority") << tr("Attachment") << tr("From") << tr("To") << tr("Subject") << tr("Date") << tr("Size") << tr("Folder") << tr("Uid");
    MLMCE_Fold, //折叠占位
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
    MLDM_UNKNOWN = 0, //未知
    MLDM_MAIL,  //邮件模式 只显示邮件
    MLDM_GROUP, //分组模式 分组加邮件
    MLDM_CONVERSATION //会话模式  分组 会话 邮件都显示
};


enum MailListItemType
{
    MLIT_UNKNOWN = 0, //未知
    MLIT_GROUP,  //分组项
    MLIT_CONVERSATION, /*会话*/
    MLIT_MAIL   //邮件
};

/**
*
*/
struct MailListItemData
{
    MailListItemData()
    :id(DEFAULT_VALUE_ZERO) //64位的整数
    , itemType(MLIT_MAIL)
    //, messageDate(NOT_SET_VALUE)
    //, messageSize(NOT_SET_VALUE)
    //, itemType(MLIT_UNKNOWN)
    //, folderId(DEFAULT_VALUE_ZERO)
    {
    }
    int itemType;
    uint64_t id;   //itemType不同代表不同的项id
    //uint64_t messageDate; //邮件时间
    //会话会根据其下的邮件产生一个虚拟的邮件作为会话显示【会话邮件】（其信息来自相关邮件的整合）
    //如：5个标题相同的邮件 新产生一个做为组代表，其下显示五个
    //一个会话下只有一个邮件也会产生一个【会话邮件】其信息和邮件本身相同 点击等同邮件
    //QString name; //分组名 标题名
    //uint64_t newestMailId;
    //uint64_t oldestMailId;
    //messageIds 会话中的所有邮件
    //uint32_t flags; //若为会话，则根据其下所有邮件计算而得，如有一个有附件，则这个会话就有附件
    //uint32_t messageSize; //邮件大小  会话要取和
    //分组时间范围
    //uint64_t startTime; //开始时间
    //uint64_t endTime; //结束时间
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
    : id(DEFAULT_VALUE_ZERO) //64位的整数
    , itemType(MLIT_UNKNOWN)
    {
    }
    int itemType;
    uint64_t id;   //itemType不同代表不同的项id
};

struct MailListSelectData
{
    MailListSelectData()
    {
    }
    QVector<MailListSelectItemData> vecselectItemDatas;
};

#pragma endregion 邮件列表相关定义

#pragma region 查询

enum QueryOptionAttachment
{
    QOA_UNLIMITED = 0, //不限制
    QOA_EXIST,    //有附件
    QOA_WITHOUT // 无附件
};

enum QueryOptionTime
{
    QOT_UNLIMITED = 0, //不限制
    QOT_TODAY,    //今天
    QOT_IN3DAYS,    //三天内
    QOT_INAWIIK,    //一周内
    QOT_INAMONTH,    //一个月内
    QOT_INAYEAR,    //一年内
    QOT_SPECIFY    //自定义
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
    bool query;//是否通过点查询按钮获取的数据

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
    //uint64_t date; //时间
    //uint32_t messageSize; //大小
    bool operator == (const QuerySummaryInfo &right) const
    {
        return (id == right.id/* && date == right.date && messageSize == right.messageSize*/);
    }
};


/**
* 查询标志位
*/
enum QueryMailFlag : uint32_t
{
    QMF_NONE = 0x00000000,
    QMF_FOLDER = 0x00000001,  //邮件夹查询条件判断
    QMF_SUBJECT = 0x00000002, //标题
    QMF_AUTHOR = 0x00000004, //发件人
    QMF_RECIPIENTS = 0x00000008, //收件人
    QMF_TIME = 0x00000010, //时间
    QMF_NoSync = 0x00000020,
    QMF_CacheData = 0x00000040,
    QMF_Offline = 0x0000080,
    QMF_Queued = 0x00000100,
    QMF_Forwarded = 0x00000200,
    QMF_New = 0x00000400,
    QMF_MDNReportNeeded = 0x00000800,
    QMF_MDNReportSent = 0x00001000,
    QMF_Template = 0x00002000,
    QMF_ATTACHMENT = 0x00004000,  //附件
    QMF_Preview = 0x00008000,
    QMF_DateOnly = 0x00010000,
    QMF_Deleted = 0x00020000,
    QMF_Hidden = 0x00040000
};

#pragma endregion 查询

#pragma region 函数定义

QString bytesToGBMBKB(qint64 size);
uint qHash(const QuerySummaryInfo key);
#pragma endregion 函数定义


#endif	//__DATADEFINE_H__