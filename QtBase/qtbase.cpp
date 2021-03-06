#include "qtbase.h"
#include <QString>
#include <iostream>
#include <QDebug>
#include <QDateTime>
#include <iomanip>
#include <bitset>
#include <QSet>
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
    // 设置可排序
    //ui.mailListTreeView->setSortingEnabled(true);
    // 设置按照日期降序排列
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


#pragma region 字符集测试

void QtBase::on_charSetTestPushButton_clicked()
{
    //http://www.firemail.wang/forum.php?mod=viewthread&tid=8312
    QString str("汉字"); //QString内部使用Unicode对传入的串进行编码。
    std::cout << "Straight Output:" << str.data() << endl;
    QByteArray bytes = str.toLocal8Bit();
    std::cout << "Local Output:" << bytes.data() << endl;
    std::cout << "Unicode Output:" << str.unicode() << endl;

    //http://blog.csdn.net/l_andy/article/details/49837253
    //GBK ‐>QString
    QString str1 = QString::fromLocal8Bit("你好中国");
    //QString ‐>GBK
    QByteArray bytes1 = str1.toLocal8Bit();
    const char* gbk = bytes1.data();
    std::cout << gbk;
}


#pragma endregion 字符集测试


#pragma region 正则表达式
void QtBase::on_regExpPushButton_clicked()
{
    //QString subject = QString::fromLocal8Bit("回复：转发： Re: Fw:主题回");
    //QString converSubject = subject;
    //converSubject.replace(QRegExp(QString::fromLocal8Bit("回复：|转发：|Re:| Fw:")), "");
    //qDebug() << subject << "  " << converSubject;
    //QString subject2 = "Re: Fw:subject";
    //QString converSubject2 = subject2;
    //converSubject2.replace(QRegExp(QString::fromLocal8Bit("回复：|转发：|Re:| Fw:")), "");
    //qDebug() << subject2 << "  " << converSubject2;

    //QString subject3 = "回复：Re: Fw:subject";
    //QString converSubject3 = subject3;
    //converSubject3.replace(QRegExp("回复：|转发：|Re:| Fw:"), "");
    //qDebug() << subject3 << "  " << converSubject3;

    QString subject_1 = QString::fromLocal8Bit("回复：转发： Re: Fw:主题回");
    QString subject_2 = "回复：转发： Re: Fw:主题回";
    subject_1.replace(QRegExp(QString::fromLocal8Bit("回复：|转发：|Re:| Fw:")), "");
    subject_1.replace(QRegExp("回复：|转发：|Re:| Fw:"), "");

    QString reg = QString::fromLocal8Bit("回复：|转发：|Re:| Fw:");
    subject_2.replace(QRegExp(QString::fromLocal8Bit("回复：|转发：|Re:| Fw:")), "");
    subject_2.replace(QRegExp(reg), "");
    qDebug() << subject_1;
    qDebug() << subject_2;
}
#pragma endregion 正则表达式


#pragma region 时间测试


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


#pragma endregion 时间测试

#pragma region 位操作测试


// shift-expression << additive-expression  要移位的数  << 左移几位
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
    //cout << hex << MessageFlagNone << dec << MessageFlagNone << endl; //输出十进制数
    //cout<<oct<<MessageFlagSeen<<endl; //输出八进制数
    //cout << setbase(16) << i << endl; //十六进制数
    //cout << setbase(8) << i << endl; 八进制数
    //int width = 20;
    //int x = 12, y = 300, z = 1024;
    //cout << setiosflags(ios::showbase | ios::uppercase); //设置基指示符和数值中的字母大写输出
    //cout << dec << x << ' ' << y << ' ' << z << endl; //按十进制输出    30 300 1024
    //cout << hex << x << ' ' << y << ' ' << z << endl; //按十六进制输出  0X1E 0X12C 0X400
    //cout << oct << x << ' ' << y << ' ' << z << endl; //按八进制输出    036 0454 02000
    //cout << "------------------" << endl;
    //cout << setiosflags(ios::right);
    //cout << setw(width) << dec << x << ' ' << setw(width) << hex << x << ' ' << setw(width) << oct << x << endl;
    //cout << setw(width) << dec << y << ' ' << setw(width) << hex << y << ' ' << setw(width) << oct << y << endl;
    //cout << setw(width) << dec << z << ' ' << setw(width) << hex << z << ' ' << setw(width) << oct << z << endl;
    //cout << "------------------" << endl;
    //cout << setprecision(2); //设置显示小数位置 作用永久
    //cout << setiosflags(ios::fixed); //和上面一起使用，才有效果
    //cout << 2.345 << endl;
    //cout << resetiosflags(ios::showbase | ios::uppercase); //取消基指示符和数值中的字母大写输出
    //char bitString[64];
    //itoa(data, bitString, 2);
    cout << setiosflags(ios::showbase | ios::uppercase); //设置基指示符和数值中的字母大写输出
    cout << setiosflags(ios::right);
    cout << setw(width) << dec << data << 'd' << setw(width) << hex << data << endl;
    cout << ' ' << bitset<64>{data} << endl; // (data)是对int的转换
    //cout << resetiosflags(ios::showbase | ios::uppercase); //取消基指示符和数值中的字母大写输出
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

#pragma endregion 位操作测试

#pragma region 容器测试



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
    //QSet 基于哈希表的   STL的set红黑树的变种
    //QSet是基于哈希算法的，这就要求自定义的结构体Type必须提供：
    //1. bool operator == (const Type &b) const
    //2. 一个全局的uint qHash(Type key)函数
    //QSet有序测试
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

    //插入
    //直接插入到 setQuerySummarys 里面 然后再调用下 setQuerySummarys.toList();

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
    //qDebug() << "反向遍历"; 不可行?
    //for (QList<QuerySummaryInfo>::iterator iter = listQuerySummarys.end(); iter != listQuerySummarys.begin();)
    //{
    //    qDebug() << (*iter).mailId << " " << (*iter).data;
    //}

    //两个set的交集计算
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
    // 根据 qHash 和 == 两个共同决定是不是要移除的
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

#pragma endregion 容器测试

#pragma region 字符串处理
void QtBase::on_stringProcePushButton_clicked()
{

    QSet<uint64_t> setMailIds;
    setMailIds.insert(2);
    setMailIds.insert(3);
    QStringList mailIds;
    QSet<uint64_t>::const_iterator iter = setMailIds.constBegin();
    while (iter != setMailIds.constEnd())
    {
        mailIds << QString::number(*iter);
        ++iter;
    }
    //mailIds.removeOne("0");
    QString strMailIds = mailIds.join(",");
    qDebug() << strMailIds;

    QSet<uint64_t> setMailIds2;
    QStringList mailIds2 = strMailIds.split(",");
    foreach(const QString &id, mailIds2) {
        setMailIds2.insert(id.toULongLong());
    }
    int xxx;
    xxx++;
}
#pragma endregion 字符串处理

#pragma region 邮件列表
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
    int displayMode = MLDM_CONVERSATION;//MLDM_CONVERSATION; MLDM_MAIL
    if (displayMode == MLDM_MAIL)
    {
        ui.mailListTreeView->setColumnHidden(MLMCE_Fold, true);
    }
    else
    {
        ui.mailListTreeView->setColumnHidden(MLMCE_Fold, false);
    }
    int sortColumn = MLMCE_Date;
    ui.mailListTreeView->setDisplayMode(displayMode);
    QueryConditions stQueryConditions;
    stQueryConditions.displayMode = displayMode;
    stQueryConditions.curSortColumn = sortColumn;
    stQueryConditions.folderId = ui.folderIdQueryLineEdit->text().toUInt();
    stQueryConditions.query = true;
    //QMailSortFilterProxyModel::instance()->setQueryCondition(stQueryConditions);
    QMailTreeModel::instance()->queryData(stQueryConditions);
    ui.mailListTreeView->sortByColumn(sortColumn, Qt::DescendingOrder);
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
    MailHeaderTable stMailHeaderInfo;
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
            MailHeaderTable stMailHeaderInfo = CMemoryDBManager::instance()->getMailHeader(stMailListSelectItemData.id);
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

void QtBase::on_saveStatusInfoPushButton_clicked()
{
    ui.mailListTreeView->saveStatusInfo();
}

void QtBase::on_recoveryStatusInfoPushButton_clicked()
{
    ui.mailListTreeView->recoveryStatusInfo();
}

#pragma endregion 邮件列表