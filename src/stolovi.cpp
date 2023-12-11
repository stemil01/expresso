#include "stolovi.h"
#include "ui_stolovi.h"
#include "tabla.h"
#include "stozaprikaz.h"

qint32 idd=0;

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
    connect(ui->pbObrisiSve, &QPushButton::clicked, this, &stolovi::obrisiSve);

}

void stolovi::dodajNovSto()
{
    idd++;
    const auto sto = new stozaprikaz(idd);

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

void stolovi::obrisiSve()
{
    for(auto sto : _stolovi)
        tabla->removeItem(sto);
}

void stolovi::closeWindow()
{
    this->close();
}

stolovi::~stolovi()
{
    delete ui;
}

