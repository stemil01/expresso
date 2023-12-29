#include "glavnimeni.h"
#include "help.h"
#include "ui_glavnimeni.h"
#include "tabla.h"
#include "sto.h"
#include "raspored.h"
#include "binaryserializer.h"
#include "naruci.h"
#include "rasporeddata.h"
#include "porudzbina.h"

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
    ui(new Ui::GlavniMeni),
    tabla(new Tabla(this)),
    mainView(new Tabla(this)),
    m_rasporedData("data")
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

    // ucitavanje rasporeda
    m_rasporedData.executeLoad();
    m_currentRaspored = nullptr;
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
    connect(ui->cbChooseArrangement,&QComboBox::currentIndexChanged, this, &GlavniMeni::ucitajRaspored);
    connect(ui->cbDesign,&QComboBox::currentIndexChanged, this, &GlavniMeni::ucitajRasporedDTA);
    connect(ui -> pbEditMenuMainMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbEditMenuMainMenu_clicked);
    connect(ui -> pbFinishEMMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbFinishEMMenu_clicked);
    connect(ui->pbAddArrangementTAMenu, &QPushButton::clicked, this, &GlavniMeni::dodajRaspored);
}

void setStyle() {

}

void GlavniMeni::on_pbHelpMainMenu_clicked()
{
    //help *helpOpen = new help(this);
    //helpOpen -> setModal(true);
    //helpOpen -> exec();
    //delete helpOpen;
    unesiartikle* ua=new unesiartikle();
    Porudzbina* porudzbina = new Porudzbina();
    Naruci *naruci=new Naruci(this,porudzbina,ua);
    naruci->setModal(true);
    naruci->exec();
    delete naruci;
}

void GlavniMeni::on_pbQuitMainMenu_clicked()
{
    qApp -> quit();
}

void GlavniMeni::on_pbDTAMainMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(1);

//    ui->cbDesign->clear();
//    for (const auto& raspored : *(m_rasporedData.getRasporedi())) {
//        ui->cbDesign->addItem(raspored->getNaziv());
//    }
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
    for (const auto& raspored : *(m_rasporedData.getRasporedi())) {
        ui->cbChooseArrangement->addItem(raspored->getNaziv());
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
    if(m_currentRaspored->currentNumOfTables >= m_currentRaspored->getMaxTables()){
        QMessageBox messageBox;
        messageBox.setText("Maximum number of tables is " + QString::number(m_currentRaspored->getMaxTables()));
        messageBox.setWindowTitle("Info");
        messageBox.setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                   "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
        messageBox.addButton(QMessageBox::Ok);
        messageBox.exec();
        return;
    }

    if(!m_currentRaspored){
        QMessageBox messageBox;
        messageBox.setText("Add arrangement");
        messageBox.setWindowTitle("Info");
        messageBox.setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                  "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
        messageBox.addButton(QMessageBox::Ok);
        messageBox.exec();
        return;
    }

    Sto *sto = m_currentRaspored->addSto();
    m_currentRaspored->currentNumOfTables += 1;
    tabla->addItem(sto);

    emit dodatNovSto(sto);
}

void GlavniMeni::obrisiSto()
{
    QList<QGraphicsItem*> sto_za_brisanje = tabla->selectedItems();
    if(sto_za_brisanje.length() == 1){
        tabla->removeItem(sto_za_brisanje[0]);
        Sto* sto = dynamic_cast<Sto*>(sto_za_brisanje[0]);
        m_currentRaspored->removeSto(sto->getId());
    }
    else if(sto_za_brisanje.length() == 0){
        QMessageBox messageBox;
        messageBox.setText("Select table to remove");
        messageBox.setWindowTitle("Info");
        messageBox.setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                   "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
        messageBox.addButton(QMessageBox::Ok);
        messageBox.exec();
    }
}

void GlavniMeni::obrisiSve()
{
    for(auto sto : m_currentRaspored->getItems()) {
        tabla->removeItem(sto);
    }
    m_currentRaspored->clearSto();
}

void GlavniMeni::sacuvajRaspored(){
    QMessageBox messageBox;
    messageBox.setText("Saved succesfully!");
    messageBox.setWindowTitle("Saved");
    messageBox.setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                              "QMessageBox QLabel {color:green;min-width:200px;min-height:100px}");
    messageBox.addButton(QMessageBox::Ok);

    int result = messageBox.exec();
    if(result == QMessageBox::Ok){
        ui -> stackedWidget -> setCurrentIndex(0);

        m_rasporedData.executeSave();

        for(auto item : m_currentRaspored->getItems()){
            tabla->removeItem(item);
        }
        Sto::resetNextId();
    }
    else if(result == QMessageBox::Cancel){
        messageBox.close();
    }

    const auto rasporedi = m_rasporedData.getRasporedi();
    qint32 brojRasporeda = rasporedi->size();
    if(brojRasporeda == 1){
        for(auto item : (rasporedi->values())[0]->getItems()){
            item->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable,false);
            mainView->addItem(item);
        }
    }
}

void GlavniMeni::ucitajRaspored(){
    QString naziv = ui->cbChooseArrangement->currentText();
    m_currentRaspored = m_rasporedData.getRaspored(naziv);

    if (m_currentRaspored == nullptr) {
        // TODO: obrada greske
        //std::cerr << "no raspored with name '" << naziv.toStdString() << "'" << std::endl;
        return;
    }

    this->ocistiTablu(mainView);
    for(auto sto : m_currentRaspored->getItems()){
        sto->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable,false);
        sto->za_raspored = false;
        mainView->addItem(sto);
    }
}

void GlavniMeni::ucitajRasporedDTA(){
    QString naziv = ui->cbDesign->currentText();

    Raspored* raspored = m_rasporedData.getRaspored(naziv);


    this->ocistiTablu(tabla);
    for(auto item : raspored->getItems()){
        tabla->addItem(item);
    }
}

void GlavniMeni::dodajRaspored(){

    QDialog saveInput;
    QPushButton okButton("OK");
    QPushButton cancelButton("Cancel");
    saveInput.setWindowTitle("New Arrangement");
    saveInput.setStyleSheet("QDialog{background-color:lightgray;font-weight:bold}");

    QFormLayout layout(&saveInput);
    QLineEdit textInput(&saveInput);
    QLineEdit numOfTablesInput(&saveInput);

    layout.addRow("Enter arrangement name:", &textInput);
    layout.addRow("Enter maximum number of tables:",&numOfTablesInput);
    layout.addRow(&okButton, &cancelButton);
    connect(&okButton, &QPushButton::clicked, &saveInput, &QDialog::accept);
    connect(&cancelButton, &QPushButton::clicked, &saveInput, &QDialog::reject);

    int result = saveInput.exec();
    if(result == QDialog::Accepted){
        delete m_currentRaspored;
        m_currentRaspored = new Raspored(textInput.text());
        m_currentRaspored->setMaxTables(numOfTablesInput.text().toInt());
        m_rasporedData.addRaspored(m_currentRaspored);

        ui->cbDesign->addItem(m_currentRaspored->getNaziv());
    }
    else if(result == QDialog::Rejected){
        saveInput.close();
    }
}

void GlavniMeni::ocistiTablu(QGraphicsScene* tabla){
     for(auto item : tabla->items()){
          tabla->removeItem(item);
     }
     Sto::resetNextId();
}


