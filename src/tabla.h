#ifndef TABLA_H
#define TABLA_H

#include <QGraphicsScene>

class stozaprikaz;

class Tabla : public QGraphicsScene
{
public:
    explicit Tabla(QObject *parent = nullptr);
    void positionTable(stozaprikaz *s);

public slots:
    void postaviSto(stozaprikaz *s);

private:
    qint32 brStolova;
};

#endif // TABLA_H
