#include "naruci.h"
#include "ui_naruci.h"

Naruci::Naruci(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Naruci)
{
    ui->setupUi(this);
}

Naruci::~Naruci()
{
    delete ui;
}
