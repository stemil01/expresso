#ifndef PORUDZBINA_H
#define PORUDZBINA_H

#include "artikl.h"
#include <vector>

class Sto;

class Porudzbina{

public:
    Porudzbina();
    Porudzbina(Sto* sto);


    int dodajArtikl(Artikl& a);
    void obrisiArtikle();

    QString racun();
    void obrisiPoNazivu(const QString& naziv);

private:
    std::vector<Artikl> artikli;
    Sto* _sto;
};


#endif // PORUDZBINA_H
