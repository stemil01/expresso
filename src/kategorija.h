#ifndef KATEGORIJA_H
#define KATEGORIJA_H
#include <QString>
#include <QVector>

class Artikl;

class Kategorija
{
public:
    Kategorija(const QString&);

    QString getNaziv();

    void dodajArtikl(Artikl*);
    QVector<Artikl*> getArtikli();
    Artikl* getArtiklByNaziv(const QString &naziv);


private:
    QString _naziv;
    QVector<Artikl*> _artikli;
};

#endif // KATEGORIJA_H
