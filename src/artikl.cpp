#include "artikl.h"


Artikl::Artikl(const QString& _naziv, double _cena,const QString& _kategorija, int _kolicina):naziv(_naziv),cena(_cena),kategorija(_kategorija),kolicina(_kolicina){}
Artikl::~Artikl(){}


QString Artikl::getNaziv() const{
    return naziv;
}
double Artikl::getCena() const{
    return cena;
}
int Artikl::getKolicina() const{
    return kolicina;
}
QString Artikl::getKategorija() const
{
    return kategorija;
}



void Artikl::setNaziv(QString _naziv){
    naziv=_naziv;
}
void Artikl::setCena(double _cena){
    cena=_cena;
}
void Artikl::setKolicina(int _kolicina){
    kolicina=_kolicina;
}

void Artikl::setKategorija(const QString _kategorija)
{
    kategorija=_kategorija;
}



bool Artikl::operator==( Artikl& a) const{
    return a.getKategorija()==kategorija && a.getNaziv()==naziv && a.getCena()==cena;
}



