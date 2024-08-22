#include "naruci.h"
#include "ui_naruci.h"

#include "porudzbina.h"
#include "kategorija.h"
#include "meni.h"
#include "sto.h"
#include <QWidget>
#include <QMessageBox>


Naruci::Naruci(QWidget *parent,Porudzbina* porudzbina, unesiartikle* _unesiArtikle,Meni* meni) :
    QDialog(parent),
    ui(new Ui::Naruci),
    p(porudzbina),
    unesiArtikle(_unesiArtikle),
    _meni(meni)
{
    ui->setupUi(this);

    connect(ui->pbAddItemOrderDialog,&QPushButton::clicked,this,&Naruci::onPbAddItemOrderDialogClicked);
    connect(ui->pbReceiptOrderDialog,&QPushButton::clicked,this,&Naruci::onPbReceiptOrderDialogClicked);
    connect(ui->pbDeleteOrderDialog,&QPushButton::clicked,this,&Naruci::deleteSelectedRow);
    connect(ui->pbBackOrderDialog,&QPushButton::clicked,this,&QDialog::accept);
    connect(ui->cbTypeOrderDialog,&QComboBox::currentTextChanged,this,&Naruci::comboBoxTextChanged);
    connect(ui->pbSplitBillOrderDialog,&QPushButton::clicked,this,&Naruci::onPbSplitBillOrderDialogClicked);

    setStyle();
}

void Naruci::setStyle() {
    QHeaderView* header = ui->twOrderOrderDialog->horizontalHeader();
    // Set the resizing mode for each column to Stretch
    int columnCount = ui->twOrderOrderDialog->columnCount();
    for (int i = 0; i < columnCount; ++i) {
        header->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    ui -> twOrderOrderDialog -> verticalHeader() -> setVisible(false);
    ui->twOrderOrderDialog->setShowGrid(false);
    ui->cbTypeOrderDialog->setCurrentIndex(-1);

    ui -> lwMenuOrderDialog -> setSelectionMode(QAbstractItemView::SingleSelection);
}

Naruci::~Naruci()
{
    delete ui;
    //delete copy;
}

void Naruci::onPbAddItemOrderDialogClicked(){

    ui->teReceiptOrderDialog->clear();

    QString kategorija=ui->cbTypeOrderDialog->currentText();
\
    auto selectedItems = ui->lwMenuOrderDialog->selectedItems();

    for(const auto& item :selectedItems){
        QString naziv=item->text();


        Artikl* artikl = (_meni->getKategorije())[kategorija]->getArtiklByNaziv(naziv);
        int promena;

        copy = new Artikl(naziv,artikl->getCena(),kategorija);
        promena = p->dodajArtikl(copy);
        if(!promena){
            addItemInTW(ui->twOrderOrderDialog,artikl);
        }else{
            updateItemInTW(ui->twOrderOrderDialog,naziv);
        }
    }
}


void Naruci::addItemInTW(QTableWidget* tw,Artikl* artikl){
    QTableWidgetItem* itemNaziv = new QTableWidgetItem();
    itemNaziv->setText(artikl->getNaziv());
    itemNaziv->setFlags(itemNaziv->flags() & ~Qt::ItemIsEditable);
    itemNaziv->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QTableWidgetItem* itemKolicina = new QTableWidgetItem();
    itemKolicina->setText(QString::number(artikl->getKolicina()));
    itemKolicina->setFlags(itemKolicina->flags() & ~Qt::ItemIsEditable);
    itemKolicina->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    QTableWidgetItem* itemCena = new QTableWidgetItem();
    itemCena->setText(QString::number(artikl->getCena()));
    itemCena->setFlags(itemCena->flags() & ~Qt::ItemIsEditable);
    itemCena->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

    int row=tw->rowCount();
    tw->insertRow(row);
    tw->setItem(row,0,itemNaziv);
    tw->setItem(row,1,itemKolicina);
    tw->setItem(row,2,itemCena);

    p -> getSto() -> currentStatus = Sto::OCCUPIED;
}
void Naruci::updateItemInTW(QTableWidget* tw,const QString& naziv){

            QList<QTableWidgetItem *> foundItems = tw->findItems(naziv, Qt::MatchExactly);

            if (!foundItems.isEmpty()) {
                QTableWidgetItem *foundItem = foundItems.first();
                int row = foundItem->row();
                QTableWidgetItem* itemChange=tw->item(row,1);
                int kolicina=(itemChange->text()).toInt();
                itemChange->setText(QString::number(++kolicina));
            }
}

void Naruci::onPbReceiptOrderDialogClicked(){

    ui->teReceiptOrderDialog->setText(p->ispisiCeoRacun());
    ui->twOrderOrderDialog->clearContents();
    ui->twOrderOrderDialog->model()->removeRows(0, ui->twOrderOrderDialog->rowCount());
    p->obrisiArtikle();
    p -> getSto() -> currentStatus = Sto::AVAILABLE;
}

void Naruci::deleteSelectedRow() {
    auto selectedRanges = ui->twOrderOrderDialog->selectedRanges();

    for (const auto& range : selectedRanges) {
        int startRow = range.topRow();
        int endRow = range.bottomRow();

        for (int row = endRow; row >= startRow; --row) {
            QTableWidgetItem *item = ui->twOrderOrderDialog->item(row, 0);
            if (item) {
                QString naziv = item->text();
                p->obrisiPoNazivu(naziv);
                ui->twOrderOrderDialog->removeRow(row);
            }
        }
    }

    if(ui -> twOrderOrderDialog -> rowCount() == 0)
        p -> getSto() -> currentStatus = Sto::AVAILABLE;

}


void Naruci::comboBoxTextChanged(){

    ui->lwMenuOrderDialog->clear();
    QString kategorija = ui->cbTypeOrderDialog->currentText();
    auto kategorije = _meni->getKategorije();
    if(kategorije.contains(kategorija)){
        auto artikli = kategorije[kategorija]->getArtikli();
        for(auto artikl : artikli){
            ui->lwMenuOrderDialog->addItem(artikl->getNaziv());
        }
    }
}


void Naruci::onPbSplitBillOrderDialogClicked() {
    auto selectedRanges = ui->twOrderOrderDialog->selectedRanges();

    if (selectedRanges.isEmpty()) {
        QMessageBox::warning(this, "Warning",
                             "If you want to split the bill, please select the desired items from the order.");
        return;
    }

    QVector<Artikl*> odabraniArtikli;

    for (const auto& range : selectedRanges) {
        int startRow = range.topRow();
        int endRow = range.bottomRow();

        for (int row = endRow; row >= startRow; --row) {
            QTableWidgetItem *itemName = ui->twOrderOrderDialog->item(row, 0);
            QTableWidgetItem *itemQuantity = ui->twOrderOrderDialog->item(row, 1);
            QTableWidgetItem *itemPrice= ui->twOrderOrderDialog->item(row, 2);

            QString kategorija=ui->cbTypeOrderDialog->currentText();

            if (itemName && itemPrice && itemQuantity) {
                QString naziv = itemName->text();
                int kolicina = itemQuantity->text().toInt();
                double cena = itemPrice->text().toDouble();
                Artikl* artikl = new Artikl(naziv,cena,kategorija,kolicina);
                if (artikl) {
                    odabraniArtikli.append(artikl);
                }
                p->obrisiPoNazivu(naziv);
                ui->twOrderOrderDialog->removeRow(row);
            }
            ui->teReceiptOrderDialog->setText(p->racun(odabraniArtikli));

        }
    }
}




