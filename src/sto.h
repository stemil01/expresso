#ifndef STO_H
#define STO_H

#include <QGraphicsObject>

class sto : public QGraphicsObject
{
public:
    sto(qint32 id);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    qint32 getId();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
private:
    qint32 _id;
    QPointF _lastPos;

};

#endif // STO_H
