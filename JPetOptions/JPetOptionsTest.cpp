#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetOptionsTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetOptions/JPetOptions.h"

//JPetOptions
//public methods
//JPetOptions();
//explicit JPetOptions(const Options& opts);

//bool areCorrect(const Options& opts) const;
//const char* getInputFile() const;
//const char* getOutputFile() const;
//long long getFirstEvent() const;
//long long getLastEvent() const;
//int getRunNumber() const;
//bool isProgressBar() const;
//FileType getInputFileType() const;
//FileType getOutputFileType() const;
//inline Options getOptions() const;
//static  Options getDefaultOptions();

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( my_test1 )
{
  JPetOptions opts; 
  auto default_opts =  JPetOptions::getDefaultOptions();
  BOOST_REQUIRE(opts.getOptions() == default_opts);
}

BOOST_AUTO_TEST_CASE(petOptionsDefaultConstrutorTest)
{
    JPetOptions::Options options = {
        {"inputFile", ""},
        {"inputFileType", ""},
        {"outputFile", "root"},
        {"outputFileType", "test.root"},
        {"firstEvent", "-1"},
        {"lastEvent", "-1"},
        {"progressBar", "false"},
        {"runId", "-1"}
    };

    JPetOptions petOptions;
    BOOST_REQUIRE_EQUAL(CommonTools::mapComparator(petOptions.getOptions(), options), true);
}

BOOST_AUTO_TEST_CASE(petOptionsBasicTest)
{
    JPetOptions::Options options = {
        {"inputFile", "input"},
        {"outputFile", "output"},
        {"firstEvent", "8246821 0xffff 020"},
        {"lastEvent", "8246821 0xffff 020"},
        {"runId", "2001, A Space Odyssey"},
        {"progressBar", "true"},
        {"inputFileType", "root"},
        {"outputFileType", "scope"}
    };

    JPetOptions petOptions(options);
    BOOST_REQUIRE_EQUAL(petOptions.getInputFile(), "input");
    BOOST_REQUIRE_EQUAL(petOptions.getOutputFile(), "output");
    auto firstEvent = petOptions.getFirstEvent();
    BOOST_REQUIRE_EQUAL(firstEvent, 8246821);
    auto lastEvent = petOptions.getLastEvent();
    BOOST_REQUIRE_EQUAL(lastEvent, 8246821);
    int runNumberHex = petOptions.getRunNumber();
    BOOST_REQUIRE_EQUAL(runNumberHex, 2001);
    BOOST_REQUIRE_EQUAL(petOptions.isProgressBar(), true);
    BOOST_REQUIRE_EQUAL(petOptions.getInputFileType(), JPetOptions::FileType::kRoot);
    BOOST_REQUIRE_EQUAL(petOptions.getOutputFileType(), JPetOptions::FileType::kScope);
    BOOST_REQUIRE_EQUAL(CommonTools::mapComparator(petOptions.getOptions(), options), true);
    BOOST_REQUIRE_EQUAL(CommonTools::mapComparator(petOptions.getDefaultOptions(), options), false);
}

BOOST_AUTO_TEST_SUITE_END()
