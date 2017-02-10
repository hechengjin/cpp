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
#include "dataType.h"

#define DEFAULT_VALUE_ZERO    0
#define NOT_SET_VALUE    4294967295 //-1 99999999  4294967295

#pragma region 内存与数据库表对应结构定义
/**
*邮件头结构体 ----mail_header
*/
struct MailHeaderInfo
{
    MailHeaderInfo()
    :Id(DEFAULT_VALUE_ZERO) //64位的整数
    , serverId(NOT_SET_VALUE)
    , folderId(NOT_SET_VALUE)
    , indexPop(NOT_SET_VALUE)
    , conversationId(NOT_SET_VALUE)
    , date(NOT_SET_VALUE)
    , messageSize(NOT_SET_VALUE)
    , flags(NOT_SET_VALUE)
    , priority(NOT_SET_VALUE)
    , messageId("")
    {
    }

    uint64_t Id; //邮件id或会话id
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
        Id = DEFAULT_VALUE_ZERO;
        Subject.clear();
        author.clear();
        recipients.clear();
        ccList.clear();
        bccList.clear();
        changeKey.clear();
    }

    MailHeaderInfo& operator=(const MailHeaderInfo &rhs)
    {
        Id = rhs.Id;
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

struct MailConversationInfo : MailHeaderInfo
{
    MailConversationInfo()
    :MailHeaderInfo() 
    {
    }
    QList<uint64_t> listConversationMailIds;
    MailConversationInfo& operator=(const MailHeaderInfo &rhs)
    {
        Id = rhs.Id;
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

#pragma endregion 内存与数据库表对应结构定义

#pragma region 邮件列表相关定义
enum MailListModelColumn {
    //headers << tr("Id") << tr("ItemType") << tr("Priority") << tr("Attachment") << tr("From") << tr("To") << tr("Subject") << tr("Date") << tr("Size") << tr("Folder") << tr("Uid");
    MLMC_Fold, //折叠占位
    //MLMC_Fold2, //折叠占位2
    MLMC_Id,
    MLMC_ItemType,
    MLMC_Priority,
    MLMC_Attachment,
    MLMC_From,
    MLMC_To,
    MLMC_Subject,
    MLMC_Date,
    MLMC_Size,
    MLMC_Folder,
    MLMC_Uid,
    MLMC_Count
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
    , messageDate(NOT_SET_VALUE)
    , messageSize(NOT_SET_VALUE)
    , itemType(MLIT_UNKNOWN)
    {
    }
    int itemType;
    uint64_t id;   //itemType不同代表不同的项id
    uint64_t messageDate; //邮件时间
    //会话会根据其下的邮件产生一个虚拟的邮件作为会话显示【会话邮件】（其信息来自相关邮件的整合）
    //如：5个标题相同的邮件 新产生一个做为组代表，其下显示五个
    //一个会话下只有一个邮件也会产生一个【会话邮件】其信息和邮件本身相同 点击等同邮件
    QString name; //分组名 标题名
    //uint64_t newestMailId;
    //uint64_t oldestMailId;
    //messageIds 会话中的所有邮件
    uint32_t flags; //若为会话，则根据其下所有邮件计算而得，如有一个有附件，则这个会话就有附件
    uint32_t messageSize; //邮件大小  会话要取和
    //分组时间范围
    uint64_t startTime; //开始时间
    uint64_t endTime; //结束时间

    //bool operator == (const MailListItemData &right) const
    //{
    //    return (mailId == right.mailId);
    //}
};
#pragma endregion 邮件列表相关定义

#endif	//__DATADEFINE_H__