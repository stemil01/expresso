#include "tableoptions.h"
#include "ui_tableoptions.h"
#include <QPushButton>
#include <QSlider>
#include <QGraphicsView>

TableOptions::TableOptions(QWidget *parent,Sto* sto) :
    QDialog(parent),
    ui(new Ui::TableOptions),
    m_sto(sto)
{
    ui->setupUi(this);
    ui->lID->setText("Table ID: <b>"+QString::number(sto->getId())+"</b>");
    ui->leSeats->setText(QString::number(sto->getNumSeats()));
    ui->hsbWidth->setValue(m_sto->getWidth());
    ui->hsbHeight->setValue(m_sto->getHeight());
    ui->lWidth->setText(QString::number(sto->getWidth()));
    ui->lHeight->setText(QString::number(sto->getHeight()));

    if(sto->getColor() == QColor::fromRgb(0x7f,0x70,0x53))
        ui->rbBlack->setChecked(true);
    else if(sto->getColor() == QColor::fromRgb(128,128,128))
        ui->rbGray->setChecked(true);
    else if(sto->getColor() == QColor::fromRgb(70,70,70))
        ui->rbColor3->setChecked(true);
    else
        ui->rbBrown->setChecked(true);

    if(sto->getStatus() == Sto::RESERVED)
        ui->cbReserved->setChecked(true);
    else
        ui->cbAvailable->setChecked(true);

    m_oldWidth = sto->getWidth();
    m_oldHeight = sto->getHeight();
    m_oldColor = sto->getColor();
    m_oldDegree = sto->getDegree();
    m_oldStatus = sto->getStatus();

    if(m_sto->xRadius || m_sto->yRadius){
        ui->cbRound->setChecked(true);
        m_rounded = true;
    }
    else{
        m_rounded = false;
    }

    connectSlots();
}

TableOptions::~TableOptions()
{
    delete ui;
}

void TableOptions::refresh()
{
    QGraphicsScene *scene = m_sto->scene();
    auto views = scene->views();
    QGraphicsView *view = views[0];
    view->update();
    m_sto->update();
}


void TableOptions::restoreValues()
{
    m_sto->setWidth(m_oldWidth);
    m_sto->setHeight(m_oldHeight);
    m_sto->setColor(m_oldColor);
    m_sto->setDegree(m_oldDegree);
    m_sto->setRotation(m_oldDegree);
    m_sto->setStatus(m_oldStatus);
    if(m_rounded){
        m_sto->xRadius = 10;
        m_sto->yRadius = 10;
    }
    else{
        m_sto->xRadius = 0;
        m_sto->yRadius = 0;
    }

}

void TableOptions::connectSlots()
{
    connect(this, &QDialog::accepted, this, &TableOptions::onOkClicked);
    connect(ui->pbCancel, &QPushButton::clicked, this,[this](){
        this->close();
        this->restoreValues();
    });
    connect(ui->cbReserved,&QCheckBox::clicked,this,[this](){
        if(ui->cbAvailable->isChecked()){
            ui->cbAvailable->setChecked(false);
        }
        else
            ui->cbAvailable->setChecked(true);
    });
    connect(ui->cbAvailable,&QCheckBox::clicked,this,[this](){
        if(ui->cbReserved->isChecked())
            ui->cbReserved->setChecked(false);
        else
            ui->cbReserved->setChecked(true);
    });
    connect(ui->cbRound,&QCheckBox::clicked,this,&TableOptions::onRound);
    connect(ui->rbBlack,&QRadioButton::toggled,this,[this](){
        m_sto->setColor(QColor::fromRgb(0x7f,0x70,0x53));
        refresh();
    });
    connect(ui->rbGray,&QRadioButton::toggled,this,[this](){
        m_sto->setColor(QColor::fromRgb(128,128,128));
        refresh();
    });
    connect(ui->rbColor3,&QRadioButton::toggled,this,[this](){
        m_sto->setColor(QColor::fromRgb(70,70,70));
        refresh();
    });
    connect(ui->rbBrown,&QRadioButton::toggled,this,[this](){
        m_sto->setColor(QColor::fromRgb(120,64,20));
        refresh();
    });
    connect(ui->hsbWidth,&QSlider::valueChanged,this,&TableOptions::onHSliderWidthChanged);
    connect(ui->hsbHeight,&QSlider::valueChanged,this,&TableOptions::onHSliderHeightChanged);
    connect(ui->pbDefault, &QPushButton::clicked, this, &TableOptions::onDefaultClicked);
    connect(ui->pbApply, &QPushButton::clicked, this, &TableOptions::onApplyClicked);
    connect(this,&QDialog::rejected,this,&TableOptions::restoreValues);
    connect(ui->pbOk,&QPushButton::clicked,this,&QDialog::accept);
}

void TableOptions::onOkClicked()
{
    qint32 brojMesta = ui->leSeats->text().toInt();
    if(brojMesta<=0){
        ui->labelInfo->setText("<b>Enter valid number of chairs!</b>");
        return;
    }
    m_sto->setNumSeats(brojMesta);
    if(!ui->leDegrees->text().isEmpty()){
        qint32 degree = ui->leDegrees->text().toInt();
        m_sto->setDegree(degree);
        m_sto->setRotation(degree);
    }

    if(!ui->leScale->text().isEmpty()){
        qreal scaleFactor = ui->leScale->text().toDouble();
        qreal newWidth = m_sto->getWidth()*scaleFactor;
        qreal newHeight = m_sto->getHeight()*scaleFactor;
        m_sto->setWidth(newWidth);
        m_sto->setHeight(newHeight);
        ui->lWidth->setText(QString::number(newWidth));
        ui->lHeight->setText(QString::number(newHeight));
        ui->hsbWidth->setValue(newWidth);
        ui->hsbHeight->setValue(newHeight);
    }

    if(ui->cbReserved->isChecked()){
        m_sto->setStatus(Sto::RESERVED);
    }
    else{
        m_sto->setStatus(Sto::AVAILABLE);
    }

    this->close();
}

void TableOptions::onRound()
{
    if(ui->cbRound->isChecked()){
        m_sto->xRadius = 10;
        m_sto->yRadius = 10;
        refresh();
    }
    else{
        m_sto->xRadius = 0;
        m_sto->yRadius = 0;
        refresh();
    }
}

void TableOptions::onDefaultClicked()
{
    m_sto->setWidth(150);
    m_sto->setHeight(150);
    m_sto->setDegree(0);
    m_sto->setRotation(0);
    ui->leDegrees->clear();
    ui->leScale->clear();
    m_sto->setStatus(Sto::AVAILABLE);
    m_sto->xRadius = 0;
    m_sto->yRadius = 0;
    m_sto->setColor(QColor::fromRgb(128,128,128));
    if(ui->cbRound->isChecked()){
        ui->cbRound->setChecked(false);
    }
    if(ui->cbReserved->isChecked()){
        ui->cbReserved->setChecked(false);
        ui->cbAvailable->setChecked(true);
    }
    if(!ui->rbGray->isChecked()){
        ui->rbGray->setChecked(true);
    }

    m_sto->setNumSeats(4);
    ui->leSeats->setText(QString::number(m_sto->getNumSeats()));
    ui->hsbWidth->setValue(m_sto->getWidth());
    ui->hsbHeight->setValue(m_sto->getHeight());
    ui->lWidth->setText(QString::number(m_sto->getWidth()));
    ui->lHeight->setText(QString::number(m_sto->getHeight()));
    ui->labelInfo->setText("<b>Changed to default settings!</b>");

}

void TableOptions::onHSliderHeightChanged()
{
    qint32 newHeight = ui->hsbHeight->value();
    m_sto->setHeight(newHeight);
    ui->lHeight->setText(QString::number(newHeight));

    refresh();
}

void TableOptions::onApplyClicked()
{
    ui->labelInfo->clear();
    if(!ui->leDegrees->text().isEmpty()){
        qint32 degree = ui->leDegrees->text().toInt();
        m_sto->setDegree(degree + m_sto->getDegree());
        m_sto->setDegree(m_sto->getDegree());
        m_sto->setRotation(m_sto->getDegree());
        ui->leDegrees->clear();
    }

    if(!ui->leScale->text().isEmpty()){
        qreal scaleFactor = ui->leScale->text().toDouble();
        qreal newWidth = m_sto->getWidth()*scaleFactor;
        qreal newHeight = m_sto->getHeight()*scaleFactor;
        m_sto->setWidth(newWidth);
        m_sto->setHeight(newHeight);
        ui->lWidth->setText(QString::number(newWidth));
        ui->lHeight->setText(QString::number(newHeight));
        ui->hsbWidth->setValue(newWidth);
        ui->hsbHeight->setValue(newHeight);
        ui->leScale->clear();
    }

    if(ui->cbReserved->isChecked()){
        m_sto->setStatus(Sto::RESERVED);
    }
    else{
        m_sto->setStatus(Sto::AVAILABLE);
    }

    refresh();
}

void TableOptions::onHSliderWidthChanged()
{
    qint32 newWidth = ui->hsbWidth->value();
    m_sto->setWidth(newWidth);
    ui->lWidth->setText(QString::number(newWidth));

    refresh();
}
