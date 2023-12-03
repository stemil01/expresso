#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stolovi.h"
#include "help.h"
#include <QApplication>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->buttonDesArrangment->setStyleSheet("border-image : url(:/resources/redbutton.png); color: white; background: transparent;");
    connect(ui->buttonQuit, SIGNAL(clicked()), this, SLOT(quitApplication()));
    connect(ui->buttonDesArrangement, &QPushButton::clicked,this,&MainWindow::onDEClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonQuit_clicked()
{


}
void MainWindow::quitApplication()
{
    qApp->quit();
}


void MainWindow::on_buttonHelp_clicked()
{
    help helpOpen;
    helpOpen.setModal(true);
    helpOpen.exec();

}

void MainWindow::onDEClicked()
{
    stolovi* t = new stolovi();
    t->show();
}


