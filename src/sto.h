#ifndef STO_H
#define STO_H

#include "serializable.h"
#include <QGraphicsObject>

class Porudzbina;
class Meni;

class Sto : public QGraphicsObject, public Serializable {
  Q_OBJECT

public:
  Sto(qint32 id);
  ~Sto();

  enum Status { AVAILABLE, OCCUPIED, RESERVED };

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  qint32 getId();
  void setPorudzbina(Porudzbina *p);
  Porudzbina *getPorudzbina();
  bool za_raspored = true;
  void setMeni(Meni *);
  Meni *getMeni();
  Status getStatus();
  void setStatus(Status);

  qint32 getNumSeats();
  void setNumSeats(qint32);
  qint32 getDegree();
  void setDegree(qint32);
  qint32 getWidth();
  qint32 getHeight();
  void setWidth(qint32);
  void setHeight(qint32);
  void setColor(QColor);
  QColor getColor();

  qint32 xRadius;
  qint32 yRadius;

  QVariant toVariant() const override;
  void fromVariant(const QVariant &variant) override;

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
  Porudzbina *_p = nullptr;
  qint32 m_id;
  qint32 m_degree;
  QPointF _lastPos;
  Meni *m_meni = nullptr;
  Status m_currentStatus = AVAILABLE;
  qreal m_width;
  qreal m_height;
  qint32 m_numSeats;
  QColor m_color;
};

#endif // STO_H
