#ifndef STO_H
#define STO_H

#include <QGraphicsObject>
#include "serializable.h"

class Porudzbina;
class Meni;

class Sto : public QGraphicsObject, public Serializable
{
    Q_OBJECT

public:
    Sto(qint32 id);
    ~Sto();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    qint32 getId();
    void setPorudzbina(Porudzbina* p);
    Porudzbina* getPorudzbina();
    qint32 broj_mesta = 4;
    bool za_raspored = true;
    QColor color = QColor::fromRgb(128,128,128);
    qreal width = 150;
    qreal height = 150;
    void setMeni(Meni *);
    Meni* getMeni();
    enum Status{
        AVAILABLE,
        OCCUPIED,
        RESERVED
    };
    Status currentStatus;

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
private:
    Porudzbina* _p = nullptr;
    qint32 _id;
    QPointF _lastPos;
    Meni* _meni;

};

#endif // STO_H
