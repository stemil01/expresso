#ifndef RASPORED_H
#define RASPORED_H

#include <QString>
#include <QGraphicsObject>


class Raspored
{
public:
    Raspored(QString,QList<QGraphicsItem*>);
    QString naziv;
    QList<QGraphicsItem*> getItems();

private:
    QList<QGraphicsItem*> _raspored;
};

#endif // RASPORED_H
