#include "artikl.h"

#include <string>
#include <iostream>

Artikl::Artikl( std::string& _naziv, double _cena,QString& _kategorija):naziv(_naziv),cena(_cena),kategorija(_kategorija){}

std::string Artikl::getNaziv() const{
    return naziv;
}
double Artikl::getCena() const{
    return cena;
}

void Artikl::setNaziv(std::string _naziv){
    naziv=_naziv;
}
void Artikl::setCena(double _cena){
    cena=_cena;
}

QString Artikl::getKategorija() const
{
    return kategorija;
}

void Artikl::setKategorija(const QString _kategorija)
{
    kategorija=_kategorija;
}



std::ostream& operator<<(std::ostream& out, const Artikl& a){
    return out<<a.getNaziv()<<".................................."<<a.getCena()<<" RSD";
}
