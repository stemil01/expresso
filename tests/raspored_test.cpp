#include <catch.hpp>
#include "../src/sto.h"
#include "../src/porudzbina.h"
#include "../src/artikl.h"
#include "../src/raspored.h"

TEST_CASE("Testing Raspored","[class]"){
    SECTION("Testing dodaj sto"){

        Raspored* primer = new Raspored("raspored 1");
        primer->setMaxTables(5);

        qint32 expected = 2;

        primer->addSto();
        primer->addSto();

        qint32 result = primer->currentNumOfTables;

        REQUIRE(result == expected);

        delete primer;
    }
}
