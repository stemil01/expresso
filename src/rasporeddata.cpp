#include "rasporeddata.h"
#include "binaryserializer.h"
#include "glavnimeni.h"

#include <QDir>
#include <QFileInfo>
#include <iostream>

RasporedData::RasporedData(const QString &dirPath) {
  m_dirPath = dirPath;
  m_rasporedi = new QMap<QString, Raspored *>();
  m_binarySerializer = new BinarySerializer(dirPath);
}

RasporedData::~RasporedData() {
  qDeleteAll(*m_rasporedi);
  delete m_rasporedi;
  delete m_binarySerializer;
}

void RasporedData::addRaspored(Raspored *raspored) {
  if (m_rasporedi->contains(raspored->getNaziv())) {
    // TODO: add pop-up that says this
    std::cout << "arrangement with the same name already exists" << std::endl;
  } else {
    (*m_rasporedi)[raspored->getNaziv()] = raspored;
  }
}

void RasporedData::updateRaspored(const Raspored &raspored) {
  if (!m_rasporedi->contains(raspored.getNaziv())) {
    // TODO: add pop-up that says this
    std::cout << "arrangement with the same name doesn't exist" << std::endl;
  } else {
    // check if this is necessary
    delete (*m_rasporedi)[raspored.getNaziv()];
    (*m_rasporedi)[raspored.getNaziv()] = new Raspored(raspored);
  }
}

void RasporedData::removeRaspored(const QString &rasporedName) {
  delete m_rasporedi->value(rasporedName);
  m_rasporedi->remove(rasporedName);

  QDir dir(m_dirPath);
  QString filePath = m_dirPath + "/" + rasporedName + ".bin";

  if (!dir.remove(rasporedName + ".bin")) {
    qWarning() << "file " + rasporedName + ".bin wasn't deleted";
  }
}

Raspored *RasporedData::getRaspored(const QString &name) const {
  return m_rasporedi->value(name);
}

void RasporedData::setMeni(Meni *meni) {
  for (auto &raspored : *m_rasporedi) {
    raspored->setMeni(meni);
  }
}

void RasporedData::executeLoad() {
  QDir dir(m_dirPath);
  QStringList nameFilters;
  nameFilters << "*.bin";

  for (const auto &fileInfo : dir.entryInfoList(nameFilters)) {
    auto *raspored = new Raspored();
    m_binarySerializer->load(*raspored, fileInfo.fileName());
    m_rasporedi->insert(raspored->getNaziv(), raspored);
  }
}

void RasporedData::executeSave() const {
  for (const auto raspored : *m_rasporedi) {
    m_binarySerializer->save(*raspored, raspored->getNaziv() + ".bin");
  }
}
