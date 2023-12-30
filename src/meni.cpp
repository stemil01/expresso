#include "meni.h"

Meni::Meni() {
    _binarySerializer = new BinarySerializer("data/meni");
}

Meni::~Meni() {
    auto end = _meni.end();
    for (auto it = _meni.begin(); it != end; ++it)
        delete it.value();
}

void Meni::printNamesInComboBox(QComboBox *cb) {
    cb -> clear();
    for(const auto &kategorija : _meni.keys()) {
        cb -> addItem(kategorija);
    }
}

QMap<QString, Porudzbina*>* Meni::getMeni() {
    return &_meni;
}

void Meni::addCategory(QString naziv) {
    _meni[naziv] = new Porudzbina();
}

QVariant Meni::toVariant() const
{
    QVariantMap map;
    QVariantList variantMeni;
    for (const auto& kategorija : _meni.keys()) {
        QVariantMap mapKategorija;
        mapKategorija.insert("naziv", kategorija);
        mapKategorija.insert("porudzbina", _meni[kategorija]->toVariant());
        variantMeni.append(mapKategorija);
    }
    map.insert("meni", variantMeni);
    return map;
}

void Meni::fromVariant(const QVariant &variant)
{
    const auto map = variant.toMap();
    qDeleteAll(_meni);
    _meni.clear();

    const auto variantMeni = map.value("meni").toList();
    for (const auto& variantKategorija : variantMeni) {
        const auto mapKategorija = variantKategorija.toMap();
        QString nazivKategorije = mapKategorija.value("naziv").toString();
        QVariant variantPorudzbina = mapKategorija.value("porudzbina");

        _meni[nazivKategorije] = new Porudzbina();
        _meni[nazivKategorije]->fromVariant(variantPorudzbina);
    }
}

void Meni::executeLoad()
{
    _binarySerializer->load(*this, "meni.bin");
}

void Meni::executeSave() const
{
    _binarySerializer->save(*this, "meni.bin");
}
