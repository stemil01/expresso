#ifndef NARUCI_H
#define NARUCI_H
#include <QDialog>

#include <QTableWidgetItem>

class Porudzbina;
class Artikl;
namespace Ui {
class Naruci;
}

class Naruci : public QDialog
{
    Q_OBJECT

public:
    explicit Naruci(QWidget *parent = nullptr,Porudzbina* porudzbina = nullptr);
    ~Naruci();


public slots:
    void onPbAddItemOrderDialogClicked();
    void onPbReceiptOrderDialogClicked();
    void deleteSelectedRow();
    void twItemActivated(QTableWidgetItem* item);

private:
    Ui::Naruci *ui;
    Porudzbina* p;
    void addItemInTW(Artikl* a);
    void updateItemInTW(const QString& str);

};

#endif // NARUCI_H
