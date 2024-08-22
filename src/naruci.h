#ifndef NARUCI_H
#define NARUCI_H

#include "unesiartikle.h"

#include <QDialog>
#include <QTableWidgetItem>

class unesiartikle;
class Porudzbina;
class Artikl;
class Meni;

namespace Ui {
class Naruci;
}

class Naruci : public QDialog
{
    Q_OBJECT

public:
    explicit Naruci(QWidget *parent = nullptr,Porudzbina* porudzbina = nullptr, unesiartikle* unesiArtikle=nullptr,Meni* meni = nullptr);
    ~Naruci();

    void addItemInTW(QTableWidget*tw,Artikl* a);
    void updateItemInTW(QTableWidget* tw,const QString& str);

    Ui::Naruci* getUi() const { return ui; }
    Meni* getMenu(){return _meni;};
    Artikl* copy;

public slots:
    void onPbAddItemOrderDialogClicked();
    void onPbReceiptOrderDialogClicked();
    void onPbSplitBillOrderDialogClicked();
    void deleteSelectedRow();
    void comboBoxTextChanged();
private:
    void setStyle();

    Ui::Naruci *ui;
    Porudzbina* p;
    unesiartikle* unesiArtikle;
    Meni* _meni;
};

#endif // NARUCI_H
