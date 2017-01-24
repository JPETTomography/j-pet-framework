#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetOptionsTest
#include <boost/test/unit_test.hpp>
#include "../JPetOptionsJson/JPetOptionsJson.h"
#include <boost/filesystem.hpp>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( test_1_createFileFromOptions ){
	JPetOptions options;
	JPetOptionsJson::createFileFromOptions(options);
	BOOST_CHECK(boost::filesystem::exists("options.json"));
}

BOOST_AUTO_TEST_CASE( test_2_createFileFromOptions ){
	JPetOptions options;
	//CmdParser::generateOption
	//tu można tworzyć- przyjrzyj się tej funkcji
}

BOOST_AUTO_TEST_SUITE_END()
