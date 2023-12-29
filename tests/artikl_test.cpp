#include <catch.hpp>
#include "../src/artikl.h"
TEST_CASE("Testing Artikl","[class]"){
    SECTION("Testing get naziv"){
        Artikl* a=new Artikl("cocacola",250,"sokovi");
        QString resenje="cocacola";
        QString naziv=a->getNaziv();

        REQUIRE(resenje==naziv);


    }

    SECTION("Testing get kategorija"){
        Artikl* a=new Artikl("cocacola",250,"sokovi");
        QString resenje="sokovi";
        QString kategorija=a->getKategorija();

        REQUIRE(resenje==kategorija);


    }

    SECTION("Testing get cena"){
        Artikl* a=new Artikl("cocacola",250,"sokovi");
        int resenje=250;
        int cena=a->getCena();

        REQUIRE(resenje==cena);


    }





}
