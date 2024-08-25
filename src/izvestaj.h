#ifndef IZVESTAJ_H
#define IZVESTAJ_H
#include "porudzbina.h"
#include <QDate>
class izvestaj {
public:
  izvestaj();
  void sacuvajRacun(double ukupno, const QString &opis);
  QString ucitajdnevniizvestaj(const QDate &datum);
  QString ucitajMesecniIzvestaj(const QDate &datum);
  QString ucitajGodisnjiIzvestaj(const QDate &datum);
  double izracunajProsecnuDnevnuZaradu(const QDate &datum);
  QDate najprometnijiDanMesec(const QDate &datum);
  QDate najmanjePrometanDanMesec(const QDate &datum);
  double ukupniPrihodMesec(const QDate &datum);
  double ukupniPrihodGodina(const QDate &datum);
  double dnevniPrihod(const QDate &datum);
  void unesiTrosakNabavke();
  void cistPrihodMesec(const QDate &datum);
};

#endif // IZVESTAJ_H
