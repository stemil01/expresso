#ifndef IZVESTAJ_H
#define IZVESTAJ_H
#include "porudzbina.h"
#include <QDate>
class izvestaj
{
public:
    izvestaj();
    void sacuvajRacun(double ukupno,const QString& opis);
    QString ucitajdnevniizvestaj(const QDate& datum);
};

#endif // IZVESTAJ_H
