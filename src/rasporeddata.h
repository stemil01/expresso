#ifndef RASPOREDDATA_H
#define RASPOREDDATA_H

#include "raspored.h"
#include "serializer.h"

#include <QMap>
#include <QString>

class RasporedData
{
public:
    RasporedData() = default;

    void addRaspored(const Raspored& raspored);
    void updateRaspored(const Raspored& raspored);
    void removeRaspored(const QString& rasporedName);

    void executeLoad(const QString& dir);
    void executeSave(const QString& dir) const;

private:
    QMap<QString, Raspored*> m_rasporedi;
    Serializer *m_binarySerializer;
};

#endif // RASPOREDDATA_H
