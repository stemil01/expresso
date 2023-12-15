#include "raspored.h"

Raspored::Raspored(QString text,QList<QGraphicsItem*> lista)
    :naziv(text),
    _raspored(lista)
{

}

QList<QGraphicsItem*> Raspored::getItems(){
    return _raspored;
}
