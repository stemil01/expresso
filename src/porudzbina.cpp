#include "porudzbina.h"
#include <QVector>
#include <QString>
#include <QDebug>

Porudzbina::Porudzbina(){
    artikli = QVector<Artikl*>();
}

Porudzbina::~Porudzbina(){
    obrisiArtikle();
}

int Porudzbina::dodajArtikl(Artikl* a){
    int prom=0;
    bool postoji=false;
    auto it = artikli.begin();

    while (it != artikli.end())
    {
        if (*(*it) == *a)
        {
            postoji = true;
            prom=1;
            int k = (*it)->getKolicina();
            (*it)->setKolicina(++k);
            break;
        }
        ++it;
    }

    if(!postoji){

        artikli.push_back(a);


    }
    return prom;
}

QString Porudzbina::racun() {
    double ukupno = 0;
    QString opis;
    for (const Artikl* a : artikli) {
        opis += a->getNaziv() + ".................................................." +
                QString::number(a->getCena()) + "x" + QString::number(a->getKolicina()) + "\n";
        ukupno += a->getCena() * a->getKolicina();
    }

    opis += "\nTotal...................................................." + QString::number(ukupno) + "\n";
    return opis;
}

void Porudzbina::obrisiArtikle(){
    for(auto v : artikli){
        delete v;
    }
    artikli.clear();
}



void Porudzbina::obrisiPoNazivu(const QString& _naziv) {
    QVector<Artikl*>::iterator it = artikli.begin();
    while (it != artikli.end()) {
        if ((*it)->getNaziv() == _naziv) {
            delete *it;
            it=artikli.erase(it);
        } else {
            ++it;
        }
    }
}

void Porudzbina::sacuvajPromenu(const QString& _naziv, int _kolicina){
    QVector<Artikl*>::iterator it = artikli.begin();
    while (it != artikli.end()) {
        if ((*it)->getNaziv() == _naziv && (*it)->getKolicina() != _kolicina) {
            (*it)->setKolicina(_kolicina);
            qDebug()<<"Promjena u vektoru: ";
            qDebug()<<QString::number(_kolicina);
        }
    }
}

QVector<Artikl*> Porudzbina::getArtikli(){
    return artikli;
}

