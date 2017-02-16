#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetOptionsTest
#include <boost/test/unit_test.hpp>
#include "../JPetOptions/JPetOptions.h"

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
        {"scopeConfigFile",""},
        {"scopeInputDirectory",""},
	{"outputPath", ""},
        {"outputFile", "root"},
        {"outputFileType", "test.root"},
        {"firstEvent", "-1"},
        {"lastEvent", "-1"},
        {"progressBar", "false"},
        {"runId", "-1"},
	{"unpackerConfigFile", "conf_trb3.xml"},
	{"unpackerCalibFile", ""}
    };

    JPetOptions petOptions;
    BOOST_REQUIRE_EQUAL(JPetCommonTools::mapComparator(petOptions.getOptions(), options), true);
}

BOOST_AUTO_TEST_CASE(petOptionsBasicTest)
{
    JPetOptions::Options options = {
        {"inputFile", "input"},
        {"scopeConfigFile","test.json"},
        {"scopeInputDirectory","scopeData"},
	{"outputPath", "/home/test"},
        {"outputFile", "output"},
        {"firstEvent", "8246821 0xffff 020"},
        {"lastEvent", "8246821 0xffff 020"},
        {"runId", "2001, A Space Odyssey"},
        {"progressBar", "true"},
        {"inputFileType", "root"},
        {"outputFileType", "scope"},
	{"unpackerConfigFile", "conf_trb3.xml"},
	{"unpackerCalibFile", ""}
    };

    JPetOptions petOptions(options);
    BOOST_REQUIRE_EQUAL(petOptions.getInputFile(), "input");
    BOOST_REQUIRE_EQUAL(petOptions.getScopeConfigFile(), "test.json");
    BOOST_REQUIRE_EQUAL(petOptions.getScopeInputDirectory(), "scopeData");
    BOOST_REQUIRE_EQUAL(petOptions.getOutputPath(), "/home/test");
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
    BOOST_REQUIRE_EQUAL(JPetCommonTools::mapComparator(petOptions.getOptions(), options), true);
    BOOST_REQUIRE_EQUAL(JPetCommonTools::mapComparator(petOptions.getDefaultOptions(), options), false);
}

BOOST_AUTO_TEST_CASE(getTotalEventsTest)
{
    JPetOptions::Options options = {
        {"inputFile", "input"},
        {"scopeConfigFile","test.json"},
        {"scopeInputDirectory","scopeData"},
        {"outputFile", "output"},
        {"firstEvent", "-1"},
        {"lastEvent", "-1"},
        {"runId", "2001, A Space Odyssey"},
        {"progressBar", "true"},
        {"inputFileType", "root"},
        {"outputFileType", "scope"},
        {"unpackerConfigFile", "conf_trb3.xml"},
	{"unpackerCalibFile", ""}
    };

    BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), -1);

    options.at("firstEvent")="0";
    options.at("lastEvent")="-1";

    BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), -1);

    options.at("firstEvent")="0";
    options.at("lastEvent")="-1";
    BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), -1);

    options.at("firstEvent")= "0";
    options.at("lastEvent")= "0";
    BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), 1);

    options.at("firstEvent")= "0";
    options.at("lastEvent")= "1";
    BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), 2);

    options.at("firstEvent")= "7";
    options.at("lastEvent")= "9";
    BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), 3);

    options.at("firstEvent")= "6";
    options.at("lastEvent")= "5";
    BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), -1);

    options.at("firstEvent")= "9";
    options.at("lastEvent")= "5";
    BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), -1);
}
BOOST_AUTO_TEST_SUITE_END()
