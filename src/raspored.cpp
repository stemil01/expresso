#include "raspored.h"
#include "sto.h"

Raspored::Raspored(QString text,QList<sto*> lista)
    :naziv(text),
    _raspored(lista)
{

}

QList<sto*> Raspored::getItems(){
    return _raspored;
}
