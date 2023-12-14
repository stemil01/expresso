#include "izvestaj.h"
#include <QDate>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

izvestaj::izvestaj() {}

void izvestaj::sacuvajRacun(double ukupno, const QString &opis)
{
    QDate datum = QDate::currentDate();
    QString filename = "racuni_" + datum.toString("yyyy_MM_dd") + ".txt";
    unsigned i=1;

    QFile file(filename);
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << i<<". "<< opis << "\n";
            out << "Ukupno: ...................................." << ukupno << " RSD\n\n";
            file.close();
        } else {
            qDebug() << "Greska prilikom kreiranja dnevnog izvestaja";
        }
    } else {
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out <<i<<". " << opis << "\n";
            out << "Ukupno: ...................................." << ukupno << " RSD\n\n";
            file.close();
        } else {
            qDebug() << "Greska prilikom cuvanja racuna u izvestaju";
        }
    }
}

QString izvestaj::ucitajdnevniizvestaj(const QDate &datum)
{

    QString filename = "racuni_" + datum.toString("yyyy_MM_dd") + ".txt";
    QString izvestajdnevni;

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        izvestajdnevni = in.readAll();
        file.close();
    } else {
        qDebug() << "Greska prilikom ucitavanja dnevnog izvestaja";
    }

    return izvestajdnevni;
}





