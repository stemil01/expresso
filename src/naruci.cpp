#include "naruci.h"
#include "ui_naruci.h"
#include "porudzbina.h"

Naruci::Naruci(QWidget *parent,Porudzbina* porudzbina) :
    QDialog(parent),
    ui(new Ui::Naruci),
    p(porudzbina)
{
    ui->setupUi(this);

    connect(ui->pbAddItemOrderDialog,&QPushButton::clicked,this,&Naruci::onPbAddItemOrderDialogClicked);
    connect(ui->pbReceiptOrderDialog,&QPushButton::clicked,this,&Naruci::onPbReceiptOrderDialogClicked);
    connect(ui->pbDeleteOrderDialog,&QPushButton::clicked,this,&Naruci::deleteSelectedRow);
    connect(ui->twOrderOrderDialog,&QTableWidget::itemActivated, this,&Naruci::twItemActivated);

    QHeaderView* header = ui->twOrderOrderDialog->horizontalHeader();
    // Set the resizing mode for each column to Stretch
    int columnCount = ui->twOrderOrderDialog->columnCount();
    for (int i = 0; i < columnCount; ++i) {
        header->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    ui->twOrderOrderDialog->setShowGrid(false);

}

Naruci::~Naruci()
{
    delete ui;
}

void Naruci::onPbAddItemOrderDialogClicked(){

    ui->teReceiptOrderDialog->clear();

    QString kategorija=ui->cbTypeOrderDialog->currentText();
\
    auto selectedItems = ui->lwMenuOrderDialog->selectedItems();

    for(const auto& item :selectedItems){ //postavljena mogucnost za multiselection
        QString naziv=item->text();

        //izvuci cenu iz skladista artikala

        double cena=0;
        Artikl* artikl=new Artikl(naziv,cena,kategorija);
        int promena=p->dodajArtikl(artikl);
        if(!promena){
            addItemInTW(artikl);
        }else{
            updateItemInTW(naziv);
        }

    }
}
void Naruci::addItemInTW(Artikl* artikl){
    QTableWidgetItem* itemNaziv = new QTableWidgetItem();
    itemNaziv->setText(artikl->getNaziv());
    itemNaziv->setFlags(itemNaziv->flags() & ~Qt::ItemIsEditable);

    QTableWidgetItem* itemKolicina = new QTableWidgetItem();
    itemKolicina->setText(QString::number(artikl->getKolicina()));
    itemKolicina->setFlags(itemKolicina->flags() | Qt::ItemIsEditable);

    QTableWidgetItem* itemCena = new QTableWidgetItem();
    itemCena->setText(QString::number(artikl->getCena()));
    itemCena->setFlags(itemCena->flags() & ~Qt::ItemIsEditable);

    int row=ui->twOrderOrderDialog->rowCount();
    ui->twOrderOrderDialog->insertRow(row);
    ui->twOrderOrderDialog->setItem(row,0,itemNaziv);
    ui->twOrderOrderDialog->setItem(row,1,itemKolicina);
    ui->twOrderOrderDialog->setItem(row,2,itemCena);
}
void Naruci::updateItemInTW(const QString& naziv){
            QList<QTableWidgetItem *> foundItems = ui->twOrderOrderDialog->findItems(naziv, Qt::MatchExactly);

            if (!foundItems.isEmpty()) {
                QTableWidgetItem *foundItem = foundItems.first();
                int row = foundItem->row();
                QTableWidgetItem* itemChange=ui->twOrderOrderDialog->item(row,1);
                int kolicina=(itemChange->text()).toInt();
                itemChange->setText(QString::number(++kolicina));
            }
}

void Naruci::onPbReceiptOrderDialogClicked(){
    ui->teReceiptOrderDialog->setText(p->racun());
    ui->twOrderOrderDialog->clearContents();
    ui->twOrderOrderDialog->model()->removeRows(0, ui->twOrderOrderDialog->rowCount());
    p->obrisiArtikle();
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
}

void Naruci::twItemActivated(QTableWidgetItem *item) {
    qDebug()<<"item activated";
    if (item) {
        qDebug() << "Nova vrijednost:" << item->text();
        int kolicina = (item->text()).toInt();
        int row = item->row();

        QTableWidgetItem *itemNaziv = ui->twOrderOrderDialog->item(row, 0);
        if (itemNaziv) {
            QString naziv = itemNaziv->text();
            qDebug() << "Naziv:" << naziv;
            //p->sacuvajPromenu(naziv, kolicina);
        }
    }


}


