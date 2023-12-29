#include <catch.hpp>
#include "../src/sto.h"
#include "../src/porudzbina.h"
#include "../src/artikl.h"
#include "../src/glavnimeni.h"
//#include "../src/raspored.h"
#include <QGraphicsScene>

class GlavniMeniTest : public GlavniMeni
{
public:
    using GlavniMeni::dodajNovSto;
    using GlavniMeni::obrisiSto;
    using GlavniMeni::tabla;
    using GlavniMeni::m_currentRaspored;
};

TEST_CASE("Testing Sto","[class]"){
    SECTION("Testing id"){

        Sto* sto = new Sto();
        qint32 expected = 1;


        qint32 result = sto->getId();

        REQUIRE(result == expected);

        delete sto;
    }
    SECTION("Testing resetId"){

        Sto::resetNextId();
        Sto* sto = new Sto();

        qint32 expected = 1;


        qint32 result = sto->getId();

        REQUIRE(result == expected);

        delete sto;
    }
    SECTION("Testing porudzbina in sto"){

        Sto* sto = new Sto();
        Artikl* artikl = new Artikl("Fanta",80.0,"Sokovi",10);
        Porudzbina* p = new Porudzbina();

        p->dodajArtikl(artikl);
        sto->setPorudzbina(p);

        Porudzbina* result = sto->getPorudzbina();

        REQUIRE(result != nullptr);

        delete sto;

    }
}
