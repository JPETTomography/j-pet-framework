#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetGeantParserToolsTest
#include <boost/test/unit_test.hpp>

#include "./JPetGeantParser/JPetGeantParserTools.h"
#include "./JPetGeantEventPack/JPetGeantEventPack.h"

JPetGeantEventPack* createPack(bool genPrompt, bool gen2g, bool gen3g ){
    JPetGeantEventPack* pack = new JPetGeantEventPack();

    if(genPrompt){
        JPetGeantScinHits* hit0 =  pack->ConstructNextHit();
        hit0->SetGenGammaMultiplicity(1);
        hit0->SetGenGammaIndex(1);
    }

    if(gen2g){
        for ( uint i=0; i <2; i++){
            JPetGeantScinHits* hit0 =  pack->ConstructNextHit();
            hit0->SetGenGammaMultiplicity(2);
            hit0->SetGenGammaIndex(i+1);
        }
    }

    if(gen3g){
        for ( uint i=0; i <3; i++){
            JPetGeantScinHits* hit0 =  pack->ConstructNextHit();
            hit0->SetGenGammaMultiplicity(3);
            hit0->SetGenGammaIndex(i+1);
        }
    }

    return pack;
} 

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( testIdentification )
{

    double epsilon = 0.0001;

    for (bool genPrompt : { false, true }) 
    {
        for (bool gen2g : { false, true }) 
        {
            for (bool gen3g : { false, true }) 
            {


                bool isRecPrompt = false;
                bool isRec2g = false;
                bool isRec3g = false;
                std::array<bool,2> isSaved2g{false,false};
                std::array<bool,3> isSaved3g{false,false};

                float enePrompt = 0.;
                std::array<float,2> ene2g{0.,0.};
                std::array<float,3> ene3g{0.,0.,0.} ;

                // generate only prompt
                JPetGeantEventPack* pack = createPack(genPrompt, gen2g, gen3g);

                for ( uint i=0; i < pack->GetNumberOfHits(); i++){
                    JPetHit  recHit; // does not matter if empty
                    JPetGeantParserTools::identifyRecoHits(pack->GetHit(i), recHit,
                            isRecPrompt, isSaved2g, isSaved3g,
                            enePrompt, ene2g, ene3g);
                }

                isRec2g = isSaved2g[0] && isSaved2g[1];
                isRec3g = isSaved3g[0] && isSaved3g[1] && isSaved3g[2];


                BOOST_REQUIRE_EQUAL(isRecPrompt, genPrompt);
                BOOST_REQUIRE_EQUAL(isRec2g, gen2g);
                BOOST_REQUIRE_EQUAL(isRec3g, gen3g);

                BOOST_REQUIRE_CLOSE(enePrompt,0.,epsilon);
                BOOST_REQUIRE_CLOSE(ene2g[1],0.,epsilon);
                BOOST_REQUIRE_CLOSE(ene3g[1],0.,epsilon);


            }

        }
    }

}


BOOST_AUTO_TEST_SUITE_END()
