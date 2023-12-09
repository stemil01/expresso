#include "stolovi.h"
#include "ui_stolovi.h"
#include "tabla.h"
#include "stozaprikaz.h"

qint32 id=0;

stolovi::stolovi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::stolovi)
    ,tabla(new Tabla(this))
{
    ui->setupUi(this);
    tabla->setSceneRect(-10,0,600,500);
    ui->gvTabla->setScene(tabla);

    connect(ui->pbDodajSto, &QPushButton::clicked, this, &stolovi::dodajNovSto);
    connect(ui->pb2, &QPushButton::clicked, this, &stolovi::closeWindow);
    connect(this, &stolovi::dodatNovSto, dynamic_cast<Tabla *>(tabla), &Tabla::postaviSto);

}

void stolovi::dodajNovSto()
{
    id++;
    const auto sto = new stozaprikaz(id);

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

