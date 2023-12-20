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

private:
    Ui::GlavniMeni *ui;
    void connectSlots();
    void setStyle();
    void on_pbDTAMainMenu_clicked();
    void on_pbBackDTAMenu_clicked();
    void on_pbStartMainMenu_clicked();
    void on_pbBackStartMenu_clicked();
    void on_pbEditMenuMainMenu_clicked();
    void on_pbQuitMainMenu_clicked();
    void on_pbHelpMainMenu_clicked();
    void on_pbFinishEMMenu_clicked();
    QGraphicsScene *tabla;
    QGraphicsScene *mainView;
    QVector<Sto *> _stolovi;
    RasporedData m_rasporedData;
    QString arrangementName;
    void ocistiTablu(QGraphicsScene*);

private slots:
    void dodajNovSto();
    void obrisiSto();
    void obrisiSve();
    void sacuvajRaspored();
    void ucitajRaspored();
    void dodajRaspored();
};

#endif // GLAVNIMENI_H
