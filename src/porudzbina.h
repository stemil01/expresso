#ifndef PORUDZBINA_H
#define PORUDZBINA_H

#include "artikl.h"
#include "sto.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVector>

class Porudzbina : public Serializable {
public:
  Porudzbina();
  Porudzbina(Sto *sto);
  ~Porudzbina();

  int dodajArtikl(Artikl *a);
  void obrisiArtikle();
  void sacuvajPromenu(const QString &naziv, int kolicina);
  QString racun(const QVector<Artikl *> &artikliZaIspis);
  QString ispisiCeoRacun();
  void obrisiPoNazivu(const QString &naziv);
  void obrisiPoArtiklu(Artikl *artikal);
  QVector<Artikl *> getArtikli();
  // void printInListWidget(QListWidget& lw)
  void printInTableWidget(QTableWidget *tw);
  void printInListWidget(QListWidget *lw);
  Sto *getSto();

  QVariant toVariant() const override;
  void fromVariant(const QVariant &variant) override;

private:
  Sto *_sto;
  QVector<Artikl *> artikli;
};

#endif // PORUDZBINA_H
