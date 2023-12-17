#ifndef BINARYSERIALIZER_H
#define BINARYSERIALIZER_H

#include "serializer.h"

class BinarySerializer : public Serializer
{
public:
    BinarySerializer() = default;

    void save(const Serializable& serializable, const QString& filePath) const override;
    void load(Serializable& serializable, const QString& filePath) const override;
};

#endif // BINARYSERIALIZER_H
