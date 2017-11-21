#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE HelperMathFunctionsTest
#include <boost/test/unit_test.hpp>
#include "./JPetSimplePhysSignalReco/HelperMathFunctions.h"
using namespace boost::numeric::ublas;

//float polynomialFit(const vector<float>& t, const vector<float>& v_source, int alfa, float v0)


BOOST_AUTO_TEST_SUITE(FirstSuite)
  
BOOST_AUTO_TEST_CASE( polynomialFitTest1  )
{
  vector<float> time(4);
  vector<float> volt(4);
    
  int alfa = 1;
  float v0 = -0.10;
    
  time(0) = 1035.0;   
  time(1) = 1542.0;
  time(2) = 2282.0;  
  time(3) = 2900.0;
    
  volt(0) = -0.06;
  volt(1) = -0.20;
  volt(2) = -0.35;  
  volt(3) = -0.50;
    
  float result = polynomialFit(time, volt,  alfa, v0);
  
  float epsilon = 0.1; 
  BOOST_REQUIRE_CLOSE(result, 1171.98, epsilon);
}

BOOST_AUTO_TEST_CASE( polynomialFitTest2  )
{
  vector<float> time(4);
  vector<float> volt(4);
    
  int alfa = 2;
  float v0 = -0.05;
    
  time(0) = 1035.0;   
  time(1) = 1542.0;
  time(2) = 2282.0;  
  time(3) = 2900.0;
    
  volt(0) = -0.06;
  volt(1) = -0.20;
  volt(2) = -0.35;  
  volt(3) = -0.50;
    
  float result = polynomialFit(time, volt,  alfa, v0);
  
  float epsilon = 0.1; 
  BOOST_REQUIRE_CLOSE(result, 793.1, epsilon);
  //BOOST_REQUIRE_EQUAL(result, 3);
}

BOOST_AUTO_TEST_SUITE_END()
