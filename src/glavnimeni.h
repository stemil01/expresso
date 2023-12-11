#ifndef GLAVNIMENI_H
#define GLAVNIMENI_H

#include <QMainWindow>

namespace Ui {
class GlavniMeni;
}

class GlavniMeni : public QMainWindow
{
    Q_OBJECT

public:
    explicit GlavniMeni(QWidget *parent = nullptr);
    ~GlavniMeni();

private:
    Ui::GlavniMeni *ui;
    void connectSlots();
    void setStyle();
    void on_pbDTAMainMenu_clicked();
    void on_pbBackDTAMenu_clicked();
    void on_pbStartMainMenu_clicked();
    void on_pbBackStartMenu_clicked();

private slots:
    void on_pbQuitMainMenu_clicked();
    void on_pbHelpMainMenu_clicked();
};

#endif // GLAVNIMENI_H
