#include "dataDefine.h"

QString bytesToGBMBKB(qint64 size)
{
    if (size / GB >= 1)
        return QString("%1 GB").arg(QString::number(size / (float)GB, 'f', 2));
    else if (size / MB >= 1)
        return QString("%1 MB").arg(QString::number(size / (float)MB, 'f', 2));
    else if (size / KB >= 1)
        return QString("%1 KB").arg(QString::number(size / (float)KB, 'f', 2));
    else
        return QString("%1 Bytes").arg(size);
}

uint qHash(const QuerySummaryInfo key)
{
    return key.id/* + key.date*/; //°´ÈÕÆÚÅÅĞò
}