#include "../src/artikl.h"
#include "../src/meni.h"
#include "../src/porudzbina.h"
#include "../src/raspored.h"
#include "../src/sto.h"
#include <catch.hpp>

TEST_CASE("Testing Raspored", "[class]") {
  SECTION("Testing dodaj sto") {

    Raspored *primer = new Raspored("raspored 1");
    Meni *meni = new Meni();
    primer->setMaxTables(5);

    qint32 expected = 2;

    primer->addSto(meni);
    primer->addSto(meni);

    qint32 result = primer->currentNumOfTables;

    REQUIRE(result == expected);

    delete primer;
    delete meni;
  }
  SECTION("Testing remove sto") {

    Raspored *primer = new Raspored("raspored 1");
    Meni *meni = new Meni();
    primer->setMaxTables(5);

    qint32 expected = 1;

    primer->addSto(meni);
    primer->addSto(meni);

    primer->removeSto(2);

    qint32 result = primer->currentNumOfTables;

    REQUIRE(result == expected);

    delete primer;
    delete meni;
  }
  SECTION("Testing clear all tables") {

    Raspored *primer = new Raspored("raspored 1");
    Meni *meni = new Meni();
    primer->setMaxTables(5);

    qint32 expected = 0;

    primer->addSto(meni);
    primer->addSto(meni);
    primer->addSto(meni);
    primer->addSto(meni);

    primer->clearSto();

    qint32 result = primer->currentNumOfTables;

    REQUIRE(result == expected);

    delete primer;
    delete meni;
  }
}
