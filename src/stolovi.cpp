#include "stolovi.h"
#include "ui_stolovi.h"
#include "tabla.h"
#include "stozaprikaz.h"

stolovi::stolovi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::stolovi)
    ,tabla(new Tabla(this))
{
    ui->setupUi(this);
    tabla->setSceneRect(-15,-15,700,400);
    ui->gvTabla->setScene(tabla);

    connect(ui->pb1, &QPushButton::clicked, this, &stolovi::dodajNovSto);
    connect(ui->pb2, &QPushButton::clicked, this, &stolovi::closeWindow);
    connect(this, &stolovi::dodatNovSto, dynamic_cast<Tabla *>(tabla), &Tabla::postaviSto);

}

void stolovi::dodajNovSto()
{
    const auto sto = new stozaprikaz();

    _stolovi.push_back(sto);
    tabla->addItem(sto);

    emit dodatNovSto(sto);
}

void stolovi::closeWindow()
{
    this->close();
}

stolovi::~stolovi()
{
    delete ui;
}

