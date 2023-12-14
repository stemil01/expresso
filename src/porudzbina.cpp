#include "porudzbina.h"
#include <vector>
#include <iostream>
#include <QString>

Porudzbina::Porudzbina(int _n):br_artikala(_n){}


void Porudzbina::dodajArtikl(Artikl& a){
    artikli.push_back(a);
}

double Porudzbina::racun() {
    double ukupno=0;
    QString opis;
    for(const Artikl &a : artikli){
        std::cout<<a<<std::endl;
        ukupno+=a.getCena();
        opis +=QString::fromStdString(a.getNaziv())+" "+QString::number(a.getCena())+"\n";
    }
    std::cout<<"Ukupno: ...................................."<<ukupno<<" RSD "<<std::endl;
    return ukupno;
}
