#ifndef QTBASE_H
#define QTBASE_H

#include <QtWidgets/QMainWindow>
#include "ui_qtbase.h"

typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
#define DATETIME_FORMAT "yyyy-MM-dd hh:mm:ss.zzz"

class QtBase : public QMainWindow
{
    Q_OBJECT

public:
    QtBase(QWidget *parent = 0);
    ~QtBase();

private slots:
    void on_charSetTestPushButton_clicked();
    void on_containerPushButton_clicked();
    void on_getCurTimePushButton_clicked();
    void on_toReadTimePushButton_clicked();
    void on_toNumberTimePushButton_clicked();
    void on_bitPushButton_clicked();
private:
    Ui::QtBaseClass ui;
};

#endif // QTBASE_H
