#ifndef MENI_H
#define MENI_H

#include "porudzbina.h"
#include "binaryserializer.h"
#include "kategorija.h"
#include <QMap>
#include <QSet>
#include <QString>
#include <QComboBox>

class Meni : public Serializable
{
public:
    Meni();
    ~Meni();

    //QSet<QString> imenaKategorija;

public slots:
    void printNamesInComboBox(QComboBox *cb);
    QMap<QString, Porudzbina*>* getMeni();
    void addCategory(QString naziv);
    void addItem(const QString&,Artikl*);

    QMap<QString,Kategorija*> getKategorije();
    void deleteCategory(const QString& naziv);

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    void executeLoad();
    void executeSave() const;

private:
    //QList<Kategorija*> _kategorije;
    QMap<QString,Kategorija*> _kategorije;
    QMap<QString, Porudzbina*> _meni;
    Serializer *_binarySerializer;
};

#endif // MENI_H
