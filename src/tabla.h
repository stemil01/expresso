#ifndef TABLA_H
#define TABLA_H

#include <QGraphicsScene>

class Sto;

class Tabla : public QGraphicsScene
{
public:
    explicit Tabla(QObject *parent = nullptr);
    void pozicionirajSto(Sto *s);

public slots:
    void postaviSto(Sto *s);
};

#endif // TABLA_H
