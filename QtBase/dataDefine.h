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
#include "dataType.h"

#define DEFAULT_VALUE_ZERO    0
#define NOT_SET_VALUE    4294967295 //-1 99999999  4294967295

#pragma region �ڴ������ݿ���Ӧ�ṹ����
/**
*�ʼ�ͷ�ṹ�� ----mail_header
*/
struct MailHeaderInfo
{
    MailHeaderInfo()
    :Id(DEFAULT_VALUE_ZERO) //64λ������
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

    uint64_t Id; //�ʼ�id��Ựid
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

#pragma endregion �ڴ������ݿ���Ӧ�ṹ����

#pragma region �ʼ��б���ض���
enum MailListModelColumn {
    //headers << tr("Id") << tr("ItemType") << tr("Priority") << tr("Attachment") << tr("From") << tr("To") << tr("Subject") << tr("Date") << tr("Size") << tr("Folder") << tr("Uid");
    MLMC_Fold, //�۵�ռλ
    //MLMC_Fold2, //�۵�ռλ2
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
    , messageDate(NOT_SET_VALUE)
    , messageSize(NOT_SET_VALUE)
    , itemType(MLIT_UNKNOWN)
    {
    }
    int itemType;
    uint64_t id;   //itemType��ͬ����ͬ����id
    uint64_t messageDate; //�ʼ�ʱ��
    //�Ự��������µ��ʼ�����һ��������ʼ���Ϊ�Ự��ʾ���Ự�ʼ���������Ϣ��������ʼ������ϣ�
    //�磺5��������ͬ���ʼ� �²���һ����Ϊ�����������ʾ���
    //һ���Ự��ֻ��һ���ʼ�Ҳ�����һ�����Ự�ʼ�������Ϣ���ʼ�������ͬ �����ͬ�ʼ�
    QString name; //������ ������
    //uint64_t newestMailId;
    //uint64_t oldestMailId;
    //messageIds �Ự�е������ʼ�
    uint32_t flags; //��Ϊ�Ự����������������ʼ�������ã�����һ���и�����������Ự���и���
    uint32_t messageSize; //�ʼ���С  �ỰҪȡ��
    //����ʱ�䷶Χ
    uint64_t startTime; //��ʼʱ��
    uint64_t endTime; //����ʱ��

    //bool operator == (const MailListItemData &right) const
    //{
    //    return (mailId == right.mailId);
    //}
};
#pragma endregion �ʼ��б���ض���

#endif	//__DATADEFINE_H__