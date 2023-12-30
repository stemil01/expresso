#ifndef ARTIKL_H
#define ARTIKL_H

#include "serializable.h"
#include <QString>

class Artikl : public Serializable {

public:

    Artikl() = default;
    Artikl(const QString& _naziv, double _cena,const QString& _kategorija, int _kolicina=1);
    ~Artikl();

    QString getNaziv() const;
    double getCena() const;
    int getKolicina() const;
    QString getKategorija() const;

    void setNaziv(const QString _naziv);
    void setCena(double _cena);
    void setKolicina(int _kolicina);
    void setKategorija(const QString _kategorija);

    bool operator==( Artikl& a) const;

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

private:
    QString naziv;
    double cena;
    QString kategorija;
    int kolicina;
};




#endif // ARTIKL_H
