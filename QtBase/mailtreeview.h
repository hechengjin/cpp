#ifndef QMAILTREEVIEW_H
#define QMAILTREEVIEW_H

#include <QTreeView>
#include "dataDefine.h"
class QMailTreeViewHeader;

class QMailTreeView : public QTreeView
{
    Q_OBJECT

public:
    QMailTreeView(QWidget *parent);
    ~QMailTreeView();

public:
    void setDisplayMode(int displayMode);
    void saveStatusInfo();
    void recoveryStatusInfo();
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
    QMailTreeViewHeader * m_pMailTreeViewHeader;
    QItemSelection      m_itemSelection;
    MailListItemData m_selMailListItemData;
};

#endif // QMAILTREEVIEW_H
