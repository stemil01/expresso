#include "naruci.h"
#include "ui_naruci.h"
#include "porudzbina.h"

Naruci::Naruci(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Naruci)
{
    ui->setupUi(this);

    connect(ui->pbAddItemOrderDialog,&QPushButton::clicked,this,&Naruci::on_pbAddItemOrderDialog_clicked);
    connect(ui->pbReceiptOrderDialog,&QPushButton::clicked,this,&Naruci::on_pbReceiptOrderDialog_clicked);
    connect(ui->pbDeleteOrderDialog,&QPushButton::clicked,this,&Naruci::deleteSelectedRow);
    //connect(ui->tableWidget, &QTableWidget::itemChanged, this, &Naruci::on_tableWidget_itemChanged);

}

Naruci::~Naruci()
{
    delete ui;
}

void Naruci::on_pbAddItemOrderDialog_clicked(){

    ui->teReceiptOrderDialog->clear();

    QString kategorija=ui->comboBox->currentText();
\
    auto selectedItems = ui->lwMenuOrderDialog->selectedItems();

    for(const auto& item :selectedItems){ //postavljena mogucnost za multiselection
        QString naziv=item->text();

        //izvuci cenu iz skladista artikala kad bude tu ucitan meni


        double cena=0;
        Artikl artikl(naziv,cena,kategorija);
        int promena=p.dodajArtikl(artikl);

        if(!promena){
            QTableWidgetItem* itemNaziv = new QTableWidgetItem();
            itemNaziv->setText(artikl.getNaziv());
            QTableWidgetItem* itemKolicina = new QTableWidgetItem();
            itemKolicina->setText(QString::number(artikl.getKolicina()));
            QTableWidgetItem* itemCena = new QTableWidgetItem();
            itemCena->setText(QString::number(artikl.getCena()));

            int row=ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row,0,itemNaziv);
            ui->tableWidget->setItem(row,1,itemKolicina);
            ui->tableWidget->setItem(row,2,itemCena);
        }else{
            QList<QTableWidgetItem *> foundItems = ui->tableWidget->findItems(naziv, Qt::MatchExactly);

            if (!foundItems.isEmpty()) {
                QTableWidgetItem *foundItem = foundItems.first();
                int row = foundItem->row();
                QTableWidgetItem* itemChange=ui->tableWidget->item(row,1);
                int kolicina=(itemChange->text()).toInt();
                kolicina++;
                itemChange->setText(QString::number(kolicina));
            }
        }
    }

}

void Naruci::on_pbReceiptOrderDialog_clicked(){
    ui->teReceiptOrderDialog->setText(p.racun());
    ui->tableWidget->clearContents();
    ui->tableWidget->model()->removeRows(0, ui->tableWidget->rowCount());
    p.obrisiArtikle();
}

void Naruci::deleteSelectedRow() {
    auto selectedRanges = ui->tableWidget->selectedRanges();

    for (const auto& range : selectedRanges) {
        int startRow = range.topRow();
        int endRow = range.bottomRow();

        for (int row = endRow; row >= startRow; --row) {
            QTableWidgetItem *item = ui->tableWidget->item(row, 0);
            if (item) {
                QString naziv = item->text();
                p.obrisiPoNazivu(naziv);
                ui->tableWidget->removeRow(row);
            }
        }
    }
}



//void Naruci::on_tableWidget_itemChanged(QTableWidgetItem *item)
//{

//}

