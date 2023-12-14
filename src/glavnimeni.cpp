#include "glavnimeni.h"
#include "src/help.h"
#include "ui_glavnimeni.h"
#include "tabla.h"
#include "sto.h"
#include <QMessageBox>

qint32 id=0;

GlavniMeni::GlavniMeni(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniMeni),
    tabla(new Tabla(this))
{
    ui -> setupUi(this);
    ui -> stackedWidget -> setCurrentIndex(0);
    connectSlots();
    //setStyle();

    tabla->setSceneRect(ui->gvTabla->rect());
    ui->gvTabla->setScene(tabla);
    ui->gvTabla->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

GlavniMeni::~GlavniMeni()
{
    delete ui;
}

void GlavniMeni::connectSlots() {
    connect(ui -> pbQuitMainMenu, SIGNAL(clicked()), this, SLOT(on_pbHelpMainMenu_clicked()));
    connect(ui -> pbHelpMainMenu, SIGNAL(clicked()), this, SLOT(on_pbQuitMainMenu_clicked()));
    connect(ui -> pbDTAMainMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbDTAMainMenu_clicked);
    connect(ui -> pbBackDTAMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbBackDTAMenu_clicked);
    connect(ui -> pbBackStartMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbBackStartMenu_clicked);
    connect(ui -> pbStartMainMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbStartMainMenu_clicked);
    connect(ui->pbAddTableDTAMenu, &QPushButton::clicked, this, &GlavniMeni::dodajNovSto);
    connect(this, &GlavniMeni::dodatNovSto, dynamic_cast<Tabla *>(tabla), &Tabla::postaviSto);
    connect(ui->pbRemoveTableDTAMenu, &QPushButton::clicked, this, &GlavniMeni::obrisiSto);
    connect(ui->pbClearAllDTAMenu, &QPushButton::clicked, this, &GlavniMeni::obrisiSve);
    connect(ui->pbSaveDTAMenu, &QPushButton::clicked, this, &GlavniMeni::sacuvajRaspored);
}

void setStyle() {

}

void GlavniMeni::on_pbHelpMainMenu_clicked()
{
    help *helpOpen = new help(this);
    helpOpen -> setModal(true);
    helpOpen -> exec();
    delete helpOpen;
}

void GlavniMeni::on_pbQuitMainMenu_clicked()
{
    qApp -> quit();
}

void GlavniMeni::on_pbDTAMainMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(1);
}

void GlavniMeni::on_pbBackDTAMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(0);
}

void GlavniMeni::on_pbBackStartMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(0);
}

void GlavniMeni::on_pbStartMainMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(2);
}

void GlavniMeni::dodajNovSto()
{
    id++;
    if(id > 15){
        QMessageBox* messageBox = new QMessageBox();
        messageBox->setText("No more tables available");
        messageBox->setWindowTitle("Error");
        messageBox->setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                   "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
        messageBox->addButton(QMessageBox::Ok);
        messageBox->exec();
        delete messageBox;
        return;
    }
    const auto table = new sto(id);

    _stolovi.push_back(table);
    tabla->addItem(table);

    emit dodatNovSto(table);
}

void GlavniMeni::obrisiSto()
{
    QList<QGraphicsItem*> sto_za_brisanje = tabla->selectedItems();
    if(sto_za_brisanje.length() == 1){
        tabla->removeItem(sto_za_brisanje[0]);
        id--;
    }
    else if(sto_za_brisanje.length() == 0){
        QMessageBox* messageBox = new QMessageBox();
        messageBox->setText("Select table to remove");
        messageBox->setWindowTitle("Error");
        messageBox->setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                   "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
        messageBox->addButton(QMessageBox::Ok);
        messageBox->exec();
        delete messageBox;
        return;
    }

}

void GlavniMeni::obrisiSve()
{
    for(auto sto : _stolovi)
        tabla->removeItem(sto);
    id=0;
}

void GlavniMeni::sacuvajRaspored(){
    QGraphicsScene *mainTabla = new Tabla(this);
    mainTabla->setSceneRect(ui->gvMain->rect());
    ui->gvMain->setScene(mainTabla);
    ui->gvMain->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    QList<QGraphicsItem*> raspored = tabla->items();

    QMessageBox* messageBox = new QMessageBox();
    messageBox->setText("Saved!");
    messageBox->setWindowTitle("Success");
    messageBox->setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                              "QMessageBox QLabel {color:blue;min-width:200px;min-height:100px}");
    messageBox->addButton(QMessageBox::Ok);
    messageBox->setDefaultButton(QMessageBox::Ok);
    int result = messageBox->exec();
    if(result == QMessageBox::Ok){
        ui -> stackedWidget -> setCurrentIndex(0);
        delete messageBox;
        for(auto item : raspored){
            mainTabla->addItem(item);
            tabla->removeItem(item);
        }
    }
}

