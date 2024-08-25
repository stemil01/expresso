#include "../src/rasporeddata.h"
#include <catch.hpp>

#include <QDir>

TEST_CASE("RasporedData", "[class]") {
  SECTION("Kada se ucitaju podaci, broj elementata je jedna broju fajlova u "
          "direktorijumu") {
    // Arrange
    QString dirPath = "../src/data/arrangemets";
    RasporedData rasporedData(dirPath);
    int brojUcitanihRasporeda = 0;

    QDir dir(dirPath);
    QStringList nameFilters;
    nameFilters << "*.bin";
    int brojFajlova = dir.entryInfoList(nameFilters).size();

    // Act
    rasporedData.executeLoad();
    brojUcitanihRasporeda = rasporedData.getRasporedi()->size();

    // Assert
    REQUIRE(brojUcitanihRasporeda == brojFajlova);
  }

  SECTION("Kada se sacuvaju podaci, broj elemenata je jednak broju fajlova u "
          "direktorijumu") {
    // Arrange
    QString dirPath = "../src/data/arrangemets";
    RasporedData rasporedData(dirPath);

    int brojRasporeda = rasporedData.getRasporedi()->size();
    int brojFajlova = 0;

    // Act
    rasporedData.executeSave();
    QDir dir(dirPath);
    QStringList nameFilters;
    nameFilters << "*.bin";
    brojFajlova = dir.entryInfoList(nameFilters).size();

    // Assert
    REQUIRE(brojRasporeda == brojFajlova);
  }
}
