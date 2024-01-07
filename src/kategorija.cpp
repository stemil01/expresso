#include "kategorija.h"
#include "artikl.h"

Kategorija::Kategorija(const QString& naziv)
    :_naziv(naziv)
{
}

QString Kategorija::getNaziv(){
    return _naziv;
}

int Kategorija::dodajArtikl(Artikl* artikal){
    int prom=0;
    auto it = _artikli.begin();

    while (it != _artikli.end())
    {
        if ((*it) -> getNaziv() == artikal -> getNaziv())
        {
            prom=1;
            break;
        }
        ++it;
    }

    if(!prom){

        _artikli.push_back(artikal);
    }
    return prom;
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

void Kategorija::printInTableWidget(QTableWidget *tw) {
    int rowCount = tw->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < tw->columnCount(); ++j) {
            QTableWidgetItem *item = tw->takeItem(i, j);
            delete item;
        }
    }

    tw->setRowCount(0);
    int rowIndex = tw -> rowCount();
    for(auto artikl : _artikli) {
        QTableWidgetItem* nameItem = new QTableWidgetItem(artikl->getNaziv());
        QTableWidgetItem* priceItem = new QTableWidgetItem(QString::number(artikl->getCena()));
        tw->insertRow(rowIndex);
        tw->setItem(rowIndex, 0, nameItem);
        tw->setItem(rowIndex, 1, priceItem);
        rowIndex ++;
    }
}
