/**
  *  @copyright Copyright (c) 2014, J-PET collaboration 
  *  @file JPetCmdParserTest.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */ 
  #include "../JPetCmdParser/JPetCmdParser.h"
  
  #define BOOST_TEST_DYN_LINK
  #define BOOST_TEST_MODULE  JPetCmdParserTest
  #include <boost/test/unit_test.hpp>
  #include <cstdlib>

  BOOST_AUTO_TEST_SUITE(FirstSuite)

  BOOST_AUTO_TEST_CASE( parsing_correct )
  {
    const int argc = 10;
    const char * argv[argc];
    argv[0] = "test";
    argv[1] = "-t";
    argv[2] = "hld";
    argv[3] = "-r";
    argv[4] = "145";
    argv[5] = "180";
    argv[6] = "-f";
    argv[7] = "testfile.hld";
    argv[8] = "-p";
    argv[9] = "trbnumbers.blahblah";
    
    JPetCmdParser parser;
    parser.parse(argc, argv);
    BOOST_CHECK( parser.fileTypeIsSet() );
    BOOST_CHECK_EQUAL( (std::string)argv[2], parser.getFileType() );
    BOOST_CHECK_EQUAL( (std::string)argv[7], parser.getFileName() );
    BOOST_CHECK_EQUAL( atoi(argv[4]), parser.getLowerEventBound() );
    BOOST_CHECK_EQUAL( atoi(argv[5]), parser.getHigherEventBound() );
    BOOST_CHECK( parser.paramIsSet() );
    BOOST_CHECK_EQUAL( (std::string)argv[9], parser.getParam() );
  }

  BOOST_AUTO_TEST_SUITE_END()
  
