#ifndef STO_H
#define STO_H

#include <QGraphicsObject>
#include "serializable.h"

class Porudzbina;

class Sto : public QGraphicsObject, public Serializable
{
    Q_OBJECT

public:
    Sto();
    ~Sto();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    static qint32 getNextId();
    qint32 getId();
    static void resetNextId();
    void setPorudzbina(Porudzbina* p);
    Porudzbina* getPorudzbina();
    qint32 broj_mesta = 4;
    bool za_raspored = false;
    QColor color = QColor::fromRgb(128,128,128);
    qreal width = 150;
    qreal height = 150;
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
    static qint32 _nextId;
    QPointF _lastPos;

};

#endif // STO_H
