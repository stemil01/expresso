#include "raspored.h"
#include "sto.h"

#include <QVariant>
#include <QVariantMap>
#include <QVariantList>

Raspored::Raspored(const QString& rasporedName)
    : m_naziv(rasporedName)
{

}

Raspored::~Raspored()
{
    qDeleteAll(m_raspored);
}

QList<Sto*> Raspored::getItems(){
    return m_raspored;
}

QVariant Raspored::toVariant() const
{
    QVariantMap map;
    map.insert("naziv", m_naziv);
    QVariantList raspored;
    for (const auto& sto : m_raspored) {
        raspored.append(sto->toVariant());
    }
    map.insert("raspored", raspored);
    return map;
}

void Raspored::fromVariant(const QVariant& variant)
{
    const auto map = variant.toMap();
    m_naziv = map.value("naziv").toString();

    qDeleteAll(m_raspored);
    m_raspored.clear();

    const auto raspored = map.value("raspored").toList();
    for (const auto& stoVariant : raspored) {
        Sto *sto = new Sto();
        sto->fromVariant(stoVariant);
        m_raspored.append(sto);
    }
}


Sto* Raspored::addSto()
{
    Sto *sto = new Sto();
    m_raspored.append(sto);
    return sto;
}

void Raspored::removeSto(qint32 idStola)
{

}

void Raspored::clearSto()
{
    qDeleteAll(m_raspored);
    m_raspored.clear();
    Sto::resetNextId();
}
