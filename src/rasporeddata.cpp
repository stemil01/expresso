#include "rasporeddata.h"

#include <iostream>

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
        m_rasporedi[raspored.naziv] = new Raspored(raspored);
    }
}

void RasporedData::removeRaspored(const QString &rasporedName)
{
    m_rasporedi.remove(rasporedName);
}
