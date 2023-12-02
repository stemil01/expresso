#ifndef STOLOVI_H
#define STOLOVI_H
#include <QWidget>

class QGraphicsScene;
class stozaprikaz;

namespace Ui {
class stolovi;
}

class stolovi : public QWidget
{
    Q_OBJECT

public:
    stolovi(QWidget *parent = nullptr);
    ~stolovi();

signals:
    void dodatNovSto(stozaprikaz *);
    \
private slots:
    void dodajNovSto();
    void closeWindow();

private:
    Ui::stolovi *ui;
    QGraphicsScene *tabla;
    QVector<stozaprikaz *> _stolovi;
};

#endif // STOLOVI_H
