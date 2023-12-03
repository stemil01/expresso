#include "krenisaradom.h"
#include "ui_krenisaradom.h"

krenisaradom::krenisaradom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::krenisaradom)
{
    ui->setupUi(this);
    ui->pushButton->setStyleSheet("border-image : url(:/resources/redbutton.png); color: white; background: transparent;");

}

krenisaradom::~krenisaradom()
{
    delete ui;
}
