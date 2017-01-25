#include "qtbase.h"
#include <QString>
#include <iostream>
#include <QDebug>
#include <QDateTime>
using namespace std;

QtBase::QtBase(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

QtBase::~QtBase()
{

}



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



struct QuerySummaryInfo
{
    uint64_t mailId;
    uint64_t data;
    bool operator == (const QuerySummaryInfo &right) const
    {
        return (mailId == right.mailId && data == right.data);
    }
};

uint qHash(const QuerySummaryInfo key)
{
    return /*key.mailId + */key.data; //按日期排序
}

bool compQuerySummaryAsc(const QuerySummaryInfo& qs1, const QuerySummaryInfo& qs2)
{
    return qs1.data < qs2.data;
}

bool compQuerySummaryDesc(const QuerySummaryInfo& qs1, const QuerySummaryInfo& qs2)
{
    return qs1.data > qs2.data;
}

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

void QtBase::on_containerPushButton_clicked()
{
    //QSet 基于哈希表的   STL的set红黑树的变种
    //QSet是基于哈希算法的，这就要求自定义的结构体Type必须提供：
    //1. bool operator == (const Type &b) const
    //2. 一个全局的uint qHash(Type key)函数
    //QSet有序测试
   

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
}
