#ifndef MENI_H
#define MENI_H

#include "porudzbina.h"
#include <QMap>
#include <QString>
#include <QComboBox>

class Meni
{
public:
    Meni();
    ~Meni();

public slots:
    void printNamesInComboBox(QComboBox *cb);
    QMap<QString, Porudzbina*>* getMeni();
    void addCategory(QString naziv);


private:
    QMap<QString, Porudzbina*> _meni;
};

#endif // MENI_H
