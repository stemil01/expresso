#ifndef PORUDZBINA_H
#define PORUDZBINA_H

#include "artikl.h"
#include <QVector>

class Porudzbina
{
public:
    Porudzbina();
    ~Porudzbina();


    int dodajArtikl(Artikl* a);
    void obrisiArtikle();
    void sacuvajPromenu(const QString& naziv, int kolicina);
    QString racun();
    void obrisiPoNazivu(const QString& naziv);
    QVector<Artikl*> getArtikli();

private:
    QVector<Artikl*> artikli;
};


#endif // PORUDZBINA_H
