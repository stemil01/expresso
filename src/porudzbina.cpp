#include "porudzbina.h"
#include <QDebug>
#include <QString>
#include <QVector>

Porudzbina::Porudzbina() { artikli = QVector<Artikl *>(); }

Porudzbina::Porudzbina(Sto *sto) {
  _sto = sto;
  artikli = QVector<Artikl *>();
}

Porudzbina::~Porudzbina() { obrisiArtikle(); }

Sto *Porudzbina::getSto() { return _sto; }

void Porudzbina::printInTableWidget(QTableWidget *tw) {
  int rowCount = tw->rowCount();
  for (int i = 0; i < rowCount; ++i) {
    for (int j = 0; j < tw->columnCount(); ++j) {
      QTableWidgetItem *item = tw->takeItem(i, j);
      delete item;
    }
  }

  tw->setRowCount(0);
  int rowIndex = tw->rowCount();
  for (auto artikl : artikli) {
    auto *nameItem = new QTableWidgetItem(artikl->getNaziv());
    auto *priceItem = new QTableWidgetItem(QString::number(artikl->getCena()));
    auto *quantityItem =
        new QTableWidgetItem(QString::number(artikl->getKolicina()));
    tw->insertRow(rowIndex);
    tw->setItem(rowIndex, 0, nameItem);
    tw->setItem(rowIndex, 1, quantityItem);
    tw->setItem(rowIndex, 2, priceItem);
    rowIndex++;
  }
}

int Porudzbina::dodajArtikl(Artikl *a) {
  int prom = 0;
  bool postoji = false;
  auto it = artikli.begin();

  while (it != artikli.end()) {
    if (*(*it) == *a) {
      postoji = true;
      prom = 1;
      int k = (*it)->getKolicina();
      (*it)->setKolicina(++k);
      break;
    }
    ++it;
  }

  if (!postoji) {

    artikli.push_back(a);
  }
  return prom;
}

QString Porudzbina::racun(const QVector<Artikl *> &artikliZaIspis) {
  double ukupno = 0;
  QString opis;
  for (const Artikl *a : artikliZaIspis) {
    opis += a->getNaziv() +
            ".................................................." +
            QString::number(a->getCena()) + "x" +
            QString::number(a->getKolicina()) + "\n";
    ukupno += a->getCena() * a->getKolicina();
  }

  opis += "\nTotal...................................................." +
          QString::number(ukupno) + "\n";
  return opis;
}
QString Porudzbina::ispisiCeoRacun() { return racun(artikli); }

void Porudzbina::obrisiArtikle() {
  for (auto v : artikli) {
    delete v;
  }
  artikli.clear();
}

void Porudzbina::obrisiPoNazivu(const QString &_naziv) {
  QVector<Artikl *>::iterator it = artikli.begin();
  while (it != artikli.end()) {
    if ((*it)->getNaziv() == _naziv) {
      delete *it;
      it = artikli.erase(it);
    } else {
      ++it;
    }
  }
}

void Porudzbina::obrisiPoArtiklu(Artikl *artikal) {
  QVector<Artikl *>::iterator it = artikli.begin();
  while (it != artikli.end()) {
    if (*(*it) == *artikal) {
      delete *it;
      it = artikli.erase(it);
      return;
    } else {
      ++it;
    }
  }
}

QVector<Artikl *> Porudzbina::getArtikli() { return artikli; }

QVariant Porudzbina::toVariant() const {
  QVariantMap map;
  QVariantList variantArtikl;
  for (const auto &artikl : artikli) {
    variantArtikl.append(artikl->toVariant());
  }
  map.insert("artikli", variantArtikl);
  return map;
}

void Porudzbina::fromVariant(const QVariant &variant) {
  const auto map = variant.toMap();
  qDeleteAll(artikli);
  artikli.clear();

  const auto variantArtikli = map.value("artikli").toList();
  for (const auto &variantArtikl : variantArtikli) {
    auto *artikl = new Artikl();
    artikl->fromVariant(variantArtikl);
    // artikli.append(artikl);
    dodajArtikl(artikl);
  }
}
