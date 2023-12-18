#include "naruci.h"
#include "ui_naruci.h"

Naruci::Naruci(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Naruci)
{
    ui->setupUi(this);

    QHeaderView* header = ui->twOrderOrderDialog->horizontalHeader();
    // Set the resizing mode for each column to Stretch
    int columnCount = ui->twOrderOrderDialog->columnCount();
    for (int i = 0; i < columnCount; ++i) {
        header->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    ui->twOrderOrderDialog->setShowGrid(false);
}

Naruci::~Naruci()
{
    delete ui;
}
