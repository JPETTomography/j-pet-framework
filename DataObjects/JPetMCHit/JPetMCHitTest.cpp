#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetMCHitTest
#include <boost/test/unit_test.hpp>

#include "./JPetMCHit/JPetMCHit.h"
#include "./JPetScin/JPetScin.h"
#include "./JPetBarrelSlot/JPetBarrelSlot.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetMCHit MChit;
  double epsilon = 0.0001;  
  BOOST_REQUIRE_CLOSE(MChit.getEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(MChit.getTime(), 0.0f, epsilon);
  
}

BOOST_AUTO_TEST_CASE(set_get_scalars_test){
  
  std::cout << "JPetMCHit test" << std::endl;

  JPetMCHit MChit;
  
  Float_t time = 0.1;
  //Float_t scin = 0.5;  //usunac 8.01
   //Int_t MCDecayTreeIndex = 1;  //added 8.01?
  
  MChit.setTime(time);
  //MChit.setScinPos(scin); //usunac 8.01
 // MChit.setMCDecayTreeIndex(dti); //added 8.01?

  BOOST_REQUIRE_EQUAL(MChit.getTime(), time);
  //BOOST_REQUIRE_EQUAL(MChit.getScinPos(), scin);//usunac 8.01
   //BOOST_REQUIRE_EQUAL(MChit.getMCDecayTreeIndex(),MCDecayTreeIndex); //added 8.01?
  
}

BOOST_AUTO_TEST_SUITE_END()
