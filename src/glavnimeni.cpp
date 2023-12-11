#include "glavnimeni.h"
#include "src/help.h"
#include "ui_glavnimeni.h"
#include "tabla.h"
#include "stozaprikaz.h"

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

    tabla->setSceneRect(0,0,700,700);
    ui->gvTabla->setScene(tabla);
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
    const auto sto = new stozaprikaz(id);

    _stolovi.push_back(sto);
    tabla->addItem(sto);

    emit dodatNovSto(sto);
}

