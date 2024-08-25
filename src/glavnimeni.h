#ifndef GLAVNIMENI_H
#define GLAVNIMENI_H

#include "artikl.h"
#include "meni.h"
#include "rasporeddata.h"
#include "serializable.h"

#include <iostream>

#include <QList>
#include <QMainWindow>
#include <QString>

class Sto;
class QGraphicsScene;
class Raspored;
class Meni;

namespace Ui {
class GlavniMeni;
}

class GlavniMeni : public QMainWindow {
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
  void on_pbAddCategoryEMMenu_clicked();
  void on_pbRemoveCategoryEMMenu_clicked();
  void on_pbAddItemEMMenu_clicked();
  void on_pbRemoveItemEMMenu_clicked();
  void cbTypeEMMenuChanged();
  void dodajNovSto();
  void obrisiSto();
  void obrisiSve();
  void sacuvajRaspored();
  void ucitajRaspored();
  void ucitajRasporedDTA();
  void dodajRaspored();
  void obrisiRaspored();

private:
  void ocistiTablu(QGraphicsScene *);

private:
  Ui::GlavniMeni *ui;
  void connectSlots();
  void setStyle();
  QGraphicsScene *tabla;
  QGraphicsScene *mainView;
  RasporedData m_rasporedData;
  Raspored *m_currentRaspored;
  Meni *menu;

  friend class GlavniMeniTest;
};

#endif // GLAVNIMENI_H
