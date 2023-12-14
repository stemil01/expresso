#include "tabla.h"
#include "sto.h"

class GlavniMeni;

Tabla::Tabla(QObject *parent)
    : QGraphicsScene(parent)
{

}

void Tabla::postaviSto(sto *s)
{
    pozicionirajSto(s);
    s->setFlag(QGraphicsItem::ItemIsMovable);
}

void Tabla::pozicionirajSto(sto *s)
{
    // auto sirina = static_cast<int>(this->width());
    const auto sirina = 1250;
    const auto xOffset = 50;
    const auto yOffset = 50;

    const auto x = (250 * (s->getId()-1)) % sirina;
    const auto y = 240 * ((250 * (s->getId()-1)) / sirina);

    s->setPos(x + xOffset,y + yOffset);
}


