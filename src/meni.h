#ifndef MENI_H
#define MENI_H

#include "porudzbina.h"
#include "binaryserializer.h"
#include <QMap>
#include <QString>
#include <QComboBox>

class Meni : Serializable
{
public:
    Meni();
    ~Meni();

public slots:
    void printNamesInComboBox(QComboBox *cb);
    QMap<QString, Porudzbina*>* getMeni();
    void addCategory(QString naziv);

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    void executeLoad();
    void executeSave() const;

private:
    QMap<QString, Porudzbina*> _meni;
    Serializer *_binarySerializer;
};

#endif // MENI_H
