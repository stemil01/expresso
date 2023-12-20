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

    inline QString getNaziv() const { return m_naziv; }

    Sto* addSto();
    // TODO: Implement these
    void removeSto(qint32 idStola);
    void clearSto();
private:
    QString m_naziv;
    QList<Sto*> m_raspored;
};

#endif // RASPORED_H
