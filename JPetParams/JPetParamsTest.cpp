#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamsTest
#include <boost/test/unit_test.hpp>
#include <boost/any.hpp>

#include "../JPetParams/JPetParams.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(defaultConstr)
{
  JPetParams params;

  BOOST_REQUIRE(params.getParamManager() == nullptr);
  BOOST_REQUIRE(params.getOptions().empty());
}

BOOST_AUTO_TEST_CASE(nonDefaultConstr)
{
  jpet_options_tools::OptsStrAny opts;
  opts["blaOption"] = std::string("value");
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager);
  JPetParams params(opts, mgr);
  BOOST_REQUIRE_EQUAL(params.getParamManager(), mgr.get());
  BOOST_REQUIRE_EQUAL(params.getOptions().size(), 1u);
}

BOOST_AUTO_TEST_CASE(copyCtr)
{
  jpet_options_tools::OptsStrAny opts;
  opts["blaOption"] = std::string("value");
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager);
  JPetParams params(opts, mgr);
  auto params2 = params;
  BOOST_REQUIRE_EQUAL(params2.getParamManager(), mgr.get());
  BOOST_REQUIRE_EQUAL(params2.getOptions().size(), params.getOptions().size());
}

BOOST_AUTO_TEST_CASE(memoryLeaks)
{
  jpet_options_tools::OptsStrAny opts;
  opts["blaOption"] = std::string("value");
  JPetParams* params = new JPetParams(opts, std::make_shared<JPetParamManager>(new JPetParamManager));
  auto mgr = params->getParamManager();
  delete params;
  BOOST_REQUIRE(mgr != nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
