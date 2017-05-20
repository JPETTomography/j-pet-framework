#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetOptionsTest
#include <boost/test/unit_test.hpp>
#include "../JPetOptions/JPetOptions.h"
#include "../JPetOptionsGenerator/JPetOptionsGenerator.h"
#include "../JPetOptionsGenerator/JPetOptionsTypeHandler.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( my_test1 )
{
  JPetOptions opts; 
  auto default_opts =  JPetOptionsGenerator::getDefaultOptions();
  JPetOptionsTypeHandler toComparison;
  BOOST_REQUIRE(JPetCommonTools::mapComparator(toComparison.anyMapToStringMap(opts.getOptions()), toComparison.anyMapToStringMap(default_opts)));
}

BOOST_AUTO_TEST_CASE(petOptionsBasicTest)
{
    JPetOptions::Options options = {
        {"inputFile_std::string", std::string("input")},
        {"scopeConfigFile_std::string", std::string("test.json")},
        {"scopeInputDirectory_std::string", std::string("scopeData")},
	    {"outputPath_std::string", std::string("/home/test")},
        {"outputFile_std::string", std::string("output")},
        {"firstEvent_int", 8246821},
        {"lastEvent_int", 8246821},
        {"runId_int", 2001},
        {"progressBar_bool", true},
        {"inputFileType_std::string", std::string("root")},
        {"outputFileType_std::string", std::string("scope")},
	    {"unpackerConfigFile_std::string", std::string("conf_trb3.xml")},
	    {"unpackerCalibFile_std::string", std::string("")}
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
    JPetOptionsTypeHandler toComparison;
    BOOST_REQUIRE_EQUAL(JPetCommonTools::mapComparator(toComparison.anyMapToStringMap(petOptions.getOptions()), toComparison.anyMapToStringMap(options)), true);
    BOOST_REQUIRE_EQUAL(JPetCommonTools::mapComparator(toComparison.anyMapToStringMap(JPetOptionsGenerator::getDefaultOptions()), toComparison.anyMapToStringMap(options)), false);
}

BOOST_AUTO_TEST_CASE(getTotalEventsTest)
{
    JPetOptions::Options options = {
        {"inputFile_std::string", std::string("input")},
        {"scopeConfigFile_std::string", std::string("test.json")},
        {"scopeInputDirectory_std::string", std::string("scopeData")},
        {"outputFile_std::string", std::string("output")},
        {"firstEvent_int", -1},
        {"lastEvent_int", -1},
        {"runId_int", 2001},
        {"progressBar_bool", true},
        {"inputFileType_std::string", std::string("root")},
        {"outputFileType_std::string", std::string("scope")},
        {"unpackerConfigFile_std::string", std::string("conf_trb3.xml")},
        {"unpackerCalibFile_std::string", std::string("")}
    };
    BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), -1);

    options.at("firstEvent_int")= 0;
    options.at("lastEvent_int")= -1;

    BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), -1);

    options.at("firstEvent_int")=0;
    options.at("lastEvent_int")=-1;
    BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), -1);

    options.at("firstEvent_int")= 0;
    options.at("lastEvent_int")= 0;
    BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), 1);

    options.at("firstEvent_int")= 0;
    options.at("lastEvent_int")= 1;
    BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), 2);

    options.at("firstEvent_int")= 7;
    options.at("lastEvent_int")= 9;
    BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), 3);

    options.at("firstEvent_int")= 6;
    options.at("lastEvent_int")= 5;
    BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), -1);

    options.at("firstEvent_int")= 9;
    options.at("lastEvent_int")= 5;
    BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), -1);
}
BOOST_AUTO_TEST_SUITE_END()
