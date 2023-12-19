#ifndef NARUCI_H
#define NARUCI_H
#include "porudzbina.h"
#include <QDialog>

namespace Ui {
class Naruci;
}

class Naruci : public QDialog
{
    Q_OBJECT

public:
    explicit Naruci(QWidget *parent = nullptr);
    ~Naruci();


//private slots:
//    void on_tableWidget_itemChanged(QTableWidgetItem *item);
private:
    Ui::Naruci *ui;
    Porudzbina p;
    void on_pbAddItemOrderDialog_clicked();
    void on_pbReceiptOrderDialog_clicked();
    void deleteSelectedRow();

};

#endif // NARUCI_H
