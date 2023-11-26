#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "help.h"
#include <QApplication>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->buttonQuit, SIGNAL(clicked()), this, SLOT(quitApplication()));

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

