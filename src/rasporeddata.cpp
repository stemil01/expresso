#include "rasporeddata.h"
#include "binaryserializer.h"

#include <iostream>

RasporedData::RasporedData(const QString &dirPath)
{
    m_binarySerializer = new BinarySerializer(dirPath);
}

RasporedData::~RasporedData()
{
    qDeleteAll(m_rasporedi);
    delete m_binarySerializer;
}

void RasporedData::addRaspored(const Raspored &raspored)
{
    if (m_rasporedi.contains(raspored.naziv)) {
        // TODO: add pop-up that says this
        std::cout << "arrangement with the same name already exists" << std::endl;
    }
    else {
        m_rasporedi[raspored.naziv] = new Raspored(raspored);
    }
}

void RasporedData::updateRaspored(const Raspored &raspored)
{
    if (!m_rasporedi.contains(raspored.naziv)) {
        // TODO: add pop-up that says this
        std::cout << "arrangement with the same name doesn't exist" << std::endl;
    }
    else {
        // check if this is necessary
        delete m_rasporedi[raspored.naziv];
        m_rasporedi[raspored.naziv] = new Raspored(raspored);
    }
}

void RasporedData::removeRaspored(const QString &rasporedName)
{
    delete m_rasporedi[rasporedName];
    m_rasporedi.remove(rasporedName);
}

void RasporedData::executeLoad()
{

}

void RasporedData::executeSave() const
{
    for (const auto& raspored : m_rasporedi) {
        m_binarySerializer->save(*raspored, raspored->naziv + ".bin");
    }
}
