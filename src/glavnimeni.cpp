#include "glavnimeni.h"
#include "src/help.h"
#include "ui_glavnimeni.h"
#include "tabla.h"
#include "sto.h"
#include "raspored.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialog>
#include <QVariant>
#include <QVariantMap>
#include <QVariantList>


GlavniMeni::GlavniMeni(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniMeni),
    tabla(new Tabla(this)),
    mainView(new Tabla(this))
{
    ui -> setupUi(this);
    ui -> stackedWidget -> setCurrentIndex(0);
    connectSlots();
    //setStyle();

    //tabla za dizajn
    tabla->setSceneRect(ui->gvTabla->rect());
    ui->gvTabla->setScene(tabla);
    ui->gvTabla->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    //glavna tabla
    mainView->setSceneRect(ui->gvMain->rect());
    ui->gvMain->setScene(mainView);
    ui->gvMain->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

GlavniMeni::~GlavniMeni()
{
    delete ui;
}

QVariant GlavniMeni::toVariant() const
{
    QVariantMap map;
    QVariantList rasporedi;
    for (const auto& raspored : _rasporedi) {
        rasporedi.append(raspored->toVariant());
    }
    map.insert("rasporedi", rasporedi);
    return map;
}

void GlavniMeni::fromVariant(const QVariant &variant)
{
    const auto map = variant.toMap();
    qDeleteAll(_rasporedi);
    _rasporedi.clear();

    const auto rasporedi = map.value("rasporedi").toList();
    for (const auto& rasporedVariant : rasporedi) {
        const auto raspored = new Raspored();
        raspored->fromVariant(rasporedVariant);
        _rasporedi.append(raspored);
    }
}

void GlavniMeni::connectSlots() {
    connect(ui -> pbQuitMainMenu, SIGNAL(clicked()), this, SLOT(on_pbHelpMainMenu_clicked()));
    connect(ui -> pbHelpMainMenu, SIGNAL(clicked()), this, SLOT(on_pbQuitMainMenu_clicked()));
    connect(ui -> pbDTAMainMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbDTAMainMenu_clicked);
    connect(ui -> pbBackDTAMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbBackDTAMenu_clicked);
    connect(ui -> pbBackStartMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbBackStartMenu_clicked);
    connect(ui -> pbStartMainMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbStartMainMenu_clicked);
    connect(ui->pbAddTableDTAMenu, &QPushButton::clicked, this, &GlavniMeni::dodajNovSto);
    connect(this, &GlavniMeni::dodatNovSto, dynamic_cast<Tabla *>(tabla), &Tabla::postaviSto);
    connect(ui->pbRemoveTableDTAMenu, &QPushButton::clicked, this, &GlavniMeni::obrisiSto);
    connect(ui->pbClearAllDTAMenu, &QPushButton::clicked, this, &GlavniMeni::obrisiSve);
    connect(ui->pbSaveDTAMenu, &QPushButton::clicked, this, &GlavniMeni::sacuvajRaspored);
    connect(ui->cbChooseArrangement,&QComboBox::currentIndexChanged,this,&GlavniMeni::ucitajRaspored);
    //connect(ui->pbStartMainMenu, &QPushButton::clicked, this, &GlavniMeni::ucitajRaspored);
}

void setStyle() {

}

void GlavniMeni::on_pbHelpMainMenu_clicked()
{
    help *helpOpen = new help(this);
    helpOpen -> setModal(true);
    helpOpen -> exec();
    delete helpOpen;
}

void GlavniMeni::on_pbQuitMainMenu_clicked()
{
    qApp -> quit();
}

void GlavniMeni::on_pbDTAMainMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(1);
}

void GlavniMeni::on_pbBackDTAMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(0);
}

void GlavniMeni::on_pbBackStartMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(0);
}

void GlavniMeni::on_pbStartMainMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(2);
}

void GlavniMeni::dodajNovSto()
{
    if(Sto::getNextId() > 15){
        QMessageBox* messageBox = new QMessageBox();
        messageBox->setText("No more tables available");
        messageBox->setWindowTitle("Error");
        messageBox->setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                   "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
        messageBox->addButton(QMessageBox::Ok);
        messageBox->exec();
        delete messageBox;
        return;
    }
    const auto table = new Sto();

    _stolovi.push_back(table);
    tabla->addItem(table);

    emit dodatNovSto(table);
}

void GlavniMeni::obrisiSto()
{
    QList<QGraphicsItem*> sto_za_brisanje = tabla->selectedItems();
    if(sto_za_brisanje.length() == 1){
        tabla->removeItem(sto_za_brisanje[0]);
    }
    else if(sto_za_brisanje.length() == 0){
        QMessageBox* messageBox = new QMessageBox();
        messageBox->setText("Select table to remove");
        messageBox->setWindowTitle("Error");
        messageBox->setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                   "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
        messageBox->addButton(QMessageBox::Ok);
        messageBox->exec();
        delete messageBox;
        return;
    }

}

void GlavniMeni::obrisiSve()
{
    for(auto sto : _stolovi)
        tabla->removeItem(sto);
    Sto::resetNextId();
}

void GlavniMeni::sacuvajRaspored(){

    QString arrangementName;

    QDialog* saveInput = new QDialog();
    QLineEdit* textInput = new QLineEdit();
    QPushButton okButton("OK");
    QPushButton cancelButton("Cancel");
    saveInput->setWindowTitle("Saving");
    saveInput->setStyleSheet("QDialog{background-color:lightgray;font-weight:bold}");

    QFormLayout* layout = new QFormLayout(saveInput);
    //QLabel* label = new QLabel("Some text");
    //label->setStyleSheet("font-weight:bold");

    //layout->addWidget(label);
    layout->addRow("Enter arrangement name:", textInput);
    layout->addRow(&okButton, &cancelButton);
    connect(&okButton, &QPushButton::clicked, saveInput, &QDialog::accept);
    connect(&cancelButton, &QPushButton::clicked, saveInput, &QDialog::reject);

    int result = saveInput->exec();
    if(result == QDialog::Accepted){
        ui -> stackedWidget -> setCurrentIndex(0);
        arrangementName = textInput->text();
        ui->cbChooseArrangement->addItem(arrangementName);

        QList<Sto*> stolovi;
        for(auto item : tabla->items()){
            Sto* sto = dynamic_cast<Sto*>(item);
            if(sto){
                stolovi.append(sto);
            }
        }
        const auto raspored = new Raspored(arrangementName,stolovi);
        _rasporedi.push_back(raspored);
        for(auto item : raspored->getItems()){
            tabla->removeItem(item);
        }
        Sto::resetNextId();
    }
    else if(result == QDialog::Rejected){
        saveInput->close();
    }

    qint32 brojRasporeda;
    brojRasporeda = _rasporedi.size();
    if(brojRasporeda == 1){
        for(auto item : _rasporedi[0]->getItems()){
            mainView->addItem(item);
        }
    }
}

void GlavniMeni::ucitajRaspored(){
    QString naziv = ui->cbChooseArrangement->currentText();
    for(auto raspored : _rasporedi)
        if(naziv == raspored->naziv){
            this->ocistiTablu(mainView);
            for(auto item : raspored->getItems()){
                mainView->addItem(item);
            }
        }

}

void GlavniMeni::ocistiTablu(QGraphicsScene* tabla){
     for(auto item : tabla->items()){
          tabla->removeItem(item);
     }
     Sto::resetNextId();
}

