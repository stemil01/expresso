#ifndef PORUDZBINA_H
#define PORUDZBINA_H

#include "artikl.h"

#include <vector>

class Porudzbina{

public:
    Porudzbina(int _n);


    void dodajArtikl(Artikl& s);

    double racun();


private:
    std::vector<Artikl> artikli;
    int br_artikala;
};


#endif // PORUDZBINA_H
