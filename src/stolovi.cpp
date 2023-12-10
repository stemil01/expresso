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
    connect(ui->pbObrisiSto, &QPushButton::clicked, this, &stolovi::obrisiSto);

}

void stolovi::dodajNovSto()
{
    id++;
    const auto sto = new stozaprikaz(id);

    _stolovi.push_back(sto);
    tabla->addItem(sto);

    emit dodatNovSto(sto);
}

void stolovi::obrisiSto()
{
    QList<QGraphicsItem*> sto_za_brisanje = tabla->selectedItems();
    if(sto_za_brisanje.length() == 1)
        tabla->removeItem(sto_za_brisanje[0]);
}

void stolovi::closeWindow()
{
    this->close();
}

stolovi::~stolovi()
{
    delete ui;
}

