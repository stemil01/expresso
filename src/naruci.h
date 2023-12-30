#ifndef NARUCI_H
#define NARUCI_H

#include "unesiartikle.h"

#include <QDialog>
#include <QTableWidgetItem>

class unesiartikle;
class Porudzbina;
class Artikl;

namespace Ui {
class Naruci;
}

class Naruci : public QDialog
{
    Q_OBJECT

public:
    explicit Naruci(QWidget *parent = nullptr,Porudzbina* porudzbina = nullptr, unesiartikle* unesiArtikle=nullptr);
    ~Naruci();

    void addItemInTW(Artikl* a);
    void updateItemInTW(const QString& str);


public slots:
    void onPbAddItemOrderDialogClicked();
    void onPbReceiptOrderDialogClicked();
    void deleteSelectedRow();
    void twItemActivated(QTableWidgetItem* item);
    void comboBoxTextChanged();
private:
    Ui::Naruci *ui;
    Porudzbina* p;
    unesiartikle* unesiArtikle;

};

#endif // NARUCI_H
