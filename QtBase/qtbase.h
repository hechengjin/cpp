#ifndef QTBASE_H
#define QTBASE_H

#include <QtWidgets/QMainWindow>
#include "ui_qtbase.h"
#include "dataDefine.h"
#include <QList>


#define DATETIME_FORMAT "yyyy-MM-dd hh:mm:ss.zzz"

class QtBase : public QMainWindow
{
    Q_OBJECT

public:
    QtBase(QWidget *parent = 0);
    ~QtBase();

protected:
    void initData();
    void initUI();
private:
    int m_mailListDisplayMode;

private slots:
    void on_charSetTestPushButton_clicked();
    void on_containerPushButton_clicked();
    void on_getCurTimePushButton_clicked();
    void on_toReadTimePushButton_clicked();
    void on_toNumberTimePushButton_clicked();
    void on_bitPushButton_clicked();
    void on_deleteMailPushButton_clicked();
    void on_refreshPushButton_clicked();
    void on_updateMailPushButton_clicked();
    void on_queryPushButton_clicked();
private:
    Ui::QtBaseClass ui;
};

#endif // QTBASE_H
