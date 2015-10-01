/**
  *  @copyright Copyright (c) 2014, J-PET collaboration
  *  @file JPetCmdParserTest.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetCmdParserTest
#include <boost/test/unit_test.hpp>
#include <cstdlib>
#define private public
#include "../../JPetCmdParser/JPetCmdParser.h"

//public method
//std::vector<JPetOptions> parseAndGenerateOptions(int argc, const char** argv);

char* convertStringToCharP(const std::string& s)
{
  char* pc = new char[s.size() + 1];
  std::strcpy(pc, s.c_str());
  return pc;
}

std::vector<char*> createArgs(const std::string& commandLine) 
{
  std::istringstream iss(commandLine);
  std::vector<std::string> args {std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>{}
                                };
  std::vector<char*> args_char;
  std::transform(args.begin(), args.end(), std::back_inserter(args_char), convertStringToCharP);
  return args_char;
}

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( parsing_1 )
{
  auto commandLine = "main.x -t hld -f testfile.hld -i 10";
  auto args_char = createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  JPetCmdParser parser;
  auto options = parser.parseAndGenerateOptions(argc, const_cast<const char**>(argv));
  BOOST_REQUIRE_EQUAL(options.size(), 1);
  auto option = options.at(0);
  BOOST_REQUIRE(std::string(option.getInputFile()) == "testfile.hld");
  BOOST_REQUIRE_EQUAL(option.getFirstEvent(), -1);
  BOOST_REQUIRE_EQUAL(option.getLastEvent(), -1);
  BOOST_REQUIRE_EQUAL(option.getRunNumber(), 10);
  BOOST_REQUIRE(!option.isProgressBar());
  BOOST_REQUIRE_EQUAL(option.getInputFileType(), JPetOptions::kHld);
}

BOOST_AUTO_TEST_CASE( parsing_2 )
{
  auto commandLine = "main.x -t scope -f testfile.json ";
  auto args_char = createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  JPetCmdParser parser;
  auto options = parser.parseAndGenerateOptions(argc, const_cast<const char**>(argv));
  BOOST_REQUIRE_EQUAL(options.size(), 1);
  auto option = options.at(0);
  BOOST_REQUIRE(std::string(option.getInputFile()) == "testfile.json");
  BOOST_REQUIRE_EQUAL(option.getFirstEvent(), -1);
  BOOST_REQUIRE_EQUAL(option.getLastEvent(), -1);
  BOOST_REQUIRE_EQUAL(option.getRunNumber(), -1);
  BOOST_REQUIRE(!option.isProgressBar());
  BOOST_REQUIRE_EQUAL(option.getInputFileType(), JPetOptions::kScope);
}

BOOST_AUTO_TEST_SUITE_END()
