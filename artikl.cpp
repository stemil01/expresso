#include "artikl.h"

#include <string>
#include <iostream>

Artikl::Artikl( std::string& _naziv, double _cena):naziv(_naziv),cena(_cena){}

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



std::ostream& operator<<(std::ostream& out, const Artikl& a){
    return out<<a.getNaziv()<<".................................."<<a.getCena()<<" RSD";
}
