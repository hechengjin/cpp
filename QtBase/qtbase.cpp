#include "qtbase.h"
#include <QString>
#include <iostream>
#include <QDebug>
#include <QDateTime>
#include <iomanip>
#include <bitset>
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



struct QuerySummaryInfo
{
    uint64_t mailId;
    uint64_t data;
    uint32_t messageSize; //��С
    bool operator == (const QuerySummaryInfo &right) const
    {
        return (mailId == right.mailId/* && data == right.data*/);
    }
};

uint qHash(const QuerySummaryInfo key)
{
    return key.mailId/* + key.data */; //����������
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
void printfEx(uint64_t data, int width = 20)
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
    cout << setw(width) << dec << data << ' ' << setw(width) << hex << data << endl;
    cout << bitset<64>{data} << endl; // (data)�Ƕ�int��ת��
    //cout << resetiosflags(ios::showbase | ios::uppercase); //ȡ����ָʾ������ֵ�е���ĸ��д���
}

void QtBase::on_bitPushButton_clicked()
{
    int width = 32;
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
    //QSet ���ڹ�ϣ���   STL��set������ı���
    //QSet�ǻ��ڹ�ϣ�㷨�ģ����Ҫ���Զ���Ľṹ��Type�����ṩ��
    //1. bool operator == (const Type &b) const
    //2. һ��ȫ�ֵ�uint qHash(Type key)����
    //QSet�������
   

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
    qDebug() <<  "two set's intersection :";
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
}
