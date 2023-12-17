#include "raspored.h"
#include "sto.h"
#include <QVariant>
#include <QVariantMap>
#include <QVariantList>

Raspored::Raspored(QString text,QList<Sto*> lista)
    :naziv(text),
    _raspored(lista)
{

}

QList<Sto*> Raspored::getItems(){
    return _raspored;
}

QVariant Raspored::toVariant() const
{
    QVariantMap map;
    QVariantList raspored;
    for (const auto& sto : _raspored) {
        raspored.append(sto->toVariant());
    }
    map.insert("raspored", raspored);
    return map;
}

void Raspored::fromVariant(const QVariant& variant)
{
    const auto map = variant.toMap();
    qDeleteAll(_raspored);
    _raspored.clear();

    const auto raspored = map.value("raspored").toList();
    for (const auto& stoVariant : raspored) {
        Sto *sto = new Sto();
        sto->fromVariant(stoVariant);
        _raspored.append(sto);
    }
}
