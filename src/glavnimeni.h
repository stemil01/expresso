#ifndef GLAVNIMENI_H
#define GLAVNIMENI_H

#include <QMainWindow>

class stozaprikaz;
class QGraphicsScene;

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
    void dodatNovSto(stozaprikaz *);

private:
    Ui::GlavniMeni *ui;
    void connectSlots();
    void setStyle();
    void on_pbDTAMainMenu_clicked();
    void on_pbBackDTAMenu_clicked();
    void on_pbStartMainMenu_clicked();
    void on_pbBackStartMenu_clicked();
    QGraphicsScene *tabla;
    QVector<stozaprikaz *> _stolovi;

private slots:
    void on_pbQuitMainMenu_clicked();
    void on_pbHelpMainMenu_clicked();
    void dodajNovSto();
};

#endif // GLAVNIMENI_H
