#ifndef STO_H
#define STO_H

#include <QGraphicsObject>
#include "serializable.h"

class Porudzbina;

class Sto : public QGraphicsObject, public Serializable
{
    Q_OBJECT

public:
    Sto();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    static qint32 getNextId();
    qint32 getId();
    static void resetNextId();
    void setPorudzbina(Porudzbina* p);
    bool zauzet = false;

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
private:
    Porudzbina* _p;
    qint32 _id;
    static qint32 _nextId;
    QPointF _lastPos;

};

#endif // STO_H
