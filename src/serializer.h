#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "serializable.h"

class Serializer
{
public:
    virtual ~Serializer() = default;

    virtual void save(const Serializable& serializable, const QString& fileName) const = 0;
    virtual void load(Serializable& serializable, const QString& fileName) const = 0;
};

#endif // SERIALIZER_H
