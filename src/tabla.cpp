#include "tabla.h"
#include "stozaprikaz.h"
#include "stolovi.h"

Tabla::Tabla(QObject *parent)
    : QGraphicsScene(parent)
{

}

void Tabla::postaviSto(stozaprikaz *s)
{
    brStolova++;
    positionTable(s);
}

void Tabla::positionTable(stozaprikaz *s)
{
    const auto tableWidth = static_cast<int>(this->width());

    const auto x = (100 * (brStolova-1)) % tableWidth;
    const auto y = 100 * ((100 * (brStolova-1)) / tableWidth);

    s->setPos(x,y);
}

