#include "sto.h"
#include "meni.h"
#include "naruci.h"
#include "ui_naruci.h"
#include "tableoptions.h"
#include "ui_tableoptions.h"
#include "porudzbina.h"
#include <string.h>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialog>
#include <QPushButton>
#include <QVariant>
#include <QVariantMap>

Sto::Sto(qint32 id)
    :QGraphicsObject() {
    _id = id;
    m_width = 150;
    m_height = 150;
    numSeats = 4;
    m_degree = 0;
    xRadius = 0;
    yRadius = 0;
    m_color = QColor::fromRgb(128,128,128);
    setFlags(GraphicsItemFlag::ItemIsSelectable | GraphicsItemFlag::ItemIsMovable);
}

Sto::~Sto(){
    delete _p;
}

QRectF Sto::boundingRect() const
{
    return QRectF(0,0,m_width,m_height);
}
void Sto::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QPainterPath path;
    path.addRoundedRect(boundingRect(),xRadius,yRadius);
    painter->fillPath(path,m_color);

    painter->setPen(Qt::white);
    QFont font("Arial", 10);
    painter->setFont(font);
    painter->drawText(boundingRect(), Qt::AlignLeft | Qt::AlignTop, " "+ QString::number(numSeats) + " chairs");
    if(currentStatus == Sto::RESERVED)
        painter->drawText(boundingRect(),Qt::AlignRight | Qt::AlignTop,"Reserved ");

    font.setPointSize(15);
    painter->setFont(font);
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, QString::number(_id));

    if(this->isSelected() && this->za_raspored){
//        painter->setPen(QPen(Qt::black, 3));
//        painter->setBrush(Qt::NoBrush);

//        painter->drawRect(boundingRect());
        painter->setPen(Qt::yellow);
        font.setPointSize(10);
        painter->setFont(font);
        painter->drawText(boundingRect(), Qt::AlignLeft | Qt::AlignTop, " "+ QString::number(numSeats) + " chairs");
        if(currentStatus == Sto::RESERVED)
            painter->drawText(boundingRect(),Qt::AlignRight | Qt::AlignTop,"Reserved ");


        font.setPointSize(15);
        painter->setFont(font);
        painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, QString::number(_id));
    }

    if(za_raspored){
//        if(m_color != QColor::fromRgb(128,128,128)){
//            m_color = QColor::fromRgb(128,128,128);
//            update();
//        }
    }
    else if(currentStatus == OCCUPIED){
            m_color = QColor::fromRgb(128,238,128);
            update();
    }
    else if(currentStatus == AVAILABLE){
        m_color = QColor::fromRgb(128,128,128);
        update();
    }
}

void Sto::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    _lastPos = event->pos();
    QGraphicsItem::mousePressEvent(event);
}

void Sto::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QPointF newPos = event->pos();
    QPointF delta = newPos - _lastPos;
    QPointF newPosScene = this->scenePos() + delta;
    _lastPos = newPos;
    QGraphicsItem::mouseMoveEvent(event);
}

void Sto::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem::mouseReleaseEvent(event);
}

void Sto::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    if(!za_raspored){
        if(this->currentStatus == AVAILABLE){
            Porudzbina* porudzbina = new Porudzbina(this);
            this->setPorudzbina(porudzbina);
        }
        unesiartikle* ua=new unesiartikle();
        Naruci *dialogNarudzbine = new Naruci(nullptr,_p,ua,_meni);
        dialogNarudzbine->getUi()->cbTypeOrderDialog->clear();
        for(auto kategorija : (_meni->getKategorije()).keys()){
            dialogNarudzbine->getUi()->cbTypeOrderDialog->addItem(kategorija);
        }
        for(auto artikl : _p->getArtikli()){
            dialogNarudzbine->addItemInTW(dialogNarudzbine->getUi()->twOrderOrderDialog,artikl);
        }
        int result = dialogNarudzbine->exec();
        if(result == QDialog::Accepted){
            /*if(this -> currentStatus == AVAILABLE)
                delete _p;*/
        }
        delete dialogNarudzbine;
        delete ua;
    }
    else{
        TableOptions* to = new TableOptions(nullptr,this);
        this->setSelected(false);
        to->exec();
        delete to;
        //this->setSelected(false);
    }
}


qint32 Sto::getId(){
    return _id;
}

QVariant Sto::toVariant() const
{
    QVariantMap map;
    map.insert("id", _id);
    map.insert("position", pos());
    map.insert("NumSeats", numSeats);
    //map.insert("porudzbina",_p->toVariant());
    // map.insert("meni", _meni->toVariant());
    return map;
}

void Sto::fromVariant(const QVariant& variant)
{
    const auto map = variant.toMap();
    _id = map.value("id").toInt();
    setPos(map.value("position").toPointF());
    numSeats = map.value("NumSeats").toInt();
    _p = new Porudzbina();
    _p->fromVariant(map.value("porudzbina"));
    // if (_meni == nullptr) {
        // _meni = new Meni();
    // }
    // _meni->fromVariant(map.value("meni"));
}

void Sto::setPorudzbina(Porudzbina* porudzbina){
    _p = porudzbina;
}

Porudzbina* Sto::getPorudzbina(){
    return _p;
}

void Sto::setMeni(Meni *meni){
    _meni = meni;
}

Meni* Sto::getMeni(){
    return _meni;
}

Sto::Status Sto::getStatus()
{
    return currentStatus;
}

void Sto::setStatus(Sto::Status status)
{
    currentStatus = status;
}

qint32 Sto::getNumSeats()
{
    return numSeats;
}

void Sto::setNumSeats(qint32 broj)
{
    numSeats = broj;
}

qint32 Sto::getDegree()
{
    return m_degree;
}

void Sto::setDegree(qint32 degree){
    m_degree = degree;
}

qint32 Sto::getWidth()
{
    return m_width;
}

qint32 Sto::getHeight()
{
    return m_height;
}

void Sto::setWidth(qint32 width)
{
    m_width = width;
}

void Sto::setHeight(qint32 height)
{
    m_height = height;
}

void Sto::setColor(QColor color)
{
    m_color = color;
}

QColor Sto::getColor(){
    return m_color;
}
