#include "sto.h"
#include <string.h>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

sto::sto(qint32 id)
    :QGraphicsObject(),
    _id(id)
{
    setFlags(GraphicsItemFlag::ItemIsSelectable | GraphicsItemFlag::ItemIsMovable);
}

QRectF sto::boundingRect() const
{
    return QRectF(0,0,150,150);
}
void sto::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), QColor::fromRgb(128, 128, 128));
    painter->setPen(Qt::white);


    QString tekst;
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, tekst.number(_id));

    if(this->isSelected())
    {
        painter->setPen(QPen(Qt::yellow, 3));
        painter->setBrush(Qt::NoBrush);

        painter->drawRect(boundingRect());
    }

}

void sto::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    _lastPos = event->pos();
    QGraphicsItem::mousePressEvent(event);
}

void sto::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QPointF newPos = event->pos();
    QPointF delta = newPos - _lastPos;
    QPointF newPosScene = this->scenePos() + delta;
    _lastPos = newPos;
    QGraphicsItem::mouseMoveEvent(event);
}

void sto::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem::mouseReleaseEvent(event);
}

qint32 sto::getId(){
    return _id;
}

void sto::setId(qint32 id){
    _id = id;
}
