#ifndef RASPOREDDATA_H
#define RASPOREDDATA_H

#include "raspored.h"
#include "serializer.h"

#include <QMap>
#include <QString>

class GlavniMeni;

class RasporedData
{
public:
    RasporedData(const QString& dirPath);
    ~RasporedData();

    void addRaspored(Raspored *raspored);
    void updateRaspored(const Raspored& raspored);
    void removeRaspored(const QString& rasporedName);
    Raspored* getRaspored(const QString& name) const;

    inline QMap<QString, Raspored*>* getRasporedi() const { return m_rasporedi; }

    void executeLoad();
    void executeSave() const;

private:
    QString m_dirPath;
    QMap<QString, Raspored*> *m_rasporedi;
    Serializer *m_binarySerializer;
};

#endif // RASPOREDDATA_H
