#ifndef QMAILTREEVIEW_H
#define QMAILTREEVIEW_H

#include <QTreeView>
#include "dataDefine.h"

class QMailTreeView : public QTreeView
{
    Q_OBJECT

public:
    QMailTreeView(QWidget *parent);
    ~QMailTreeView();
protected:
    void init();
    void signalSlotConnection();

signals:
    void signalMailSelectionChanged(const MailListSelectData & stMailListSelectData);
protected slots:
    void slotCustomContextMenu(const QPoint &pos);
    void slotDeleteMailClicked();
    void slotEntered(const QModelIndex &index);
    void slotClicked(const QModelIndex &index);
    void onRefreshAccountMails();
private:
    
};

#endif // QMAILTREEVIEW_H
