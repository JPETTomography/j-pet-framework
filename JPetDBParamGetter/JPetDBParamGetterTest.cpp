#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetDBParamGetterTest
#include <boost/test/unit_test.hpp>
#include "../DBHandler/HeaderFiles/DBHandler.h"
#include "../JPetDBParamGetter/JPetDBParamGetter.h"
#include "../JPetParamManager/JPetParamManager.h"

const char* gDefaultConfigFile = "../DBConfig/configDB.cfg";

BOOST_AUTO_TEST_SUITE(DBParamGetterTS)

BOOST_AUTO_TEST_CASE(defaultConstructorTest)
{
  JPetDBParamGetter paramGetter;
}

BOOST_AUTO_TEST_CASE(basicDataTest)
{
  DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
  JPetDBParamGetter paramGetter;
  int run  = 1;
  ParamObjectsDescriptions descriptions = paramGetter.getAllBasicData(ParamObjectType::kLayer, run);

  BOOST_REQUIRE_EQUAL(descriptions.size(), 1);

  ParamObjectDescription & description = descriptions[1];
  BOOST_REQUIRE_EQUAL(description["id"], "1");
  BOOST_REQUIRE_EQUAL(description["active"], "1");
  BOOST_REQUIRE_EQUAL(description["name"], "Layer01");
  BOOST_REQUIRE_EQUAL(description["radius"], "40");
}

BOOST_AUTO_TEST_CASE(relationalDataTest)
{
  DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
  JPetDBParamGetter paramGetter;
  int run  = 1;
  ParamRelationalData relations = paramGetter.getAllRelationalData(ParamObjectType::kLayer, ParamObjectType::kFrame, run);

  BOOST_REQUIRE_EQUAL(relations.size(), 1);
  BOOST_REQUIRE_EQUAL(relations[1], 1);
}

BOOST_AUTO_TEST_CASE(tombRelationalDataTest)
{
  DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
  JPetDBParamGetter paramGetter;
  int run  = 1;
  ParamRelationalData relations = paramGetter.getAllRelationalData(ParamObjectType::kTOMBChannel, ParamObjectType::kTRB, run);

  BOOST_REQUIRE_EQUAL(relations.size(), 4);
  BOOST_REQUIRE_EQUAL(relations[111], 1);
  BOOST_REQUIRE_EQUAL(relations[112], 1);
  BOOST_REQUIRE_EQUAL(relations[113], 1);
  BOOST_REQUIRE_EQUAL(relations[114], 1);
}

BOOST_AUTO_TEST_CASE(run1Test)
{
  DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
  JPetParamManager paramManager(new JPetDBParamGetter());
  int run  = 1;
  paramManager.fillParameterBank(run);
  const JPetParamBank & bank = paramManager.getParamBank();
  BOOST_REQUIRE_EQUAL(bank.getScintillatorsSize(), 2);
  BOOST_REQUIRE_EQUAL(bank.getPMsSize(), 4);
  BOOST_REQUIRE_EQUAL(bank.getPMCalibsSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getBarrelSlotsSize(), 2);
  BOOST_REQUIRE_EQUAL(bank.getLayersSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getFramesSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getFEBsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getTRBsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getTOMBChannelsSize(), 4);
}

BOOST_AUTO_TEST_CASE(run28Test)
{
  DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
  JPetParamManager paramManager(new JPetDBParamGetter());
  int run  = 28;
  paramManager.fillParameterBank(run);
  const JPetParamBank & bank = paramManager.getParamBank();
  BOOST_REQUIRE(bank.getScintillatorsSize() > 0);
  BOOST_REQUIRE(bank.getPMsSize() > 0);
  BOOST_REQUIRE(bank.getPMCalibsSize() == 0);
  BOOST_REQUIRE(bank.getBarrelSlotsSize() == 2);
  BOOST_REQUIRE(bank.getLayersSize() == 1);
  BOOST_REQUIRE(bank.getFramesSize() == 1);
  BOOST_REQUIRE(bank.getFEBsSize() > 0);
  BOOST_REQUIRE(bank.getTRBsSize() > 0);
  BOOST_REQUIRE(bank.getTOMBChannelsSize() > 0);
}

BOOST_AUTO_TEST_SUITE_END()
