#include "glavnimeni.h"
#include "meni.h"
#include "help.h"
#include "ui_glavnimeni.h"
#include "tabla.h"
#include "sto.h"
#include "raspored.h"
#include "binaryserializer.h"
#include "naruci.h"
#include "rasporeddata.h"
#include "porudzbina.h"
#include "tableoptions.h"

#include <QMessageBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialog>
#include <QVariant>
#include <QVariantMap>
#include <QVariantList>
#include <QGraphicsItem>

GlavniMeni::GlavniMeni(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniMeni),
    tabla(new Tabla(this)),
    mainView(new Tabla(this)),
    m_rasporedData("data/arrangemets")
{
    ui -> setupUi(this);
    ui -> stackedWidget -> setCurrentIndex(0);
    connectSlots();
    setStyle();

    menu = new Meni();

    //tabla za dizajn
    tabla->setSceneRect(ui->gvTabla->rect());
    ui->gvTabla->setScene(tabla);
    ui->gvTabla->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    //glavna tabla
    mainView->setSceneRect(ui->gvMain->rect());
    ui->gvMain->setScene(mainView);
    ui->gvMain->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // ucitavanje menija
    menu->executeLoad();

    // ucitavanje rasporeda
    m_rasporedData.executeLoad();
    m_currentRaspored = nullptr;

    m_rasporedData.setMeni(menu);
}

void GlavniMeni::setStyle() {
    QHeaderView* header = ui -> twMenuEMMenu -> horizontalHeader();

    int columnCount = ui -> twMenuEMMenu -> columnCount();
    for (int i = 0; i < columnCount; ++i) {
        header -> setSectionResizeMode(i, QHeaderView::Stretch);
    }
    ui -> twMenuEMMenu -> setShowGrid(false);
    ui -> twMenuEMMenu -> verticalHeader() -> setVisible(false);

    ui -> twMenuEMMenu -> horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
    ui -> twMenuEMMenu -> horizontalHeaderItem(1)->setTextAlignment(Qt::AlignRight);

    ui -> twMenuEMMenu -> setSelectionMode(QAbstractItemView::SingleSelection);
    ui -> twMenuEMMenu -> setSelectionBehavior(QAbstractItemView::SelectRows);
    ui -> twMenuEMMenu -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    //-------------------------------------------------------------------------
}

GlavniMeni::~GlavniMeni()
{
    delete menu;
    delete ui;
}

void GlavniMeni::connectSlots() {
    connect(ui -> pbQuitMainMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbQuitMainMenu_clicked);
    connect(ui -> pbInstructionsMainMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbHelpMainMenu_clicked);
    connect(ui -> pbDTAMainMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbDTAMainMenu_clicked);
    connect(ui -> pbBackDTAMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbBackDTAMenu_clicked);
    connect(ui -> pbBackStartMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbBackStartMenu_clicked);
    connect(ui -> pbStartMainMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbStartMainMenu_clicked);
    connect(ui->pbAddTableDTAMenu, &QPushButton::clicked, this, &GlavniMeni::dodajNovSto);
    connect(this, &GlavniMeni::dodatNovSto, dynamic_cast<Tabla *>(tabla), &Tabla::postaviSto);
    connect(ui->pbRemoveTableDTAMenu, &QPushButton::clicked, this, &GlavniMeni::obrisiSto);
    connect(ui->pbClearAllDTAMenu, &QPushButton::clicked, this, &GlavniMeni::obrisiSve);
    connect(ui->pbSaveDTAMenu, &QPushButton::clicked, this, &GlavniMeni::sacuvajRaspored);
    connect(ui->cbChooseArrangement,&QComboBox::currentIndexChanged, this, &GlavniMeni::ucitajRaspored);
    connect(ui->cbDesign,&QComboBox::currentIndexChanged, this, &GlavniMeni::ucitajRasporedDTA);
    connect(ui -> pbEditMenuMainMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbEditMenuMainMenu_clicked);
    connect(ui -> pbFinishEMMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbFinishEMMenu_clicked);
    connect(ui->pbAddArrangementTAMenu, &QPushButton::clicked, this, &GlavniMeni::dodajRaspored);
    connect(ui->pbRemovearrangementTAMenu, &QPushButton::clicked, this, &GlavniMeni::obrisiRaspored);
    connect(ui->pbAddTypeEMMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbAddCategoryEMMenu_clicked);
    connect(ui->pbRemoveTypeEMMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbRemoveCategoryEMMenu_clicked);
    connect(ui->pbAddDrinkEMMenu, &QPushButton::clicked, this, &GlavniMeni::on_pbAddItemEMMenu_clicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &GlavniMeni::on_pbRemoveItemEMMenu_clicked);
    connect(ui->cbTypeEMMenu,&QComboBox::currentTextChanged,this,&GlavniMeni::cbTypeEMMenuChanged);
}
//------------------------------------------------------------------
void GlavniMeni::on_pbAddCategoryEMMenu_clicked() {
    QString kategorija = ui -> leTypeEMMenu -> displayText();
    if(kategorija == ""){
        QMessageBox messageBox;
        messageBox.setText("Please enter category name");
        messageBox.setWindowTitle("No name for category");
        messageBox.setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                 "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
        messageBox.addButton(QMessageBox::Ok);
        int result = messageBox.exec();
        if (result == QMessageBox::Ok)
            messageBox.close();
        return;
    }

    for(auto naziv : (menu -> getKategorije()).keys()) {
        if (naziv == kategorija) {
            QMessageBox messageBox;
            messageBox.setText("Category name already exists!");
            messageBox.setWindowTitle("Same category");
            messageBox.setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                     "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
            messageBox.addButton(QMessageBox::Ok);
            int result = messageBox.exec();
            if (result == QMessageBox::Ok)
                messageBox.close();
            return;
        }
    }

    menu -> addCategory(kategorija);
    ui -> cbTypeEMMenu -> addItem(kategorija);
    ui -> cbTypeEMMenu -> setCurrentText(kategorija);
    ui -> leTypeEMMenu -> clear();
}

void GlavniMeni::on_pbRemoveCategoryEMMenu_clicked() {
    QString kategorija = ui -> cbTypeEMMenu-> currentText();
   /* delete (*(menu -> getKategorije()))[kategorija];
    menu -> getMeni() -> remove(kategorija);*/
    ui -> cbTypeEMMenu -> removeItem(ui -> cbTypeEMMenu -> findText(kategorija));
    menu->deleteCategory(kategorija);
}



void GlavniMeni::on_pbAddItemEMMenu_clicked() {
    QString naziv = ui -> leNameEMMenu -> text();
    double cena = (ui -> lePriceEMMenu -> text()).toDouble();

    if(naziv == "" || cena <= 0)
        return;

    QString kategorija = ui -> cbTypeEMMenu -> currentText();
    if(kategorija == "") {
        QMessageBox messageBox;
        messageBox.setText("No category selected!");
        messageBox.setWindowTitle("No category");
        messageBox.setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                 "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
        messageBox.addButton(QMessageBox::Ok);
        int result = messageBox.exec();
        if (result == QMessageBox::Ok)
            messageBox.close();
        return;
    }

    Artikl *pom = new Artikl(naziv, cena, kategorija);
    //Artikl *a1 = new Artikl(naziv, cena, kategorija);
    int res = menu->addItem(kategorija,pom);
    if(res == 1) {
        QMessageBox messageBox;
        messageBox.setText("Item already exists!");
        messageBox.setWindowTitle("Same item");
        messageBox.setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                 "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
        messageBox.addButton(QMessageBox::Ok);
        int result = messageBox.exec();
        if (result == QMessageBox::Ok)
            messageBox.close();
        return;
    }
    (menu -> getKategorije())[kategorija] -> printInTableWidget(ui -> twMenuEMMenu);
    ui -> leNameEMMenu -> clear();
    ui -> lePriceEMMenu -> clear();
    //(*(menu -> getMeni()))[kategorija] -> printInTableWidget(ui -> twMenuEMMenu);
    //menu->addItem(kategorija,pom);
}

void GlavniMeni::on_pbRemoveItemEMMenu_clicked() {
    QList<QTableWidgetItem*> selectedItems = ui -> twMenuEMMenu ->selectedItems();

    if (!selectedItems.isEmpty()) {
        int rowToRemove = selectedItems.first()->row();

        QString naziv = ui -> twMenuEMMenu->item(rowToRemove, 0)->text();
        double cena = (ui -> twMenuEMMenu->item(rowToRemove, 1) -> text()).toDouble();
        QString kategorija = ui -> cbTypeEMMenu-> currentText();

        Artikl *pom = new Artikl(naziv, cena, kategorija);

        //(*(menu -> getMeni()))[kategorija] -> obrisiPoArtiklu(pom);

        delete pom;

        menu->getKategorije()[kategorija]->obrisiArtikl(naziv);

        ui -> twMenuEMMenu->removeRow(rowToRemove);
    } else {
        QMessageBox messageBox;
        messageBox.setText("No item has been selected!");
        messageBox.setWindowTitle("No selected items");
        messageBox.setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                 "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
        messageBox.addButton(QMessageBox::Ok);
        int result = messageBox.exec();
        if (result == QMessageBox::Ok)
            messageBox.close();
        return;
    }
}

//----------------------------------------------------------------
void GlavniMeni::on_pbHelpMainMenu_clicked()
{
    help *helpOpen = new help(this);
    //helpOpen -> setModal(true);
    helpOpen -> exec();
    //delete helpOpen;
//    unesiartikle* ua=new unesiartikle();
//    Porudzbina* porudzbina = new Porudzbina();
//    Naruci *naruci=new Naruci(this,porudzbina,ua);
//    naruci->setModal(true);
//    naruci->exec();
//    delete naruci;
}

void GlavniMeni::on_pbQuitMainMenu_clicked()
{
    qApp -> quit();
}

void GlavniMeni::on_pbDTAMainMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(1);

    ui->cbDesign->clear();
    bool addedFirst = false;
    for (const auto& raspored : *(m_rasporedData.getRasporedi())) {
        if (!addedFirst) {
            m_currentRaspored = raspored;
            addedFirst = true;
        }
        if(raspored->getNaziv() != "")
            ui->cbDesign->addItem(raspored->getNaziv());
    }
}

void GlavniMeni::on_pbBackDTAMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(0);
}

void GlavniMeni::on_pbBackStartMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(0);
}

void GlavniMeni::on_pbStartMainMenu_clicked() {
    ui -> stackedWidget -> setCurrentIndex(2);

    ui->cbChooseArrangement->clear();
    bool addedFirst = false;
    for (const auto& raspored : *(m_rasporedData.getRasporedi())) {
        if (!addedFirst) {
            m_currentRaspored = raspored;
            addedFirst = true;
        }
        ui->cbChooseArrangement->addItem(raspored->getNaziv());
    }
}

void GlavniMeni::on_pbEditMenuMainMenu_clicked() {
    menu ->printNamesInComboBox(ui -> cbTypeEMMenu);
    ui -> stackedWidget -> setCurrentIndex(3);
}

void GlavniMeni::on_pbFinishEMMenu_clicked() {
    int rowCount = ui->twMenuEMMenu->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < ui->twMenuEMMenu->columnCount(); ++j) {
            QTableWidgetItem *item = ui->twMenuEMMenu->takeItem(i, j);
            delete item;
        }
    }

    ui -> stackedWidget -> setCurrentIndex(0);

    menu->executeSave();
}

void GlavniMeni::dodajNovSto()
{
    if(!m_currentRaspored){
        QMessageBox messageBox;
        messageBox.setText("Add arrangement");
        messageBox.setWindowTitle("Info");
        messageBox.setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                  "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
        messageBox.addButton(QMessageBox::Ok);
        messageBox.exec();
        return;
    }

    if(m_currentRaspored->currentNumOfTables >= m_currentRaspored->getMaxTables()){
        QMessageBox messageBox;
        messageBox.setText("Maximum number of tables is " + QString::number(m_currentRaspored->getMaxTables()));
        messageBox.setWindowTitle("Info");
        messageBox.setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                   "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
        messageBox.addButton(QMessageBox::Ok);

        messageBox.exec();
        return;
    }

    Sto *sto = m_currentRaspored->addSto(menu);
    tabla->addItem(sto);

    emit dodatNovSto(sto);
}

void GlavniMeni::obrisiSto()
{
    QList<QGraphicsItem*> sto_za_brisanje = tabla->selectedItems();
    if(sto_za_brisanje.length() == 1){
        tabla->removeItem(sto_za_brisanje[0]);
        Sto* sto = dynamic_cast<Sto*>(sto_za_brisanje[0]);
        m_currentRaspored->removeSto(sto->getId());
    }
    else if(sto_za_brisanje.length() == 0){
        QMessageBox messageBox;
        messageBox.setText("Select table to remove");
        messageBox.setWindowTitle("Info");
        messageBox.setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                                   "QMessageBox QLabel {color:red;min-width:200px;min-height:100px}");
        messageBox.addButton(QMessageBox::Ok);
        messageBox.exec();
    }
}

void GlavniMeni::obrisiSve()
{
    for(auto sto : m_currentRaspored->getItems()) {
        tabla->removeItem(sto);
    }
    m_currentRaspored->clearSto();
}

void GlavniMeni::sacuvajRaspored(){
    QMessageBox messageBox;
    messageBox.setText("Saved succesfully!");
    messageBox.setWindowTitle("Saved");
    messageBox.setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                              "QMessageBox QLabel {color:green;min-width:200px;min-height:100px}");
    messageBox.addButton(QMessageBox::Ok);


    int result = messageBox.exec();
    if(result == QMessageBox::Ok){
        ui -> stackedWidget -> setCurrentIndex(0);

        m_rasporedData.executeSave();

        if (m_currentRaspored == nullptr) {
            return;
        }

        for(auto item : m_currentRaspored->getItems()){
            tabla->removeItem(item);
        }
    }
    else if(result == QMessageBox::Cancel){
        messageBox.close();
    }

    const auto rasporedi = m_rasporedData.getRasporedi();
    qint32 brojRasporeda = rasporedi->size();
    if(brojRasporeda == 1){
        for(auto item : (rasporedi->values())[0]->getItems()){
            item->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable,false);
            mainView->addItem(item);
        }
    }
}

void GlavniMeni::ucitajRaspored(){
    QString naziv = ui->cbChooseArrangement->currentText();
    m_currentRaspored = m_rasporedData.getRaspored(naziv);

    if (m_currentRaspored == nullptr) {
        // TODO: obrada greske
        //std::cerr << "no raspored with name '" << naziv.toStdString() << "'" << std::endl;
        return;
    }

    this->ocistiTablu(mainView);
    for(auto sto : m_currentRaspored->getItems()){
        sto->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable,false);
        sto->za_raspored = false;
        mainView->addItem(sto);
    }
}

void GlavniMeni::ucitajRasporedDTA(){
    QString naziv = ui->cbDesign->currentText();
    m_currentRaspored = m_rasporedData.getRaspored(naziv);

    if (m_currentRaspored == nullptr) {
        qCritical() << "No arrangement with name: " << naziv.toStdString();
        return;
    }

    this->ocistiTablu(tabla);
    for(auto sto : m_currentRaspored->getItems()){
        sto->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable,true);
        if(sto->isSelected())
            sto->setSelected(false);
        sto->za_raspored = true;
        tabla->addItem(sto);
    }
}

void GlavniMeni::dodajRaspored(){

    QDialog saveInput;
    QPushButton okButton("OK");
    QPushButton cancelButton("Cancel");
    saveInput.setWindowTitle("New Arrangement");
    saveInput.setStyleSheet("QDialog{background-color:lightgray;font-weight:bold}");

    QFormLayout layout(&saveInput);
    QLineEdit textInput(&saveInput);
    QLineEdit numOfTablesInput(&saveInput);

    layout.addRow("Enter arrangement name:", &textInput);
    layout.addRow("Enter maximum number of tables:",&numOfTablesInput);
    layout.addRow(&okButton, &cancelButton);
    connect(&okButton, &QPushButton::clicked, &saveInput, &QDialog::accept);
    connect(&cancelButton, &QPushButton::clicked, &saveInput, &QDialog::reject);

    int result = saveInput.exec();
    QString naziv = textInput.text();
    if(result == QDialog::Accepted){
        m_currentRaspored = new Raspored(naziv);
        m_currentRaspored->setMaxTables(numOfTablesInput.text().toInt());
        m_rasporedData.addRaspored(m_currentRaspored);

        ui->cbDesign->addItem(naziv);
        ui->cbDesign->setCurrentIndex(ui->cbDesign->findText(naziv));
    }
    else if(result == QDialog::Rejected){
        saveInput.close();
    }
}

void GlavniMeni::obrisiRaspored()
{
    QString naziv = m_currentRaspored->getNaziv();

    QMessageBox messageBox;
    messageBox.setText("Are you sure you want to delete arrangement '" + naziv + "'?");
    messageBox.setWindowTitle("Confirm deletion");
    messageBox.setStyleSheet("QMessageBox{background-color:lightgray;font-weight:bold}"
                              "QMessageBox QLabel {color:red;min-width:400px;min-height:100px}");
    messageBox.addButton(QMessageBox::Ok);
    messageBox.addButton(QMessageBox::Cancel);

    int result = messageBox.exec();
    if(result == QMessageBox::Ok){
        m_rasporedData.removeRaspored(naziv);
        ui->cbDesign->removeItem(ui->cbDesign->findText(naziv));
    }
    else if(result == QMessageBox::Cancel){
        messageBox.close();
    }
}

void GlavniMeni::ocistiTablu(QGraphicsScene* tabla){
    for(auto item : tabla->items()){
        tabla->removeItem(item);
    }
}

void GlavniMeni::cbTypeEMMenuChanged() {
    int rowCount = ui->twMenuEMMenu->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < ui->twMenuEMMenu->columnCount(); ++j) {
            QTableWidgetItem *item = ui->twMenuEMMenu->takeItem(i, j);
            delete item;
        }
    }
    if (ui -> cbTypeEMMenu -> count() == 0) {
        return;
    }
    QString kategorija = ui -> cbTypeEMMenu -> currentText();
    (menu -> getKategorije())[kategorija] -> printInTableWidget(ui -> twMenuEMMenu);
    //(*(menu -> getMeni()))[kategorija] -> printInTableWidget(ui -> twMenuEMMenu);
}
