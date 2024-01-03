#include "kategorija.h"
#include "artikl.h"

Kategorija::Kategorija(const QString& naziv)
    :_naziv(naziv)
{
}

QString Kategorija::getNaziv(){
    return _naziv;
}

void Kategorija::dodajArtikl(Artikl* artikal){
    _artikli.push_back(artikal);
}

QVector<Artikl*> Kategorija::getArtikli(){
    return _artikli;
}

Artikl* Kategorija::getArtiklByNaziv(const QString &naziv){
    for(const auto artikl : _artikli){
        if(artikl->getNaziv() == naziv)
            return artikl;
    }
    return nullptr;
}
