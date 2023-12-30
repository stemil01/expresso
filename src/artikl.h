#ifndef ARTIKL_H
#define ARTIKL_H

#include <QString>

class Artikl{

public:

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

private:
    QString naziv;
    double cena;
    QString kategorija;
    int kolicina;
};




#endif // ARTIKL_H
