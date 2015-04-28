#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetUnpackerTest
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#define private public
#include "../../JPetUnpacker/JPetUnpacker.h"
//JPetUnpacker();
//~JPetUnpacker();
//void exec();
//inline int getEventsToProcess() const;
//inline std::string getHldFile() const;
////inline std::string getCfgFile() const;
//void setParams(const std::string& hldFile, int numOfEvents = 100000, const std::string& cfgFile = "conf_trb3.xml");


BOOST_AUTO_TEST_SUITE(FirstSuite)

struct Fixture {
  Fixture(){
    // turning off cerr to get rid of Unpacker warnings
    std::cerr.setstate(std::ios_base::failbit);
  }
  ~Fixture() {

    boost::filesystem::remove("xx14099113231.hld.root");
  }
};

BOOST_AUTO_TEST_CASE( my_test )
{
  JPetUnpacker unpack;
  BOOST_REQUIRE(unpack.getEventsToProcess() == 0);
  BOOST_REQUIRE(unpack.getHldFile() == "");
  BOOST_REQUIRE(unpack.getCfgFile() == "");
  BOOST_REQUIRE(!unpack.exec());
}

BOOST_AUTO_TEST_CASE( my_test2 )
{
  JPetUnpacker unpack;
  unpack.setParams("test.hld", 10, "conf_test.xml");
  BOOST_REQUIRE(unpack.getEventsToProcess() == 10);
  BOOST_REQUIRE(unpack.getHldFile() == "test.hld");
  BOOST_REQUIRE(unpack.getCfgFile() == "conf_test.xml");
  BOOST_REQUIRE(!unpack.exec());
}

BOOST_FIXTURE_TEST_CASE( my_test3, Fixture )
{
  JPetUnpacker unpack;
  unpack.setParams("xx14099113231.hld", 10, "conf_trb3.xml");
  BOOST_REQUIRE(unpack.exec());
  BOOST_REQUIRE(unpack.getEventsToProcess() == 10);
  BOOST_REQUIRE(unpack.getHldFile() == "xx14099113231.hld");
  BOOST_REQUIRE(unpack.getCfgFile() == "conf_trb3.xml");
  BOOST_REQUIRE(unpack.exec());
}

BOOST_FIXTURE_TEST_CASE( my_test4, Fixture )
{
  JPetUnpacker unpack;
  unpack.setParams("xx14099113231.hld", 10, "conf_trb3.xml");
  BOOST_REQUIRE(unpack.exec());
  unpack.setParams("xx14099113231.hld", 10, "conf_trb.xml");
  BOOST_REQUIRE(!unpack.exec());
}

BOOST_AUTO_TEST_SUITE_END()
