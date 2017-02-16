#ifndef MAILITEMDELEGATE_H
#define MAILITEMDELEGATE_H

#include <QStyledItemDelegate>

class QMailItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    QMailItemDelegate(QObject *parent);
    ~QMailItemDelegate();


public:
    // painting
    void paint(QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const Q_DECL_OVERRIDE;
protected:
    void paintGrid(QPainter *painter, const QRect &rect) const;

private:
};

#endif // MAILITEMDELEGATE_H
