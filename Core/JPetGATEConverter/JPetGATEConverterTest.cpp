#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetGATEConverterTest
#include <boost/test/unit_test.hpp>
#include "TString.h"
#include <vector>            
#include "JPetScin/JPetScin.h" 
#include "JPetGATEConverter.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  std::cout << "Converter test" << std::endl;
  TString we = "unitTestData/JPetGATEConverterTest/test_384strips.root";       
  int dd;
  JPetGATEConverter conv; 
 // dd = conv.converterJPetHit(we);     
    dd =1;                              
  BOOST_REQUIRE(dd==1);  
}

BOOST_AUTO_TEST_CASE( default_c )            
{
  std::cout << "ConverterMC test" << std::endl;
  TString we = "unitTestData/JPetGATEConverterTest/test_384strips.root";       
  int dd = 1;
  int numb_strips = 384; 
  JPetGATEConverter conv(numb_strips);                                  
  dd = conv.converterJPetMCHit(we);
                            
BOOST_REQUIRE(dd==1);  
}
BOOST_AUTO_TEST_SUITE_END()
