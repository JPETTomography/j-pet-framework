#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetAuxilliaryDataTest
#include <boost/test/unit_test.hpp>


#include "../JPetAuxilliaryData/JPetAuxilliaryData.h"
#include "../JPetWriter/JPetWriter.h"
#include "../JPetReader/JPetReader.h"

             
BOOST_AUTO_TEST_SUITE(FirstSuite)
  
BOOST_AUTO_TEST_CASE( initial_state )
{
  JPetAuxilliaryData data1;
  BOOST_REQUIRE_EQUAL( data1.getValue("test", 0), JPetAuxilliaryData::Unset);
  BOOST_REQUIRE_EQUAL( data1.getValue("test", "key"), JPetAuxilliaryData::Unset);
  
  JPetAuxilliaryData data2("data2");
  BOOST_REQUIRE_EQUAL( data1.getValue("test2", 1), JPetAuxilliaryData::Unset);
  BOOST_REQUIRE_EQUAL( data1.getValue("test2", "key2"), JPetAuxilliaryData::Unset);
}

BOOST_AUTO_TEST_CASE( values_setting_and_retrieval )
{
  JPetAuxilliaryData data("data");

  data.createVector("myvec", 10);
  data.setValue("myvec", 0, -43.0);
  data.setValue("myvec", 9, -17.5);
  data.createMap("mydict");
  data.setValue("mydict", "key1", -43.0);
  data.setValue("mydict", "key2", -17.5);

  BOOST_REQUIRE_EQUAL(data.getValue("myvec", 0), -43.0);
  BOOST_REQUIRE_EQUAL(data.getValue("myvec", 9), -17.5);

  BOOST_REQUIRE_EQUAL(data.getValue("mydict", "key1"), -43.0);
  BOOST_REQUIRE_EQUAL(data.getValue("mydict", "key2"), -17.5);
}

BOOST_AUTO_TEST_CASE( container_limits )
{
  JPetAuxilliaryData data("data");

  data.createVector("myvec", 10);
  data.setValue("myvec", 0, -43.0);
  data.setValue("myvec", 9, -17.5);
  data.createMap("mydict");
  data.setValue("mydict", "key1", -43.0);
  data.setValue("mydict", "key2", -17.5);
  data.setValue("mydict2", "key1", 11.1);
  
  BOOST_REQUIRE_EQUAL(data.getValue("myvec", 1), JPetAuxilliaryData::Unset);
  BOOST_REQUIRE_EQUAL(data.getValue("myvec", 10), JPetAuxilliaryData::Unset);
  BOOST_REQUIRE_EQUAL(data.getValue("myvec2", 1), JPetAuxilliaryData::Unset);
  
  BOOST_REQUIRE_EQUAL(data.getValue("mydict2", "key1"), JPetAuxilliaryData::Unset);
  BOOST_REQUIRE_EQUAL(data.getValue("mydict", "key3"), JPetAuxilliaryData::Unset);
}

BOOST_AUTO_TEST_CASE( copying )
{
  JPetAuxilliaryData data("data");

  data.createVector("myvec", 10);
  data.setValue("myvec", 0, -43.0);
  data.setValue("myvec", 9, -17.5);
  data.createMap("mydict");
  data.setValue("mydict", "key1", -43.0);
  data.setValue("mydict", "key2", -17.5);

  JPetAuxilliaryData data2 = data;
  
  BOOST_REQUIRE_EQUAL(data2.getValue("myvec", 0), -43.0);
  BOOST_REQUIRE_EQUAL(data2.getValue("myvec", 9), -17.5);
  
  BOOST_REQUIRE_EQUAL(data2.getValue("mydict", "key1"), -43.0);
  BOOST_REQUIRE_EQUAL(data2.getValue("mydict", "key2"), -17.5);

  JPetAuxilliaryData data3(data);

  BOOST_REQUIRE_EQUAL(data3.getValue("myvec", 0), -43.0);
  BOOST_REQUIRE_EQUAL(data3.getValue("myvec", 9), -17.5);
  
  BOOST_REQUIRE_EQUAL(data3.getValue("mydict", "key1"), -43.0);
  BOOST_REQUIRE_EQUAL(data3.getValue("mydict", "key2"), -17.5);

}

BOOST_AUTO_TEST_CASE( file_storage )
{

  JPetAuxilliaryData data("data");

  data.createVector("myvec", 10);
  data.setValue("myvec", 0, -43.0);
  data.setValue("myvec", 9, -17.5);
  data.createMap("mydict");
  data.setValue("mydict", "key1", -43.0);
  data.setValue("mydict", "key2", -17.5);

  JPetWriter writer("unitTestData/auxdata.root");
  writer.writeObject(&data, "Auxilliary data 1");
  writer.closeFile();

  JPetReader reader;
  reader.openFileAndLoadData("unitTestData/auxdata.root", "tree");
  
  JPetAuxilliaryData * data2 = static_cast<JPetAuxilliaryData*>(reader.getObjectFromFile("Auxilliary data 1"));
  
  BOOST_REQUIRE_EQUAL(data2->getValue("myvec", 0), -43.0);
  BOOST_REQUIRE_EQUAL(data2->getValue("myvec", 9), -17.5);
  
  BOOST_REQUIRE_EQUAL(data2->getValue("mydict", "key1"), -43.0);
  BOOST_REQUIRE_EQUAL(data2->getValue("mydict", "key2"), -17.5);

  reader.closeFile();
}

BOOST_AUTO_TEST_SUITE_END()
