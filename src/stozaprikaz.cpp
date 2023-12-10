#include "stozaprikaz.h"
#include <string.h>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

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

void stozaprikaz::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    _lastPos = event->pos();
    QGraphicsItem::mousePressEvent(event);
}

void stozaprikaz::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QPointF newPos = event->pos();
    QPointF delta = newPos - _lastPos;
    QPointF newPosScene = this->scenePos() + delta;
    _lastPos = newPos;
    QGraphicsItem::mouseMoveEvent(event);
}

void stozaprikaz::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem::mouseReleaseEvent(event);
}
