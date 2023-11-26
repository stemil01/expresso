#ifndef UNESIARTIKLE_H
#define UNESIARTIKLE_H
#include<artikl.h>
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

    void dodajArtikal(const Artikl& artikal);
private slots:
    void onSubmitClicked();

private:
    Ui::unesiartikle *ui;
    std::vector<Artikl> skladisteArtikala;
};

#endif // UNESIARTIKLE_H
