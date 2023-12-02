#ifndef STOZAPRIKAZ_H
#define STOZAPRIKAZ_H

#include <QGraphicsItem>

class stozaprikaz : public QGraphicsItem
{
public:
    stozaprikaz();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // STOZAPRIKAZ_H
