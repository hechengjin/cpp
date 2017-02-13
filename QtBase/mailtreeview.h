#ifndef QMAILTREEVIEW_H
#define QMAILTREEVIEW_H

#include <QTreeView>

class QMailTreeView : public QTreeView
{
    Q_OBJECT

public:
    QMailTreeView(QWidget *parent);
    ~QMailTreeView();
protected:
    void init();
    void signalSlotConnection();


protected slots:
    void slotCustomContextMenu(const QPoint &pos);
    void slotDeleteMailClicked();
    void slotEntered(const QModelIndex &index);
private:
    
};

#endif // QMAILTREEVIEW_H
