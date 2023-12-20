#ifndef RASPOREDDATA_H
#define RASPOREDDATA_H

#include "raspored.h"
#include "serializer.h"
#include "glavnimeni.h"

#include <QMap>
#include <QString>

class RasporedData
{
public:
    RasporedData(const QString& dirPath);
    ~RasporedData();

    void addRaspored(const Raspored& raspored);
    void updateRaspored(const Raspored& raspored);
    void removeRaspored(const QString& rasporedName);

    void executeLoad();
    void executeSave() const;

public slots:
    void loadRaspored(GlavniMeni *ui, QGraphicsScene *mainView) const;
    void clearRaspored();

private:
    QMap<QString, Raspored*> m_rasporedi;
    Serializer *m_binarySerializer;
};

#endif // RASPOREDDATA_H
