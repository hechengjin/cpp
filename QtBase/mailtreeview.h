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
private:
    
};

#endif // QMAILTREEVIEW_H
