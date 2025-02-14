#ifndef RASPORED_H
#define RASPORED_H

#include "serializable.h"
#include "sto.h"
#include <QString>

class Meni;

class Raspored : public Serializable {
public:
  Raspored() = default;
  Raspored(const QString &rasporedName);
  ~Raspored();

  QList<Sto *> getItems();

  QVariant toVariant() const override;
  void fromVariant(const QVariant &variant) override;
  void setMaxTables(qint32 num);
  qint32 getMaxTables();
  qint32 currentNumOfTables = 0;

  inline QString getNaziv() const { return m_naziv; }

  Sto *addSto(Meni *);
  void removeSto(qint32 idStola);
  void clearSto();
  void setMeni(Meni *meni);

private:
  QString m_naziv;
  qint32 m_idstola;
  qint32 m_max_tables;
  QList<Sto *> m_raspored;
};

#endif // RASPORED_H
