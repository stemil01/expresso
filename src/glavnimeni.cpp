#include "glavnimeni.h"
#include "src/help.h"
#include "ui_glavnimeni.h"
#include "tabla.h"
#include "sto.h"
#include "raspored.h"
#include "binaryserializer.h"
#include "naruci.h"
#include "rasporeddata.h"

#include <QMessageBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialog>
#include <QVariant>
#include <QVariantMap>
#include <QVariantList>
#include <QGraphicsItem>


GlavniMeni::GlavniMeni(QWidget *parent) :
    QMainWindow(parent),
    ui(new GlavniMeni),
    tabla(new Tabla(this)),
    mainView(new Tabla(this)),
    m_rasporedData(new RasporedData("data"))
{
    ui -> setupUi(this);
    ui -> stackedWidget -> setCurrentIndex(0);
    connectSlots();
    //setStyle();

    //tabla za dizajn
    tabla->setSceneRect(ui->gvTabla->rect());
    ui->gvTabla->setScene(tabla);
    ui->gvTabla->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    //glavna tabla
    mainView->setSceneRect(ui->gvMain->rect());
    ui->gvMain->setScene(mainView);
    ui->gvMain->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // TODO: UCITAVANJE RASPOREDA
}

GlavniMeni::~GlavniMeni()
{
    delete ui;
}

void GlavniMeni::connectSlots() {
    connect(ui -> pbQuitMainMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbQuitMainMenu_clicked);
    connect(ui -> pbHelpMainMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbHelpMainMenu_clicked);
    connect(ui -> pbDTAMainMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbDTAMainMenu_clicked);
    connect(ui -> pbBackDTAMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbBackDTAMenu_clicked);
    connect(ui -> pbBackStartMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbBackStartMenu_clicked);
    connect(ui -> pbStartMainMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbStartMainMenu_clicked);
    connect(ui->pbAddTableDTAMenu, &QPushButton::clicked, this, &GlavniMeni::dodajNovSto);
    connect(this, &GlavniMeni::dodatNovSto, dynamic_cast<Tabla *>(tabla), &Tabla::postaviSto);
    connect(ui->pbRemoveTableDTAMenu, &QPushButton::clicked, this, &GlavniMeni::obrisiSto);
    connect(ui->pbClearAllDTAMenu, &QPushButton::clicked, this, &GlavniMeni::obrisiSve);
    connect(ui->pbSaveDTAMenu, &QPushButton::clicked, this, &GlavniMeni::sacuvajRaspored);
    connect(ui->cbChooseArrangement,&QComboBox::currentIndexChanged,&m_rasporedData,&RasporedData::loadRaspored);
    connect(ui -> pbEditMenuMainMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbEditMenuMainMenu_clicked);
    connect(ui -> pbFinishEMMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbFinishEMMenu_clicked);

    // dodaj novi prazni raspored
    connect(ui->pbAddArrangementTAMenu, &QPushButton::clicked, this, &GlavniMeni::dodajRaspored);
}

void setStyle() {

}

void GlavniMeni::on_pbHelpMainMenu_clicked()
{
    Naruci *dialogNarudzbine = new Naruci(this);
    dialogNarudzbine -> setModal(true);
    dialogNarudzbine -> exec();
    delete dialogNarudzbine;

   /* help *helpOpen = new help(this);
    helpOpen -> setModal(true);
    helpOpen -> exec();
    delete helpOpen;*/
}

void GlavniMeni::on_pbQuitMainMenu_clicked()
{
    qApp -> quit();
}

void GlavniMeni::on_pbDTAMainMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(1);

    // TODO: popunjava combobox
}

void GlavniMeni::on_pbBackDTAMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(0);
}

void GlavniMeni::on_pbBackStartMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(0);
}

void GlavniMeni::on_pbStartMainMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(2);

    ui->cbChooseArrangement->clear();
    for (const auto& raspored : _rasporedi) {
        ui->cbChooseArrangement->addItem(raspored->naziv);
    }
}

void GlavniMeni::on_pbEditMenuMainMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(3);
}

void GlavniMeni::on_pbFinishEMMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(0);
}

void GlavniMeni::dodajNovSto()
{
    if(Sto::getNextId() > 15){
        QMessageBox* messageBox = new QMessageBox();
        messageBox->setText("No more tables available");
        messageBox->setWindowTitle("Error");
        messageBox->setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                   "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
        messageBox->addButton(QMessageBox::Ok);
        messageBox->exec();
        return;
    }
    const auto table = new Sto();

    _stolovi.push_back(table);
    tabla->addItem(table);

    emit dodatNovSto(table);
}

void GlavniMeni::obrisiSto()
{
    QList<QGraphicsItem*> sto_za_brisanje = tabla->selectedItems();
    if(sto_za_brisanje.length() == 1){
        tabla->removeItem(sto_za_brisanje[0]);
    }
    else if(sto_za_brisanje.length() == 0){
        QMessageBox* messageBox = new QMessageBox();
        messageBox->setText("Select table to remove");
        messageBox->setWindowTitle("Error");
        messageBox->setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                   "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
        messageBox->addButton(QMessageBox::Ok);
        messageBox->exec();
        return;
    }

}

void GlavniMeni::obrisiSve()
{
    for(auto sto : _stolovi)
        tabla->removeItem(sto);
    Sto::resetNextId();
}

void GlavniMeni::sacuvajRaspored(){

    QMessageBox* messageBox = new QMessageBox();
    messageBox->setText("Saved succesfully!");
    messageBox->setWindowTitle("Saved");
    messageBox->setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                              "QMessageBox QLabel {color:green;min-width:200px;min-height:100px}");
    messageBox->addButton(QMessageBox::Ok);

    int result = messageBox->exec();
    if(result == QMessageBox::Ok){
        ui -> stackedWidget -> setCurrentIndex(0);
        ui->cbChooseArrangement->addItem(arrangementName);
        ui->cbDesign->addItem(arrangementName);

        QList<Sto*> stolovi;
        for(auto item : tabla->items()){
            Sto* sto = dynamic_cast<Sto*>(item);
            if(sto){
                stolovi.append(sto);
            }
        }

        for(auto item : raspored->getItems()){
            tabla->removeItem(item);
        }
        Sto::resetNextId();

        delete raspored;
    }
    else if(result == QMessageBox::Cancel){
        messageBox->close();
    }

    // qint32 brojRasporeda;
    // brojRasporeda = _rasporedi.size();
    // if(brojRasporeda == 1){
    //     for(auto item : _rasporedi[0]->getItems()){
    //         item->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable,false);
    //         mainView->addItem(item);
    //     }
    // }
    return;
}

// void GlavniMeni::ucitajRaspored(){
    // QString naziv = ui->cbChooseArrangement->currentText();
    // for(auto raspored : _rasporedi)
        // if(naziv == raspored->naziv){
            // this->ocistiTablu(mainView);
            // for(auto item : raspored->getItems()){
                // item->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable,false);
                // mainView->addItem(item);
            // }
        // }
// }

void GlavniMeni::dodajRaspored(){

    QDialog* saveInput = new QDialog();
    QLineEdit* textInput = new QLineEdit();
    QPushButton okButton("OK");
    QPushButton cancelButton("Cancel");
    saveInput->setWindowTitle("New Arrangement");
    saveInput->setStyleSheet("QDialog{background-color:lightgray;font-weight:bold}");

    QFormLayout* layout = new QFormLayout(saveInput);

    layout->addRow("Enter arrangement name:", textInput);
    layout->addRow(&okButton, &cancelButton);
    connect(&okButton, &QPushButton::clicked, saveInput, &QDialog::accept);
    connect(&cancelButton, &QPushButton::clicked, saveInput, &QDialog::reject);

    int result = saveInput->exec();
    if(result == QDialog::Accepted){
        arrangementName = textInput->text();

        QList<Sto*> stolovi;
        for(auto item : tabla->items()){
            Sto* sto = dynamic_cast<Sto*>(item);
            if(sto){
                stolovi.append(sto);
            }
        }

        m_rasporedData.addRaspored(Raspored(arrangementName, stolovi));
    }
    else if(result == QDialog::Rejected){
        saveInput->close();
    }
}

void GlavniMeni::ocistiTablu(QGraphicsScene* tabla){
     for(auto item : tabla->items()){
          tabla->removeItem(item);
     }
     Sto::resetNextId();
}

