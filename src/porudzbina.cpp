#include "porudzbina.h"
#include "sto.h"
#include <vector>
#include <iostream>
#include <QString>

Porudzbina::Porudzbina(){}

int Porudzbina::dodajArtikl(Artikl&a){
    int promena=0;
    bool postoji=false;
    for(unsigned int i=0;i<artikli.size();i++){
        if(artikli[i]==a){
            postoji=true;
            promena=1;
            int k=artikli[i].getKolicina();
            artikli[i].setKolicina(++k);
        }
    }
    if(!postoji){
        artikli.push_back(a);
    }
    return promena;
}
QString Porudzbina::racun() {
    double ukupno=0;
    QString opis;
    for(const Artikl &a : artikli){
        opis+=a.getNaziv()+".................................................."+QString::number(a.getCena())+"x"+QString::number(a.getKolicina())+"\n";
        ukupno+=a.getCena()*a.getKolicina();

    }
    opis+="\nTotal...................................................."+QString::number(ukupno)+"\n";
    return opis;
}

void Porudzbina::obrisiArtikle(){
    artikli.erase(artikli.begin(),artikli.end());
}

void Porudzbina::obrisiPoNazivu(const QString& _naziv){
    for(unsigned int i=0;i<artikli.size();i++){
        if(artikli[i].getNaziv()==_naziv){
            artikli.erase(artikli.begin()+i);
        }
    }
}

