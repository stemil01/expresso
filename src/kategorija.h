#ifndef KATEGORIJA_H
#define KATEGORIJA_H
#include "serializable.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QVector>

class Artikl;

class Kategorija : public Serializable
{
public:
    Kategorija() = default;
    Kategorija(const QString&);
   // ~Kategorija();

    QString getNaziv();

    int dodajArtikl(Artikl*);
    void obrisiArtikl(const QString& naziv);
    QVector<Artikl*> getArtikli();
    Artikl* getArtiklByNaziv(const QString &naziv);

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    void printInTableWidget(QTableWidget *tw);

private:
    QString _naziv;
    QVector<Artikl*> _artikli;
};

#endif // KATEGORIJA_H
