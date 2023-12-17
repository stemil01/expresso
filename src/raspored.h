#ifndef RASPORED_H
#define RASPORED_H

#include <QString>
#include "sto.h"


class Raspored
{
public:
    Raspored(QString,QList<Sto*>);
    QString naziv;
    QList<Sto*> getItems();

private:
    QList<Sto*> _raspored;
};

#endif // RASPORED_H
