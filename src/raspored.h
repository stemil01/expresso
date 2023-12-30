#ifndef RASPORED_H
#define RASPORED_H

#include <QString>
#include "sto.h"
#include "serializable.h"

class Raspored : public Serializable
{
public:
    Raspored() = default;
    Raspored(const QString& rasporedName);
    ~Raspored();

    QList<Sto*> getItems();

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;
    void setMaxTables(qint32 num);
    qint32 getMaxTables();
    qint32 currentNumOfTables = 0;

    inline QString getNaziv() const { return m_naziv; }

    Sto* addSto();
    void removeSto(qint32 idStola);
    void clearSto();
private:
    QString m_naziv;
    qint32 m_idstola=1;
    qint32 m_max_tables;
    QList<Sto*> m_raspored;
};

#endif // RASPORED_H
