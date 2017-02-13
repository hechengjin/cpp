#ifndef MAILSORTFILTERPROXYMODEL_H
#define MAILSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class QMailSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    QMailSortFilterProxyModel(QObject *parent = NULL);
    ~QMailSortFilterProxyModel();
    static QMailSortFilterProxyModel* instance();

protected:
    virtual bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;
private:
    
};

#endif // MAILSORTFILTERPROXYMODEL_H
