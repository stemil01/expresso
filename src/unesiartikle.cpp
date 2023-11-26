#include "unesiartikle.h"
#include "ui_unesiartikle.h"
#include <QMessageBox>
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
    std::string ime=ui->nAMELineEdit->text().toStdString();
    double cena=ui->pRICELineEdit->text().toDouble();

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
        Artikl noviArtikal(ime,cena);
        skladisteArtikala.push_back(noviArtikal);
    }
    ui->nAMELineEdit->clear();
    ui->pRICELineEdit->clear();
}
