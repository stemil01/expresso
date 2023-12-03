#include "urediporudzbinu.h"
#include "ui_urediporudzbinu.h"

urediporudzbinu::urediporudzbinu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::urediporudzbinu)
{
    ui->setupUi(this);
}

urediporudzbinu::~urediporudzbinu()
{
    delete ui;
}
