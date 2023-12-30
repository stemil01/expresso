#ifndef MENI_H
#define MENI_H

#include <QMap>
#include <QString>
#include "nizartikala.h"
#include <QComboBOx>

class Meni
{


public:
    Meni();
    ~Meni();

public slots:
    void printNamesInComboBox(QComboBox *cb);
    QMap<QString, NizArtikala*>* getMeni();
    void addCategory(QString naziv);


private:
    QMap<QString, NizArtikala*> _meni;
};

#endif // MENI_H
