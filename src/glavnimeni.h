#ifndef GLAVNIMENI_H
#define GLAVNIMENI_H

#include <QMainWindow>
#include "serializable.h"

class Sto;
class QGraphicsScene;
class Raspored;

namespace Ui {
class GlavniMeni;
}

class GlavniMeni : public QMainWindow, public Serializable
{
    Q_OBJECT

public:
    explicit GlavniMeni(QWidget *parent = nullptr);
    ~GlavniMeni();

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

signals:
    void dodatNovSto(Sto *);

private:
    Ui::GlavniMeni *ui;
    void connectSlots();
    void setStyle();
    void on_pbDTAMainMenu_clicked();
    void on_pbBackDTAMenu_clicked();
    void on_pbStartMainMenu_clicked();
    void on_pbBackStartMenu_clicked();
    QGraphicsScene *tabla;
    QGraphicsScene *mainView;
    QVector<Sto *> _stolovi;
    QList<Raspored*> _rasporedi;
    qint32 brojStolova = 0;
    void ocistiTablu(QGraphicsScene*);

private slots:
    void on_pbQuitMainMenu_clicked();
    void on_pbHelpMainMenu_clicked();
    void dodajNovSto();
    void obrisiSto();
    void obrisiSve();
    void sacuvajRaspored();
    void ucitajRaspored();
};

#endif // GLAVNIMENI_H
