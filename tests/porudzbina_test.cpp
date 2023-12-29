#include <catch.hpp>
#include "../src/artikl.h"
#include "../src/porudzbina.h"
TEST_CASE("Testing porudzbina","[class]"){
    SECTION("Testing obrisi po nazivu"){
        Artikl* a1=new Artikl("cocacola",250,"sokovi");
        Artikl* a2=new Artikl("fanta",200,"sokovi");
        Porudzbina* p = new Porudzbina();
        p->dodajArtikl(a1);
        p->dodajArtikl(a2);

        p->obrisiPoNazivu("cocacola");
        REQUIRE(p->getArtikli().size()==1);


        QString resenje="fanta";
        QString naziv=a2->getNaziv();
        REQUIRE(resenje==naziv);


    }

    SECTION("Testing obrisi artikle"){
        Artikl* a1=new Artikl("cocacola",250,"sokovi");
        Artikl* a2=new Artikl("fanta",200,"sokovi");
        Porudzbina* p = new Porudzbina();
        p->dodajArtikl(a1);
        p->dodajArtikl(a2);

        p->obrisiArtikle();

        REQUIRE(p->getArtikli().empty());

    }
    SECTION("Testing sacuvaj promenju"){
        Artikl* a1=new Artikl("cocacola",250,"sokovi");
        Porudzbina* p = new Porudzbina();
        p->dodajArtikl(a1);


        p->sacuvajPromenu("cocacola",5);

        QVector<Artikl*> artikli=p->getArtikli();
        REQUIRE(artikli[0].getKolicina()==5);

    }



}
