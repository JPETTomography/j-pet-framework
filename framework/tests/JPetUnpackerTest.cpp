/**
  *  @copyright Copyright (c) 2014, J-PET collaboration 
  *  @file JPetUnpackerTest.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */ 
  #include "../JPetUnpacker/JPetUnpacker.h"
  
  #define BOOST_TEST_DYN_LINK
  #define BOOST_TEST_MODULE  JPetUnpackerTest
  #include <boost/test/unit_test.hpp>
  
  BOOST_AUTO_TEST_SUITE(FirstSuite)
  
  
  BOOST_AUTO_TEST_CASE( my_test )
  {
    BOOST_CHECK( 2 == 1 );
  }
  
  BOOST_AUTO_TEST_SUITE_END()
  
