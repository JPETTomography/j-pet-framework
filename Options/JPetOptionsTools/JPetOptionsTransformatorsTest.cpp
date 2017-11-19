#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetOptionsTest
#include <boost/test/unit_test.hpp>
#include "./JPetOptionsTools/JPetOptionsTools.h"
using boost::any_cast;
using namespace std;

using namespace jpet_options_tools;

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(checkIfFunctionsToTransformOptionWork)
{
  std::vector<int> firstOption = {1, 2};

  BOOST_REQUIRE_EQUAL(any_cast<int>(generateLowerEventBound(firstOption).second), 1);
  BOOST_REQUIRE_EQUAL(any_cast<int>(generateHigherEventBound(firstOption).second), 2);

  std::vector<int> secondOption = { -1, -2};

  BOOST_REQUIRE_EQUAL(any_cast<int>(generateLowerEventBound(secondOption).second), -1);
  BOOST_REQUIRE_EQUAL(any_cast<int>(generateHigherEventBound(secondOption).second), -1);

  std::string emptyPath = "";
  BOOST_REQUIRE_EQUAL(appendSlash(emptyPath).first, "outputPath_std::string");
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(appendSlash(emptyPath).second), "");

  std::string correctPath = "a/b/c/d/";
  BOOST_REQUIRE_EQUAL(appendSlash(correctPath).first, "outputPath_std::string");
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(appendSlash(correctPath).second), correctPath);

  std::string pathForCorrection = "a/b/c/d";
  BOOST_REQUIRE_EQUAL(appendSlash(pathForCorrection).first, "outputPath_std::string");
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(appendSlash(pathForCorrection).second), correctPath);

}

BOOST_AUTO_TEST_SUITE_END()
