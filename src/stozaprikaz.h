#ifndef STOZAPRIKAZ_H
#define STOZAPRIKAZ_H

#include <QGraphicsObject>

class stozaprikaz : public QGraphicsObject
{
public:
    stozaprikaz(qint32 id);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    qint32 _id;


};

#endif // STOZAPRIKAZ_H
