#include "help.h"
#include "ui_help.h"

help::help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
}




/*void help(QCloseEvent *event) {
    QDialog::closeEvent(event);
}*/

help::~help()
{
    delete ui;
}
