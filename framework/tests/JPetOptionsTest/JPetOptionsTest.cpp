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

BOOST_AUTO_TEST_SUITE_END()
