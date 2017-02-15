#ifndef MAILTREEVIEWHEADER_H
#define MAILTREEVIEWHEADER_H
#include "dataDefine.h"
#include <QHeaderView>
class QMailTreeViewHeader : public QHeaderView
{
    Q_OBJECT

public:
    QMailTreeViewHeader(QWidget *parent);
    ~QMailTreeViewHeader();

    //static QMailTreeViewHeader* instance();
protected:
    void mousePressEvent(QMouseEvent *event);
    virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
protected slots:
signals :
    void refreshAccountsMailList();
private:
    int m_preSortColumn;
};

#endif // MAILTREEVIEWHEADER_H
