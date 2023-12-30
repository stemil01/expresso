#include "meni.h"

Meni::Meni() {
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
