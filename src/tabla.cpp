#include "tabla.h"
#include "stozaprikaz.h"
#include "glavnimeni.h"

Tabla::Tabla(QObject *parent)
    : QGraphicsScene(parent)
{

}

void Tabla::postaviSto(stozaprikaz *s)
{
    if(brStolova<16){
        brStolova++;
        pozicionirajSto(s);
         s->setFlag(QGraphicsItem::ItemIsMovable);
    }
}

void Tabla::pozicionirajSto(stozaprikaz *s)
{
    const auto tableWidth = static_cast<int>(this->width());

    const auto x = (150 * (brStolova-1)) % tableWidth;
    const auto y = 140 * ((150 * (brStolova-1)) / tableWidth);

    s->setPos(x,y);
}


