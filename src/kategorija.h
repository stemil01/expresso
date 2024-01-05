#ifndef KATEGORIJA_H
#define KATEGORIJA_H
#include "serializable.h"
#include <QString>
#include <QVector>

class Artikl;

class Kategorija : public Serializable
{
public:
    Kategorija(const QString&);

    QString getNaziv();

    void dodajArtikl(Artikl*);
    QVector<Artikl*> getArtikli();
    Artikl* getArtiklByNaziv(const QString &naziv);

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

private:
    QString _naziv;
    QVector<Artikl*> _artikli;
};

#endif // KATEGORIJA_H
