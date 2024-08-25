#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QString>
#include <QVariant>

class Serializable {
public:
  virtual ~Serializable() = default;

  virtual QVariant toVariant() const = 0;
  virtual void fromVariant(const QVariant &variant) = 0;
};

#endif // SERIALIZABLE_H
