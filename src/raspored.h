#ifndef RASPORED_H
#define RASPORED_H

#include <QString>
#include "sto.h"
#include "serializable.h"

class Raspored : public Serializable
{
public:
    Raspored() = default;
    Raspored(QString,QList<Sto*>);
    QList<Sto*> getItems();

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    inline QString getNaziv() const { return naziv; }

    // TODO: Implement these
    void addSto(const Sto& sto);
    void removeSto(qint32 idStola);
private:
    QString naziv;
    QList<Sto*> _raspored;
};

#endif // RASPORED_H
