#ifndef TABLA_H
#define TABLA_H

#include <QGraphicsScene>

class sto;

class Tabla : public QGraphicsScene
{
public:
    explicit Tabla(QObject *parent = nullptr);
    void pozicionirajSto(sto *s);

public slots:
    void postaviSto(sto *s);


};

#endif // TABLA_H
