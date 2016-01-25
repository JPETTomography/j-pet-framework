// Param Data Test Suite - ParamData.h (Parameter Data)
#ifndef PARAM_DATA_TESTSUITE_H
#define PARAM_DATA_TESTSUITE_H

#define SHOW_DEBUG 0

#define BOOST_TEST_MODULE ParamDataTestSuite
#include <boost/test/included/unit_test.hpp>
#include "../HeaderFiles/ParamServer.h"
#include "../HeaderFiles/ParamData.h"
#include "DBHandlerHelper.cpp"


namespace DB
{

namespace TEST
{

class ParamDataTestSuite
{
protected:
  DB::SERVICES::DBHandler &m_dbHandlerInstance;
  DB::SERVER::ParamServer *m_paramServer;
  DB::DATA::ParamData *m_paramData;

public:
  ParamDataTestSuite(void);
  virtual ~ParamDataTestSuite(void);
};


ParamDataTestSuite::ParamDataTestSuite() :
                                          m_dbHandlerInstance(DBHandlerHelper::getInstance("../../Config/configDB.cfg")), // UWAGA
                                          m_paramServer(new DB::SERVER::ParamServer(DBHandlerHelper::getInstance("../../Config/configDB.cfg"))),
                                          m_paramData(new DB::DATA::ParamData(*m_paramServer))
{

}

ParamDataTestSuite::~ParamDataTestSuite()
{
  delete m_paramServer;
  DB::SERVICES::DBHandler::deleteInstance();  // do przemyslenia!
  delete m_paramData;
}

// Tests
BOOST_AUTO_TEST_SUITE(ParamDataTS)

BOOST_FIXTURE_TEST_CASE(checkTOMBInputIdFromTOMBInputMapTest, ParamDataTestSuite)
{
#if SHOW_DEBUG
  std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
#endif

  m_paramServer->TOMBInput_Map().fillMap(1);
#if SHOW_DEBUG
  m_paramServer->TOMBInput_Map().showMap();
#endif
  if( !m_paramServer->TOMBInput_Map().empty() )
  {
    std::pair<DB::DATA::TOMB_INPUT_MAP_KEY_TYPE, DB::DATA::TOMB_INPUT_MAP_VALUE_TYPE > l_firstElementFromTOMBInputMap = *m_paramServer->TOMBInput_Map().firstElement();
    DB::DATA::TOMB_INPUT_MAP_VALUE_TYPE l_TOMBInputIdFromTOMBInputMapFromParamData = *m_paramData->getTOMBInputIdFromTOMBInputMap(l_firstElementFromTOMBInputMap.first);
    DB::DATA::TOMB_INPUT_MAP_VALUE_TYPE l_TOMBInputIdFromTOMBInputMap = l_firstElementFromTOMBInputMap.second;
    bool l_whetherTheElementsAreEqual = ( l_TOMBInputIdFromTOMBInputMapFromParamData == l_TOMBInputIdFromTOMBInputMap );
    BOOST_REQUIRE( l_whetherTheElementsAreEqual == true );
  }
}

BOOST_FIXTURE_TEST_CASE(checkTRBIdAndTRBoutputIdFromTOMBInputMapTest, ParamDataTestSuite)
{
#if SHOW_DEBUG
  std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
#endif

  m_paramServer->TOMBInput_Map().fillMap(1);
#if SHOW_DEBUG
  m_paramServer->TOMBInput_Map().showMap();
#endif
  if( !m_paramServer->TOMBInput_Map().empty() )
  {
    std::pair<DB::DATA::TOMB_INPUT_MAP_KEY_TYPE, DB::DATA::TOMB_INPUT_MAP_VALUE_TYPE > l_firstElementFromTOMBInputMap = *m_paramServer->TOMBInput_Map().firstElement();
    DB::DATA::TOMB_INPUT_MAP_KEY_TYPE l_TRBIdAndTRBoutputIdFromTOMBInputMapFromParamData = *m_paramData->getTRBIdAndTRBoutputIdFromTOMBInputMap(l_firstElementFromTOMBInputMap.second);
    DB::DATA::TOMB_INPUT_MAP_KEY_TYPE l_TRBIdAndTRBoutputIdFromTOMBInputMap = l_firstElementFromTOMBInputMap.first;
    bool l_whetherTheElementsAreEqual = ( l_TRBIdAndTRBoutputIdFromTOMBInputMapFromParamData == l_TRBIdAndTRBoutputIdFromTOMBInputMap );
    BOOST_REQUIRE( l_whetherTheElementsAreEqual == true );
  }
}

BOOST_FIXTURE_TEST_CASE(checkTRBIdFromTOMBInputMapTest, ParamDataTestSuite)
{
#if SHOW_DEBUG
  std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
#endif

  m_paramServer->TOMBInput_Map().fillMap(1);
#if SHOW_DEBUG
  m_paramServer->TOMBInput_Map().showMap();
#endif
  if( !m_paramServer->TOMBInput_Map().empty() )
  {
    std::pair<DB::DATA::TOMB_INPUT_MAP_KEY_TYPE, DB::DATA::TOMB_INPUT_MAP_VALUE_TYPE > l_firstElementFromTOMBInputMap = *m_paramServer->TOMBInput_Map().firstElement();
    DB::DATA::TOMB_INPUT_MAP_KEY_TYPE l_TRBIdAndTRBoutputIdFromTOMBInputMapFromParamData = *m_paramData->getTRBIdAndTRBoutputIdFromTOMBInputMap(l_firstElementFromTOMBInputMap.second);
    DB::DATA::TOMB_INPUT_MAP_KEY_TYPE l_TRBIdAndTRBoutputIdFromTOMBInputMap = l_firstElementFromTOMBInputMap.first;
    bool l_whetherTheElementsAreEqual = ( l_TRBIdAndTRBoutputIdFromTOMBInputMapFromParamData.first == l_TRBIdAndTRBoutputIdFromTOMBInputMap.first );
    BOOST_REQUIRE( l_whetherTheElementsAreEqual == true );
  }
}

BOOST_FIXTURE_TEST_CASE(checkTRBoutputIdFromTOMBInputMapTest, ParamDataTestSuite)
{
#if SHOW_DEBUG
  std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
#endif

  m_paramServer->TOMBInput_Map().fillMap(1);
#if SHOW_DEBUG
  m_paramServer->TOMBInput_Map().showMap();
#endif
  if( !m_paramServer->TOMBInput_Map().empty() )
  {
    std::pair<DB::DATA::TOMB_INPUT_MAP_KEY_TYPE, DB::DATA::TOMB_INPUT_MAP_VALUE_TYPE > l_firstElementFromTOMBInputMap = *m_paramServer->TOMBInput_Map().firstElement();
    DB::DATA::TOMB_INPUT_MAP_KEY_TYPE l_TRBIdAndTRBoutputIdFromTOMBInputMapFromParamData = *m_paramData->getTRBIdAndTRBoutputIdFromTOMBInputMap(l_firstElementFromTOMBInputMap.second);
    DB::DATA::TOMB_INPUT_MAP_KEY_TYPE l_TRBIdAndTRBoutputIdFromTOMBInputMap = l_firstElementFromTOMBInputMap.first;
    bool l_whetherTheElementsAreEqual = ( l_TRBIdAndTRBoutputIdFromTOMBInputMapFromParamData.second == l_TRBIdAndTRBoutputIdFromTOMBInputMap.second );
    BOOST_REQUIRE( l_whetherTheElementsAreEqual == true );
  }
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace TEST

} // namespace DB

#endif // PARAM_DATA_TESTSUITE_H
