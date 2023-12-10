#ifndef STOZAPRIKAZ_H
#define STOZAPRIKAZ_H

#include <QGraphicsObject>

class stozaprikaz : public QGraphicsObject
{
public:
    stozaprikaz(qint32 id);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
private:
    qint32 _id;
    QPointF _lastPos;

};

#endif // STOZAPRIKAZ_H
