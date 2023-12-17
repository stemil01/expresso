#ifndef RASPORED_H
#define RASPORED_H

#include <QString>
#include "sto.h"


class Raspored
{
public:
    Raspored(QString,QList<sto*>);
    QString naziv;
    QList<sto*> getItems();

private:
    QList<sto*> _raspored;
};

#endif // RASPORED_H
