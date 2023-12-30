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
    map.insert("maxTables", m_max_tables);
    map.insert("currentNumOfTables", currentNumOfTables);
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
    m_max_tables = map.value("maxTables").toInt();
    currentNumOfTables = map.value("currentNumOfTables").toInt();

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
    currentNumOfTables += 1;
    return sto;
}

void Raspored::removeSto(qint32 idStola)
{
    for(auto sto : m_raspored){
        if(sto->getId() == idStola){
            m_raspored.removeOne(sto);
            this->currentNumOfTables -= 1;
            delete sto;
        }
    }
}

void Raspored::clearSto()
{
    qDeleteAll(m_raspored);
    m_raspored.clear();
    Sto::resetNextId();
}

void Raspored::setMaxTables(qint32 num){
    m_max_tables = num;
}

qint32 Raspored::getMaxTables(){
    return m_max_tables;
}
