#include "qtbase.h"
#include <QString>
#include <iostream>
#include <QDebug>
#include <QDateTime>
#include <iomanip>
#include <bitset>
#include "MemoryDBManager.h"
#include "mailtreemodel.h"
#include "mailtreeviewHeader.h"
#include <QSortFilterProxyModel>
#include "mailsortfilterproxymodel.h"

using namespace std;

QtBase::QtBase(QWidget *parent)
    : QMainWindow(parent)
    , m_mailListDisplayMode(MLDM_CONVERSATION)
{
    initData();
    ui.setupUi(this);
    initUI();
    signalSlotConnection();
    
}

QtBase::~QtBase()
{

}

void QtBase::initData()
{
    CMemoryDBManager::instance()->init();
    //ui.mailListTreeView->setModel(TreeMailModel::instance());
    //QSortFilterProxyModel *pProxyModel = new QSortFilterProxyModel(this);
    //pProxyModel->setSourceModel(QMailTreeModel::instance());
    //ui.mailListTreeView->setModel(pProxyModel);
    // ���ÿ�����
    //ui.mailListTreeView->setSortingEnabled(true);
    // ���ð������ڽ�������
    //ui.mailListTreeView->sortByColumn(MLMC_Date, Qt::DescendingOrder);

    //ui.mailListTreeView->setHeader(new QMailTreeViewHeader());
    

    //ui.mailListTreeView->setColumnHidden(MLMC_Priority, true);

    //ui.mailListTreeView->expandAll();
    int xxx;
    xxx++;

}



void QtBase::initUI()
{
    ui.deleteMailLineEdit->setText("10");

    on_queryPushButton_clicked();
}

void QtBase::signalSlotConnection()
{
    connect(ui.mailListTreeView, SIGNAL(signalMailSelectionChanged(const MailListSelectData &)), this, SLOT(onMailListSelectChanged(const MailListSelectData &)), Qt::QueuedConnection);
}


#pragma region �ַ�������

void QtBase::on_charSetTestPushButton_clicked()
{
    //http://www.firemail.wang/forum.php?mod=viewthread&tid=8312
    QString str("����"); //QString�ڲ�ʹ��Unicode�Դ���Ĵ����б��롣
    std::cout << "Straight Output:" << str.data() << endl;
    QByteArray bytes = str.toLocal8Bit();
    std::cout << "Local Output:" << bytes.data() << endl;
    std::cout << "Unicode Output:" << str.unicode() << endl;

    //http://blog.csdn.net/l_andy/article/details/49837253
    //GBK �\>QString
    QString str1 = QString::fromLocal8Bit("����й�");
    //QString �\>GBK
    QByteArray bytes1 = str1.toLocal8Bit();
    const char* gbk = bytes1.data();
    std::cout << gbk;
}


#pragma endregion �ַ�������




#pragma region ʱ�����


void QtBase::on_getCurTimePushButton_clicked()
{
    //QDate now = QDate::currentDate();
    //QDateTime startDate(QDate(now.year(), now.month(), now.day()), QTime(0, 0, 0, 1));
    //QDateTime endDate(QDate(now.year(), now.month(), now.day()), QTime(23, 59, 59, 998));
    QDateTime current_date_time;
    QTime time;
    QDate date;
    current_date_time.setTime(time.currentTime());
    current_date_time.setDate(date.currentDate());
    QString currentDate = current_date_time.toString(DATETIME_FORMAT);
    ui.readTimeLineEdit->setText(currentDate);
    //QDateTime current_date_time = QDateTime::currentDateTime();  
    //QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");

    uint64_t uintDateTime = current_date_time.toTime_t();
    ui.numberTimeLineEdit->setText(QString::number(uintDateTime));
}

void QtBase::on_toReadTimePushButton_clicked()
{
    QDateTime testDateTime;
    uint64_t uintDateTime = ui.numberTimeLineEdit->text().toULongLong();
    testDateTime.setTime_t(uintDateTime);
    QString strDateTime = testDateTime.toString(DATETIME_FORMAT);
    ui.readTimeLineEdit->setText(strDateTime);
}


void QtBase::on_toNumberTimePushButton_clicked()
{
    QString strBuffer;
    QDateTime current_date_time;
    strBuffer = ui.readTimeLineEdit->text();
    current_date_time = QDateTime::fromString(strBuffer, DATETIME_FORMAT);
    uint64_t uintDateTime = current_date_time.toTime_t();
    ui.numberTimeLineEdit->setText(QString::number(uintDateTime));
}


#pragma endregion ʱ�����

#pragma region ��������


// shift-expression << additive-expression  Ҫ��λ����  << ���Ƽ�λ
enum MessageFlag {
    MessageFlagNone = 0,
    MessageFlagSeen = 1 << 0,
    MessageFlagAnswered = 1 << 1,
    MessageFlagFlagged = 1 << 2,
    MessageFlagDeleted = 1 << 3,
    MessageFlagDraft = 1 << 4,
    MessageFlagMDNSent = 1 << 5,
    MessageFlagForwarded = 1 << 6,
    MessageFlagSubmitPending = 1 << 7,
    MessageFlagSubmitted = 1 << 8,
    MessageFlagMaskAll = MessageFlagSeen | MessageFlagAnswered | MessageFlagFlagged |
    MessageFlagDeleted | MessageFlagDraft | MessageFlagMDNSent | MessageFlagForwarded |
    MessageFlagSubmitPending | MessageFlagSubmitted,
};

void printfEx(uint64_t data, int width = 32)
{
    //cout << hex << MessageFlagNone << dec << MessageFlagNone << endl; //���ʮ������
    //cout<<oct<<MessageFlagSeen<<endl; //����˽�����
    //cout << setbase(16) << i << endl; //ʮ��������
    //cout << setbase(8) << i << endl; �˽�����
    //int width = 20;
    //int x = 12, y = 300, z = 1024;
    //cout << setiosflags(ios::showbase | ios::uppercase); //���û�ָʾ������ֵ�е���ĸ��д���
    //cout << dec << x << ' ' << y << ' ' << z << endl; //��ʮ�������    30 300 1024
    //cout << hex << x << ' ' << y << ' ' << z << endl; //��ʮ���������  0X1E 0X12C 0X400
    //cout << oct << x << ' ' << y << ' ' << z << endl; //���˽������    036 0454 02000
    //cout << "------------------" << endl;
    //cout << setiosflags(ios::right);
    //cout << setw(width) << dec << x << ' ' << setw(width) << hex << x << ' ' << setw(width) << oct << x << endl;
    //cout << setw(width) << dec << y << ' ' << setw(width) << hex << y << ' ' << setw(width) << oct << y << endl;
    //cout << setw(width) << dec << z << ' ' << setw(width) << hex << z << ' ' << setw(width) << oct << z << endl;
    //cout << "------------------" << endl;
    //cout << setprecision(2); //������ʾС��λ�� ��������
    //cout << setiosflags(ios::fixed); //������һ��ʹ�ã�����Ч��
    //cout << 2.345 << endl;
    //cout << resetiosflags(ios::showbase | ios::uppercase); //ȡ����ָʾ������ֵ�е���ĸ��д���
    //char bitString[64];
    //itoa(data, bitString, 2);
    cout << setiosflags(ios::showbase | ios::uppercase); //���û�ָʾ������ֵ�е���ĸ��д���
    cout << setiosflags(ios::right);
    cout << setw(width) << dec << data << 'd' << setw(width) << hex << data << endl;
    cout << ' ' << bitset<64>{data} << endl; // (data)�Ƕ�int��ת��
    //cout << resetiosflags(ios::showbase | ios::uppercase); //ȡ����ָʾ������ֵ�е���ĸ��д���
}

void QtBase::on_bitPushButton_clicked()
{
    //int width = 32;
    printfEx(MessageFlagNone);
    printfEx(MessageFlagSeen);
    printfEx(MessageFlagAnswered);
    printfEx(MessageFlagFlagged);
    printfEx(MessageFlagDeleted);
    printfEx(MessageFlagDraft);
    printfEx(MessageFlagMDNSent);
    printfEx(MessageFlagForwarded);
    printfEx(MessageFlagSubmitPending);
    printfEx(MessageFlagSubmitted);
    printfEx(MessageFlagMaskAll);

}

#pragma endregion ��������

#pragma region ��������



//bool compQuerySummaryAsc(const QuerySummaryInfo& qs1, const QuerySummaryInfo& qs2)
//{
//    return qs1.data < qs2.data;
//}
//
//bool compQuerySummaryDesc(const QuerySummaryInfo& qs1, const QuerySummaryInfo& qs2)
//{
//    return qs1.data > qs2.data;
//}

void QtBase::on_containerPushButton_clicked()
{
    //QSet ���ڹ�ϣ���   STL��set������ı���
    //QSet�ǻ��ڹ�ϣ�㷨�ģ����Ҫ���Զ���Ľṹ��Type�����ṩ��
    //1. bool operator == (const Type &b) const
    //2. һ��ȫ�ֵ�uint qHash(Type key)����
    //QSet�������
    /*

    QSet<QuerySummaryInfo> setQuerySummarys;
    QuerySummaryInfo stQuerySummaryInfo;
    stQuerySummaryInfo.mailId = 1;
    stQuerySummaryInfo.data = 1;
    setQuerySummarys.insert(stQuerySummaryInfo);

    stQuerySummaryInfo.mailId = 2;
    stQuerySummaryInfo.data = 2;
    setQuerySummarys.insert(stQuerySummaryInfo);

    stQuerySummaryInfo.mailId = 30;
    stQuerySummaryInfo.data = 3;
    setQuerySummarys.insert(stQuerySummaryInfo);

    stQuerySummaryInfo.mailId = 4;
    stQuerySummaryInfo.data = 400;
    setQuerySummarys.insert(stQuerySummaryInfo);

    stQuerySummaryInfo.mailId = 5;
    stQuerySummaryInfo.data = 5;
    setQuerySummarys.insert(stQuerySummaryInfo);

    stQuerySummaryInfo.mailId = 6;
    stQuerySummaryInfo.data = 3;
    setQuerySummarys.insert(stQuerySummaryInfo);

    stQuerySummaryInfo.mailId = 3; //7
    stQuerySummaryInfo.data = 6;
    setQuerySummarys.insert(stQuerySummaryInfo);


    qDebug() << "set size:" << setQuerySummarys.size();
    //
    QSet<QuerySummaryInfo>::const_iterator iter = setQuerySummarys.constBegin();
    while (iter != setQuerySummarys.constEnd()) {
        qDebug() << (*iter).mailId << " " << (*iter).data;
        ++iter;
    }
    qDebug() << "list size:" << setQuerySummarys.size();
    QList<QuerySummaryInfo> listQuerySummarys = setQuerySummarys.toList();
    for (int i = 0; i < listQuerySummarys.size(); ++i)
    {
        qDebug() << listQuerySummarys.at(i).mailId << " " << listQuerySummarys.at(i).data;
    }


    QuerySummaryInfo stQuerySummaryInfoFind;
    stQuerySummaryInfoFind.mailId = 4;
    stQuerySummaryInfoFind.data = 100;

    QList<QuerySummaryInfo>::iterator i2 = qFind(listQuerySummarys.begin(), listQuerySummarys.end(), stQuerySummaryInfoFind);
    if (i2 != listQuerySummarys.end())
    {
        qDebug() << (*i2).data;
    }

    //����
    //ֱ�Ӳ��뵽 setQuerySummarys ���� Ȼ���ٵ����� setQuerySummarys.toList();

    stQuerySummaryInfo.mailId = 7;
    stQuerySummaryInfo.data = 6;
    setQuerySummarys.insert(stQuerySummaryInfo);
    qDebug() << "after inser";
    iter = setQuerySummarys.constBegin();
    while (iter != setQuerySummarys.constEnd())
    {
        qDebug() << (*iter).mailId << " " << (*iter).data;
        ++iter;
    }

    listQuerySummarys.clear();
    listQuerySummarys = setQuerySummarys.toList();

    qSort(listQuerySummarys.begin(), listQuerySummarys.end(), compQuerySummaryAsc);
    qDebug() << "asc";
    for (int i = 0; i < listQuerySummarys.size(); ++i)
    {
        qDebug() << listQuerySummarys.at(i).mailId << " " << listQuerySummarys.at(i).data;
    }

    qSort(listQuerySummarys.begin(), listQuerySummarys.end(), compQuerySummaryDesc);
    qDebug() << "desc";
    for (int i = 0; i < listQuerySummarys.size(); ++i)
    {
        qDebug() << listQuerySummarys.at(i).mailId << " " << listQuerySummarys.at(i).data;
    }
    //qDebug() << "�������"; ������?
    //for (QList<QuerySummaryInfo>::iterator iter = listQuerySummarys.end(); iter != listQuerySummarys.begin();)
    //{
    //    qDebug() << (*iter).mailId << " " << (*iter).data;
    //}

    //����set�Ľ�������
    qDebug() << "two set's intersection :";
    QSet<QuerySummaryInfo> setQuerySummarys1;
    stQuerySummaryInfo.mailId = 1; //7
    stQuerySummaryInfo.data = 1;
    stQuerySummaryInfo.messageSize = 1;
    setQuerySummarys1.insert(stQuerySummaryInfo);

    QSet<QuerySummaryInfo> setQuerySummarys2;
    stQuerySummaryInfo.mailId = 1; //7
    stQuerySummaryInfo.data = 2;
    stQuerySummaryInfo.messageSize = 2;
    setQuerySummarys2.insert(stQuerySummaryInfo);
    // ���� qHash �� == ������ͬ�����ǲ���Ҫ�Ƴ���
    QSet<QuerySummaryInfo> setQuerySummarys3 = setQuerySummarys1.intersect(setQuerySummarys2);

    //
    QSet<QuerySummaryInfo>::const_iterator iter2 = setQuerySummarys3.constBegin();
    while (iter2 != setQuerySummarys3.constEnd())
    {
        qDebug() << (*iter2).mailId << " " << (*iter2).data << " " << (*iter2).messageSize;
        ++iter2;
    }
    */
}

#pragma endregion ��������


#pragma region �ʼ��б�
void QtBase::on_deleteMailPushButton_clicked()
{
    uint64_t   mailId = ui.deleteMailLineEdit->text().toULongLong();
    MailListItemData stItemData;
    stItemData.id = mailId;
    if (QMailTreeModel::instance()->deleteRecord(stItemData))
    {
        CMemoryDBManager::instance()->deleteMailRecord(mailId);
        onRefreshAccountMails();
    }
}

void QtBase::on_updateMailPushButton_clicked()
{
    uint64_t   mailId = ui.deleteMailLineEdit->text().toULongLong();
    MailListItemData stItemData;
    stItemData.id = mailId;
    //stItemData.name = "ttttttt";
    if (QMailTreeModel::instance()->updateRecord(stItemData))
    {
        onRefreshAccountMails();
    }
}

void QtBase::on_refreshPushButton_clicked()
{
    QMailTreeModel::instance()->clear();
    //QMailSortFilterProxyModel::instance()->clear();
    //QMailTreeModel::instance()->loadData(m_mailListDisplayMode);
    //QMailSortFilterProxyModel::instance()->setSourceModel(QMailTreeModel::instance());
    //ui.mailListTreeView->setModel(QMailSortFilterProxyModel::instance());
    //ui.mailListTreeView->expandAll();
}


void QtBase::on_queryPushButton_clicked()
{
    QueryConditions stQueryConditions;
    stQueryConditions.mailListDisplayMode = MLDM_MAIL;//MLDM_CONVERSATION; MLDM_MAIL
    stQueryConditions.curSortColumn = MLMC_Date;
    stQueryConditions.folderId = ui.folderIdQueryLineEdit->text().toUInt();
    stQueryConditions.query = true;
    //QMailSortFilterProxyModel::instance()->setQueryCondition(stQueryConditions);
    QMailTreeModel::instance()->queryData(stQueryConditions);
    onRefreshAccountMails();
    for (int column = 0; column < QMailTreeModel::instance()->columnCount(); ++column)
        ui.mailListTreeView->resizeColumnToContents(column);
}

void QtBase::on_AddPushButton_clicked()
{
    /*
    QModelIndex index = ui.mailListTreeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui.mailListTreeView->model();

    if (!model->insertRow(index.row() + 1, index.parent()))
        return;

    //updateActions();
    MailListItemData stMailListItemData;
    stMailListItemData.id = 100;
    stMailListItemData.name = ui.titleQueryLineEdit->text();
    QModelIndex child = QMailTreeModel::instance()->index(index.row() + 1, MLMC_Subject, index.parent());
    QMailTreeModel::instance()->setData(child, stMailListItemData);
    */

    uint64_t   mailId = ui.deleteMailLineEdit->text().toULongLong();
    MailHeaderInfo stMailHeaderInfo;
    QDate now = QDate::currentDate();
    QDateTime mailDate(QDate(now.year(), now.month(), now.day()), QTime(10, 10, 10));
    stMailHeaderInfo.date = mailDate.toTime_t();
    stMailHeaderInfo.id = mailId;
    stMailHeaderInfo.folderId = 1;
    stMailHeaderInfo.conversationId = 1;
    stMailHeaderInfo.Subject = ui.titleQueryLineEdit->text();    
    if (CMemoryDBManager::instance()->addMailRecord(stMailHeaderInfo))
    {
        QMailTreeModel::instance()->queryData();
        onRefreshAccountMails();
    }
}

void QtBase::onMailListSelectChanged(const MailListSelectData & stMailListSelectData)
{
    MailListSelectItemData stMailListSelectItemData;
    for (int i = 0; i < stMailListSelectData.vecselectItemDatas.length(); i++)
    {
        stMailListSelectItemData = stMailListSelectData.vecselectItemDatas.at(i);
        if (stMailListSelectItemData.itemType == MLIT_MAIL)
        {
            MailHeaderInfo stMailHeaderInfo = CMemoryDBManager::instance()->getMailHeader(stMailListSelectItemData.id);
            ui.statusLabel->setText(stMailHeaderInfo.Subject);
        }
        else if (stMailListSelectItemData.itemType == MLIT_CONVERSATION)
        {
            ui.statusLabel->setText("conversation");
        }
        else
        {
            ui.statusLabel->setText("group");
        }
        
    }
}

void QtBase::onRefreshAccountMails()
{
    ui.mailListTreeView->expandAll();
}

#pragma endregion �ʼ��б�