#include "porudzbina.h"
#include <vector>
#include <iostream>


Porudzbina::Porudzbina(int _n):br_artikala(_n){}


void Porudzbina::dodajArtikl(Artikl& a){
    artikli.push_back(a);
}

double Porudzbina::racun() {
    double ukupno=0;
    for(const Artikl &a : artikli){
        std::cout<<a<<std::endl;
        ukupno+=a.getCena();
    }
    std::cout<<"Ukupno: ...................................."<<ukupno<<" RSD "<<std::endl;
    return ukupno;
}
