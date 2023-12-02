#ifndef ARTIKL_H
#define ARTIKL_H

#include <iostream>
#include <string>

class Artikl{

public:

    Artikl( std::string& _naziv, double _cena);

    std::string getNaziv() const;
    double getCena() const;

    void setNaziv(const std::string _naziv);
    void setCena(double _cena);


private:
    std::string naziv;
    double cena;

};

std::ostream& operator<<(std::ostream& out, const Artikl& a);



#endif // ARTIKL_H
