#include "meni.h"

Meni::Meni() {
    _binarySerializer = new BinarySerializer("data/meni");
}

Meni::~Meni() {
   /* auto end = _meni.end();
    for (auto it = _meni.begin(); it != end; ++it)
        delete it.value();*/

    auto kategorije = _kategorije.values();
    for(auto kategorija : kategorije){
        delete kategorija;
    }
}

void Meni::printNamesInComboBox(QComboBox *cb) {
    cb -> clear();
    for(const auto &kategorija : _kategorije.keys()) {
        cb -> addItem(kategorija);
    }
}
/*
QMap<QString, Porudzbina*>* Meni::getMeni() {
    return nullptr;//&_meni;
}
*/
void Meni::addCategory(QString naziv) {
    //_meni[naziv] = new Porudzbina();
    Kategorija *kategorija = new Kategorija(naziv);
    _kategorije[naziv] = kategorija;
}

QVariant Meni::toVariant() const
{
    QVariantMap map;
    QVariantList variantKategorije;
    for (const auto& naziv : _kategorije.keys()) {
        QVariantMap mapKategorija;
        mapKategorija.insert("naziv", naziv);
        mapKategorija.insert("kategorija", _kategorije[naziv]->toVariant());
        variantKategorije.append(mapKategorija);
    }
    map.insert("kategorije", variantKategorije);
/*
    QVariantList variantMeni;
    for (const auto& kategorija : _meni.keys()) {
        QVariantMap mapKategorija;
        mapKategorija.insert("naziv", kategorija);
        mapKategorija.insert("porudzbina", _meni[kategorija]->toVariant());
        variantMeni.append(mapKategorija);
    }
    map.insert("meni", variantMeni);*/

    return map;
}

void Meni::fromVariant(const QVariant &variant)
{
    const auto map = variant.toMap();

    qDeleteAll(_kategorije);
    _kategorije.clear();
    const auto variantKategorije = map.value("kategorije").toList();
    for (const auto& variantKategorija : variantKategorije) {
        const auto mapKategorija = variantKategorija.toMap();
        QString nazivKategorije = mapKategorija.value("naziv").toString();
        _kategorije[nazivKategorije] = new Kategorija();
        _kategorije[nazivKategorije]->fromVariant(mapKategorija.value("kategorija"));
    }
/*
    qDeleteAll(_meni);
    _meni.clear();
    const auto variantMeni = map.value("meni").toList();
    for (const auto& variantKategorija : variantMeni) {
        const auto mapKategorija = variantKategorija.toMap();
        QString nazivKategorije = mapKategorija.value("naziv").toString();
        QVariant variantPorudzbina = mapKategorija.value("porudzbina");

        _meni[nazivKategorije] = new Porudzbina();
        _meni[nazivKategorije]->fromVariant(variantPorudzbina);
    }*/
}

void Meni::executeLoad()
{
    _binarySerializer->load(*this, "meni.bin");
}

void Meni::executeSave() const
{
    _binarySerializer->save(*this, "meni.bin");
}

QMap<QString,Kategorija*> Meni::getKategorije(){
    return _kategorije;
}

int Meni::addItem(const QString &naziv,Artikl* artikl){
    return _kategorije[naziv]->dodajArtikl(artikl);
}

void Meni::deleteCategory(const QString& naziv){
    //delete _kategorije[naziv];
    _kategorije.remove(naziv);
}
