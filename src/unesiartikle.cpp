#include "unesiartikle.h"
#include "ui_unesiartikle.h"
#include "glavnimeni.h"
#include <QMessageBox>
#include <QFile>
#include <QTableWidget>
#include <QTableWidgetItem>

unesiartikle::unesiartikle(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::unesiartikle)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked,this,&unesiartikle::onSubmitClicked);
}

unesiartikle::~unesiartikle()
{
    delete ui;
}

void unesiartikle::dodajArtikal(const Artikl &artikal)
{
        skladisteArtikala.push_back(artikal);
}

void unesiartikle::onSubmitClicked()
{
    QString ime=ui->nAMELineEdit->text();
    double cena=ui->pRICELineEdit->text().toDouble();
    QString kategorija=ui->tYPEComboBox->currentText();

    bool postojiArtikal=false;
    for(unsigned int i=0;i<skladisteArtikala.size();++i){
        if(skladisteArtikala[i].getNaziv()==ime ){
            postojiArtikal=true;
            QMessageBox msg;
            msg.setText("Item already exists. Do you want to update its price?");
            msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msg.setDefaultButton(QMessageBox::Yes);
            unsigned int odgovor=msg.exec();
            if(odgovor==QMessageBox::Yes){
                skladisteArtikala[i].setCena(cena);
                dodajArtikal(skladisteArtikala[i]);
            }
            break;
        }

    }

    if(postojiArtikal==false){
        Artikl noviArtikal(ime,cena,kategorija);
        skladisteArtikala.push_back(noviArtikal);
    }
    ui->nAMELineEdit->clear();
    ui->pRICELineEdit->clear();
}

std::vector<Artikl> unesiartikle::getSkladisteArtikala() const
{
    return skladisteArtikala;
}

void unesiartikle::setSkladisteArtikala(const std::vector<Artikl> &newSkladisteArtikala)
{
    skladisteArtikala = newSkladisteArtikala;
}


void unesiartikle::ucitajPodatkeIzTxt()
{
    QFile file("podaci.txt");
    if(!file.exists()){
        if (!file.open(QIODevice::WriteOnly)) {
            qDebug() << "Greska prilikom otvaranja datoteke za pisanje";
                return;
        }
        file.close();
    }

    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Greska prilikom citanja fajla";
        return;

    }

    QTextStream in(&file);
    skladisteArtikala.clear();

    while(!in.atEnd()){
        QString line=in.readLine();
        QStringList tokens=line.split(" ");

        if(tokens.size()==3){
            QString ime=tokens[0];
            double cena=tokens[1].toDouble();
            QString kategorija=tokens[2];
            skladisteArtikala.push_back(Artikl(ime, cena, kategorija));
        }

    }
    file.close();
}

void unesiartikle::sacuvajPodatkeUTxt()
{
    QFile file("podaci.txt");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Greska prilikom otvaranja datoteke za pisanje";
            return;
    }

    QTextStream out(&file);
    for(const auto &a: skladisteArtikala){
        out<<a.getNaziv()<<" "<<a.getCena()<<" "<<a.getKategorija();
    }
}

void unesiartikle::ispisiPoKategorijama(const QString &odabranaKategorija)
{

    ui->twMenuEMMenu->clearContents();
    ui->twMenuEMMenu->setRowCount(0);

    int row=0;

    for(const auto& artikal: skladisteArtikala){
        if(artikal.getKategorija()==odabranaKategorija){
            QTableWidgetItem* naziv=new QTableWidgetItem (artikal.getNaziv());
            QTableWidgetItem* cena=new QTableWidgetItem(QString::number(artikal.getCena()));



            ui->twMenuEMMenu->insertRow(row);
            ui->twMenuEMMenu->setItem(row,0,naziv);
            ui->twMenuEMMenu->setItem(row,1,cena);

            ++row;
        }




    }
}
