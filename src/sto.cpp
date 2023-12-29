#include "sto.h"
#include "naruci.h"
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

qint32 Sto::_nextId = 1;

Sto::Sto()
    :QGraphicsObject() {
    _id = _nextId++;
    setFlags(GraphicsItemFlag::ItemIsSelectable | GraphicsItemFlag::ItemIsMovable);
}

Sto::~Sto(){
    delete _p;
}

QRectF Sto::boundingRect() const
{
    return QRectF(0,0,this->width,this->height);
}
void Sto::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->fillRect(boundingRect(), this->color);
    painter->setPen(Qt::white);

    QString tekst;
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, tekst.number(broj_mesta));

    if(this->isSelected() && !this->moze_da_se_koristi){
        painter->setPen(QPen(Qt::yellow, 3));
        painter->setBrush(Qt::NoBrush);

        painter->drawRect(boundingRect());
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
    if(moze_da_se_koristi){
        Porudzbina* porudzbina = new Porudzbina();
        this->setPorudzbina(porudzbina);
        Naruci *dialogNarudzbine = new Naruci(nullptr,porudzbina);
        int result = dialogNarudzbine->exec();
        if(result == QDialog::Accepted){
            this->color = QColor::fromRgb(144,238,144);
        }
        delete dialogNarudzbine;
    }
    else{
        QDialog numOfSeatsInput;
        QPushButton okButton("OK");
        QPushButton cancelButton("Cancel");
        numOfSeatsInput.setWindowTitle("Number of seats");
        numOfSeatsInput.setStyleSheet("QDialog{background-color:lightgray;font-weight:bold}");

        QFormLayout layout(&numOfSeatsInput);
        QLineEdit textInput(&numOfSeatsInput);

        layout.addRow("Enter number of seats:", &textInput);
        layout.addRow(&okButton, &cancelButton);
        connect(&okButton, &QPushButton::clicked, &numOfSeatsInput, &QDialog::accept);
        connect(&cancelButton, &QPushButton::clicked, &numOfSeatsInput, &QDialog::reject);

        int result = numOfSeatsInput.exec();
        if(result == QDialog::Accepted){
            this->broj_mesta = textInput.text().toInt();
        }
        else if(result == QDialog::Rejected){
            numOfSeatsInput.close();
        }
    }
}

qint32 Sto::getNextId(){
    return _nextId;
}

qint32 Sto::getId(){
    return _id;
}

void Sto::resetNextId(){
    _nextId = 1;
}

QVariant Sto::toVariant() const
{
    QVariantMap map;
    map.insert("id", _id);
    map.insert("nextId", _nextId);
    map.insert("position", pos());
    return map;
}

void Sto::fromVariant(const QVariant& variant)
{
    const auto map = variant.toMap();
    _id = map.value("id").toInt();
    _nextId = map.value("nextId").toInt();
    setPos(map.value("position").toPointF());
}

void Sto::setPorudzbina(Porudzbina* porudzbina){
    _p = porudzbina;
}

Porudzbina* Sto::getPorudzbina(){
    return _p;
}
