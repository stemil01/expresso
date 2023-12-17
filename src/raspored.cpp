#include "raspored.h"
#include "sto.h"

Raspored::Raspored(QString text,QList<Sto*> lista)
    :naziv(text),
    _raspored(lista)
{

}

QList<Sto*> Raspored::getItems(){
    return _raspored;
}
