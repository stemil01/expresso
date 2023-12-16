#ifndef STO_H
#define STO_H

#include <QGraphicsObject>

class sto : public QGraphicsObject
{
public:
    sto();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    static qint32 getNextId();
    qint32 getId();
    static void resetNextId();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
private:
    qint32 _id;
    static qint32 _nextId;
    QPointF _lastPos;

};

#endif // STO_H
