#include "izvestaj.h"
#include <QDate>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>

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


QString izvestaj::ucitajMesecniIzvestaj(const QDate &datum)
{
    QString mesecniIzvestaj;
    QDate startDate(datum.year(), datum.month(), 1);
    QDate endDate = startDate.addMonths(1).addDays(-1);

    for (QDate date = startDate; date <= endDate; date = date.addDays(1)) {
        mesecniIzvestaj += ucitajdnevniizvestaj(date);
    }

    return mesecniIzvestaj;
}

QString izvestaj::ucitajGodisnjiIzvestaj(const QDate &datum)
{
    QString godisnjiIzvestaj;
    QDate startDate(datum.year(), 1, 1);
    QDate endDate = startDate.addYears(1).addDays(-1);

    for (int month = 1; month <= 12; ++month) {
        QDate monthDate(datum.year(), month, 1);
        godisnjiIzvestaj += ucitajMesecniIzvestaj(monthDate);
    }

    return godisnjiIzvestaj;
}


double izvestaj::izracunajProsecnuDnevnuZaradu(const QDate &datum)
{
    QDate startDate(datum.year(), datum.month(), 1);
    QDate endDate = startDate.addMonths(1).addDays(-1);
    double ukupno = 0;
    int brojDana = 0;

    for (QDate date = startDate; date <= endDate; date = date.addDays(1)) {
        QString dnevniIzvestaj = ucitajdnevniizvestaj(date);
        QTextStream in(&dnevniIzvestaj);
        QString linija;
        while (in.readLineInto(&linija)) {
            if (linija.startsWith("Ukupno:")) {
                QStringList parts = linija.split(" ");
                ukupno += parts[1].toDouble();
                brojDana++;
            }
        }
    }

    return brojDana > 0 ? ukupno / brojDana : 0;
}

QDate izvestaj::najprometnijiDanMesec(const QDate &datum)
{
    QDate startDate(datum.year(), datum.month(), 1);
    QDate endDate = startDate.addMonths(1).addDays(-1);
    QDate najprometnijiDan;
    double najprometnijiPrihod = 0;

    for (QDate date = startDate; date <= endDate; date = date.addDays(1)) {
        double dnevniPrihod = 0;
        QString dnevniIzvestaj = ucitajdnevniizvestaj(date);
        QTextStream in(&dnevniIzvestaj);
        QString linija;
        while (in.readLineInto(&linija)) {
            if (linija.startsWith("Ukupno:")) {
                QStringList parts = linija.split(" ");
                dnevniPrihod += parts[1].toDouble();
            }
        }

        if (dnevniPrihod > najprometnijiPrihod) {
            najprometnijiPrihod = dnevniPrihod;
            najprometnijiDan = date;
        }
    }

    return najprometnijiDan;
}

QDate izvestaj::najmanjePrometanDanMesec(const QDate &datum)
{
    QDate startDate(datum.year(), datum.month(), 1);
    QDate endDate = startDate.addMonths(1).addDays(-1);
    QDate najmanjePrometanDan;
    double najmanjePrometanPrihod = std::numeric_limits<double>::max();

    for (QDate date = startDate; date <= endDate; date = date.addDays(1)) {
        double dnevniPrihod = 0;
        QString dnevniIzvestaj = ucitajdnevniizvestaj(date);
        QTextStream in(&dnevniIzvestaj);
        QString linija;
        while (in.readLineInto(&linija)) {
            if (linija.startsWith("Ukupno:")) {
                QStringList parts = linija.split(" ");
                dnevniPrihod += parts[1].toDouble();
            }
        }

        if (dnevniPrihod < najmanjePrometanPrihod) {
            najmanjePrometanPrihod = dnevniPrihod;
            najmanjePrometanDan = date;
        }
    }

    return najmanjePrometanDan;
}


double izvestaj::ukupniPrihodMesec(const QDate &datum)
{
    QDate startDate(datum.year(), datum.month(), 1);
    QDate endDate = startDate.addMonths(1).addDays(-1);
    double ukupno = 0;

    for (QDate date = startDate; date <= endDate; date = date.addDays(1)) {
        QString dnevniIzvestaj = ucitajdnevniizvestaj(date);
        QTextStream in(&dnevniIzvestaj);
        QString linija;
        while (in.readLineInto(&linija)) {
            if (linija.startsWith("Ukupno:")) {
                QStringList parts = linija.split(" ");
                ukupno += parts[1].toDouble();
            }
        }
    }

    return ukupno;
}


double izvestaj::ukupniPrihodGodina(const QDate &datum)
{
    double ukupno = 0;

    for (int month = 1; month <= 12; ++month) {
        QDate monthDate(datum.year(), month, 1);
        ukupno += ukupniPrihodMesec(monthDate);
    }

    return ukupno;
}
double izvestaj::dnevniPrihod(const QDate &datum)
{
    double dnevniPrihod = 0;
    QString dnevniIzvestaj = ucitajdnevniizvestaj(datum);
    QTextStream in(&dnevniIzvestaj);
    QString linija;
    while (in.readLineInto(&linija)) {
        if (linija.startsWith("Ukupno:")) {
            QStringList parts = linija.split(" ");
            dnevniPrihod += parts[1].toDouble();
        }
    }

    return dnevniPrihod;

}

void izvestaj::unesiTrosakNabavke()
{
    bool ok;
    double trosakNabavke = QInputDialog::getDouble(nullptr, "Trošak nabavke", "Unesite trošak nabavke:", 0, 0, 1000000, 2, &ok);
    if (!ok) {
        qDebug() << "Unos troška nabavke otkazan";
        return;
    }

    QString datumString = QInputDialog::getText(nullptr, "Datum nabavke", "Unesite datum nabavke (format: yyyy-MM-dd):", QLineEdit::Normal, QDate::currentDate().toString("yyyy-MM-dd"), &ok);
    if (!ok) {
        qDebug() << "Unos datuma nabavke otkazan";
        return;
    }

    QDate datum = QDate::fromString(datumString, "yyyy-MM-dd");
    if (!datum.isValid()) {
        qDebug() << "Neispravan format datuma";
        QMessageBox::warning(nullptr, "Greška", "Uneli ste neispravan datum. Pokušajte ponovo.");
        return;
    }

    QString filename = "nabavke.txt";
    QFile file(filename);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << datum.toString("yyyy-MM-dd") << " " << trosakNabavke << " RSD\n";
        file.close();
    } else {
        qDebug() << "Greska prilikom kreiranja fajla za nabavku";
    }
}


void izvestaj::cistPrihodMesec(const QDate &datum)
{
    double ukupniPrihod = ukupniPrihodMesec(datum);


    double ukupniTroskoviNabavke = 0;
    QString filename = "nabavke.txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString linija;
        while (in.readLineInto(&linija)) {
            QStringList parts = linija.split(" ");
            QDate date = QDate::fromString(parts[0], "yyyy-MM-dd");
            if (date.month() == datum.month() && date.year() == datum.year()) {
                ukupniTroskoviNabavke += parts[1].toDouble();
            }
        }
        file.close();
    }


    bool ok;
    int brojRadnika = QInputDialog::getInt(nullptr, "Broj radnika", "Unesite broj radnika:", 0, 0, 100, 1, &ok);
    if (!ok) {
        qDebug() << "Unos broja radnika otkazan";// Ako je unos otkazan, prekini operaciju
    }


    double ukupnePlate = 0;
    for (int i = 1; i <= brojRadnika; ++i) {
        double plata = QInputDialog::getDouble(nullptr, "Plata radnika", QString("Unesite platu za radnika %1:").arg(i), 0, 0, 1000000, 2, &ok);
        if (!ok) {
            qDebug() << "Unos plate radnika otkazan";
            return; // Ako je unos otkazan, prekini operaciju
        }
        ukupnePlate += plata;
    }


    double cistPrihod = ukupniPrihod - ukupniTroskoviNabavke - ukupnePlate;

    // Unos stope PDV-a
    double stopaPDV = QInputDialog::getDouble(nullptr, "PDV", "Unesite stopu PDV-a (%):", 20.0, 0, 100, 2, &ok);
    if (!ok) {
        qDebug() << "Unos stope PDV-a otkazan";
        return;
    }


    double cistPrihodSaPDV = cistPrihod * (1 + stopaPDV / 100.0);


    QMessageBox::information(nullptr, "Čist prihod", QString("Čist prihod bez PDV-a: %1 RSD\nČist prihod sa PDV-om: %2 RSD")
                             .arg(cistPrihod)
                                                         .arg(cistPrihodSaPDV));
}

