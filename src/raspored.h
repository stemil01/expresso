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
    QString naziv;
    QList<Sto*> getItems();

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

private:
    QList<Sto*> _raspored;
};

#endif // RASPORED_H
