#ifndef GLAVNIMENI_H
#define GLAVNIMENI_H

#include <QMainWindow>
#include "serializable.h"
#include "rasporeddata.h"

class Sto;
class QGraphicsScene;
class Raspored;

namespace Ui {
class GlavniMeni;
}

class GlavniMeni : public QMainWindow
{
    Q_OBJECT

public:
    explicit GlavniMeni(QWidget *parent = nullptr);
    ~GlavniMeni();

signals:
    void dodatNovSto(Sto *);

private slots:
    void on_pbDTAMainMenu_clicked();
    void on_pbBackDTAMenu_clicked();
    void on_pbStartMainMenu_clicked();
    void on_pbBackStartMenu_clicked();
    void on_pbEditMenuMainMenu_clicked();
    void on_pbQuitMainMenu_clicked();
    void on_pbHelpMainMenu_clicked();
    void on_pbFinishEMMenu_clicked();
    void dodajNovSto();
    void obrisiSto();
    void obrisiSve();
    void sacuvajRaspored();
    void ucitajRaspored();
    void ucitajRasporedDTA();
    void dodajRaspored();

private:
    void ocistiTablu(QGraphicsScene*);

private:
    Ui::GlavniMeni *ui;
    void connectSlots();
    void setStyle();
    QGraphicsScene *tabla;
    QGraphicsScene *mainView;
    RasporedData m_rasporedData;
    Raspored *m_currentRaspored;
};

#endif // GLAVNIMENI_H
