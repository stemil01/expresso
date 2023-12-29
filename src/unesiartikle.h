#ifndef UNESIARTIKLE_H
#define UNESIARTIKLE_H
#include<src/artikl.h>
#include <QWidget>
#include <QListWidget>

namespace Ui {
class unesiartikle;
}

class unesiartikle : public QWidget
{
    Q_OBJECT

public:
    explicit unesiartikle(QWidget *parent = nullptr);
    ~unesiartikle();

    void dodajArtikal(const Artikl& artikal);
    double cenaArtikla(const QString& _kategorija, const QString& _naziv);
    void ispisiPoKategorijiListWidget(QListWidget* lw,const QString &odabranaKategorija);


private slots:
    void onSubmitClicked();

private:
    Ui::unesiartikle *ui;
    std::vector<Artikl> skladisteArtikala;
    void ucitajPodatkeIzTxt();
    void sacuvajPodatkeUTxt();
    void ispisiPoKategorijama(const QString& odabranaKategorija);
};

#endif // UNESIARTIKLE_H
