#ifndef ARTIKL_H
#define ARTIKL_H

#include <iostream>
#include <string>
#include <QString>

class Artikl{

public:

    Artikl( std::string& _naziv, double _cena,QString& _kategorija);

    std::string getNaziv() const;
    double getCena() const;


    void setNaziv(const std::string _naziv);
    void setCena(double _cena);


    QString getKategorija() const;
    void setKategorija(const QString _kategorija);

private:
    std::string naziv;
    double cena;
    QString kategorija;

};

std::ostream& operator<<(std::ostream& out, const Artikl& a);



#endif // ARTIKL_H
