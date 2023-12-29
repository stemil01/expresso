#ifndef UNESIARTIKLE_H
#define UNESIARTIKLE_H
#include "artikl.h"
#include <QWidget>

namespace Ui {
class unesiartikle;
}

class unesiartikle : public QWidget
{
    Q_OBJECT

public:
    explicit unesiartikle(QWidget *parent = nullptr);
    ~unesiartikle();



    void setSkladisteArtikala(const std::vector<Artikl> &newSkladisteArtikala);
    std::vector<Artikl> getSkladisteArtikala() const;
    void dodajArtikal(const Artikl& artikal);
    void ucitajPodatkeIzTxt();
    void sacuvajPodatkeUTxt();
    void ispisiPoKategorijama(const QString& odabranaKategorija);

private slots:
    void onSubmitClicked();

private:
    Ui::unesiartikle *ui;
    std::vector<Artikl> skladisteArtikala;

};

#endif // UNESIARTIKLE_H
