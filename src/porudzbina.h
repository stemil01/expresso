#ifndef PORUDZBINA_H
#define PORUDZBINA_H

#include "artikl.h"
#include <QVector>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QListWidget>
#include <QListWidgetItem>


class Porudzbina : public Serializable
{
public:
    Porudzbina();
    ~Porudzbina();


    int dodajArtikl(Artikl* a);
    void obrisiArtikle();
    void sacuvajPromenu(const QString& naziv, int kolicina);
    QString racun();
    void obrisiPoNazivu(const QString& naziv);
    QVector<Artikl*> getArtikli();
    //void printInListWidget(QListWidget& lw)
    void printInTableWidget(QTableWidget *tw);

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

private:
    QVector<Artikl*> artikli;
};


#endif // PORUDZBINA_H
