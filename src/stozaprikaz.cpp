#include "stozaprikaz.h"
#include <string.h>
#include <QPainter>

stozaprikaz::stozaprikaz()
{

}

QRectF stozaprikaz::boundingRect() const
{
    return QRectF(0,0,50,50);
}
void stozaprikaz::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), QColor::fromRgb(128, 128, 128));
    painter->setPen(Qt::white);


    const auto tekst = QString("sto");
    painter->drawText(boundingRect(), Qt::AlignHCenter, tekst);

}
