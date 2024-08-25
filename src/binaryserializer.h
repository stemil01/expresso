#ifndef BINARYSERIALIZER_H
#define BINARYSERIALIZER_H

#include "serializer.h"

class BinarySerializer : public Serializer {
public:
  BinarySerializer(const QString &dirPath);

  void save(const Serializable &serializable,
            const QString &fileName) const override;
  void load(Serializable &serializable, const QString &fileName) const override;

private:
  QString m_dirPath;
};

#endif // BINARYSERIALIZER_H
