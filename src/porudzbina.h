#ifndef PORUDZBINA_H
#define PORUDZBINA_H

#include "artikl.h"
#include <vector>

class Porudzbina
{

public:
    Porudzbina();


    int dodajArtikl(Artikl& a);
    void obrisiArtikle();

    QString racun();
    void obrisiPoNazivu(const QString& naziv);

private:
    std::vector<Artikl> artikli;
};


#endif // PORUDZBINA_H
