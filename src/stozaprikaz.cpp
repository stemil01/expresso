#include "stozaprikaz.h"
#include <string.h>
#include <QPainter>


stozaprikaz::stozaprikaz(qint32 id)
    :QGraphicsObject(),
    _id(id)
{
}

QRectF stozaprikaz::boundingRect() const
{
    return QRectF(0,0,80,80);
}
void stozaprikaz::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), QColor::fromRgb(128, 128, 128));
    painter->setPen(Qt::white);


    QString tekst;
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, tekst.number(_id));

}

