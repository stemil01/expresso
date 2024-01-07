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

void Kategorija::obrisiArtikl(const QString& naziv){
    qDebug()<<_artikli.size() << " class";
    _artikli.removeOne(this->getArtiklByNaziv(naziv));
    qDebug()<<_artikli.size() << " class";
}

Artikl* Kategorija::getArtiklByNaziv(const QString &naziv){
    for(const auto artikl : _artikli){
        if(artikl->getNaziv() == naziv)
            return artikl;
    }
    return nullptr;
}

QVariant Kategorija::toVariant() const
{
    QVariantMap map;
    map.insert("naziv", _naziv);
    QVariantList variantArtikl;
    for (const auto& artikl : _artikli) {
        variantArtikl.append(artikl->toVariant());
    }
    map.insert("artikli", variantArtikl);
    return map;
}

void Kategorija::fromVariant(const QVariant &variant)
{
    const auto map = variant.toMap();
    _naziv = map.value("naziv").toString();
    qDeleteAll(_artikli);
    _artikli.clear();

    const auto variantArtikli = map.value("artikli").toList();
    for (const auto& variantArtikl : variantArtikli) {
        Artikl *artikl = new Artikl();
        artikl->fromVariant(variantArtikl);
        dodajArtikl(artikl);
    }
}
