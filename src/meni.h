#ifndef MENI_H
#define MENI_H

#include "binaryserializer.h"
#include "kategorija.h"
#include "porudzbina.h"
#include <QComboBox>
#include <QMap>
#include <QSet>
#include <QString>

class Meni : public Serializable {
public:
  Meni();
  ~Meni();

  // QSet<QString> imenaKategorija;

public slots:
  void printNamesInComboBox(QComboBox *cb);
  // QMap<QString, Porudzbina*>* getMeni();
  void addCategory(QString naziv);
  int addItem(const QString &, Artikl *);

  QMap<QString, Kategorija *> getKategorije();
  void deleteCategory(const QString &naziv);
  void deleteItem(const QString &, Artikl *);

  QVariant toVariant() const override;
  void fromVariant(const QVariant &variant) override;

  void executeLoad();
  void executeSave() const;

private:
  // QList<Kategorija*> _kategorije;
  QMap<QString, Kategorija *> _kategorije;
  // QMap<QString, Porudzbina*> _meni;
  Serializer *_binarySerializer;
};

#endif // MENI_H
