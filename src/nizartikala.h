#ifndef NIZARTIKALA_H
#define NIZARTIKALA_H

#include "artikl.h"
#include <Qvector>
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>

class NizArtikala
{


public:
    bool dodajArtikal(Artikl *artikal);
    void ukloniArtikal(QString &naziv);
    void printInTableWidget(QTableWidget *tw);
    NizArtikala();
    ~NizArtikala();

private:
    QVector<Artikl *> _nizArtikala;
};

#endif // NIZARTIKALA_H
