// Passed Information Map Test Suite - PassedInformationMapTestSuite.cpp
#ifndef PASSED_INFORMATION_MAP_TESTSUITE_H
#define PASSED_INFORMATION_MAP_TESTSUITE_H

#define SHOW_DEBUG 0

#define BOOST_TEST_MODULE PassedInformationMapTestSuite
#include <boost/test/included/unit_test.hpp>
#include "../HeaderFiles/PassedInformationMap.h"
#include "SerializableMapBT.hpp"


namespace DB
{

namespace TEST
{

class PassedInformationMapTestSuite : public SerializableMapBT<DATA::PassedInformationMap >
{
public:
  PassedInformationMapTestSuite(void);
  virtual ~PassedInformationMapTestSuite(void);
};


PassedInformationMapTestSuite::PassedInformationMapTestSuite() : SerializableMapBT<DATA::PassedInformationMap >()
{
}

PassedInformationMapTestSuite::~PassedInformationMapTestSuite()
{
}


// Tests
BOOST_AUTO_TEST_SUITE(PassedInformationMapTS)

BOOST_FIXTURE_TEST_CASE(fillPassedInformationMapCheckSizeTest, PassedInformationMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfPassedInformationMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfPassedInformationMap == 0 );

    m_map->fillMap(l_runId);

    l_sizeOfPassedInformationMap = m_map->sizeOfMap();

    std::string l_run_id = boost::lexical_cast<std::string>(l_runId);
    std::string l_sqlQuerry = "SELECT * FROM passedInformationIsTimeBasedOnTOMBInputIdFunction(" + l_run_id + ");";
    pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);

    size_t l_sizeResultQuerry = l_runDbResults.size();

  #if SHOW_DEBUG
      size_t l_sizeOfRunTable = getSizeOfRunTable();
      std::cout << "l_sizeOfRunTable = " << l_sizeOfRunTable << " l_sizeResultQuerry = " << l_sizeResultQuerry << " l_sizeOfPassedInformationMap = " << l_sizeOfPassedInformationMap << std::endl;
      m_map->showMap();
  #endif
      BOOST_REQUIRE( l_sizeResultQuerry == l_sizeOfPassedInformationMap );
  }
}

BOOST_FIXTURE_TEST_CASE(passedInformationForTOMBInputIdTest, PassedInformationMapTestSuite)
{
#if SHOW_DEBUG
  std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
#endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    std::string l_run_id = boost::lexical_cast<std::string>(l_runId);
    std::string l_sqlQuerry = "SELECT * FROM passedInformationIsTimeBasedOnTOMBInputIdFunction(" + l_run_id + ");";
    pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);

    size_t l_sizeResultQuerry = l_runDbResults.size();

  #if SHOW_DEBUG
    std::cout << "l_runDbResults.size() = " << l_sizeResultQuerry << std::endl;
  #endif

    if(l_sizeResultQuerry)
    {
      m_map->fillMap(l_runId);

      for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row)
      {
        DATA::PASSED_INFORMATION_MAP_KEY_TYPE l_tombinput_id = row["tombinput_id"].as<DATA::PASSED_INFORMATION_MAP_KEY_TYPE >();
        DATA::PASSED_INFORMATION_MAP_VALUE_TYPE l_konradBoardOutput_passedinformationistime = row["konradBoardOutput_passedinformationistime"].as<DATA::PASSED_INFORMATION_MAP_VALUE_TYPE>();

        DATA::PASSED_INFORMATION_MAP_VALUE_TYPE l_konradBoardOutput_passedinformationistimeFromPassedInformationMap = *m_map->valueFromMap(l_tombinput_id);

      #if SHOW_DEBUG
        std::cout << "l_tombinput_id = " << l_tombinput_id << " l_konradBoardOutput_passedinformationistime = " << l_konradBoardOutput_passedinformationistime << std::endl;
        std::cout << "l_konradBoardOutput_passedinformationistimeFromPassedInformationMap = " << l_konradBoardOutput_passedinformationistimeFromPassedInformationMap << std::endl;
      #endif
        BOOST_CHECK(l_konradBoardOutput_passedinformationistimeFromPassedInformationMap == l_konradBoardOutput_passedinformationistime);
      }
    }
  }
}

BOOST_FIXTURE_TEST_CASE(saveToFileAndRemoveFileWithPassedInformationMapTest, PassedInformationMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfPassedInformationMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfPassedInformationMap == 0 );

    m_map->fillMap(l_runId);
    std::string l_fileNameToSavePassedInformationMap = "PassedInformationMap.txt";
    m_map->saveMapToFile(l_fileNameToSavePassedInformationMap);

    bool l_removeFileWithPassedInformationMapSuccessfuly = m_map->removeFileWithMap();
    BOOST_CHECK(l_removeFileWithPassedInformationMapSuccessfuly == false);
  }
}

BOOST_FIXTURE_TEST_CASE(clearPassedInformationMapTest, PassedInformationMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfPassedInformationMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfPassedInformationMap == 0 );

    m_map->fillMap(l_runId);

    l_sizeOfPassedInformationMap = m_map->sizeOfMap();

    if(l_sizeOfPassedInformationMap > 0)
    {
  #if SHOW_DEBUG
      std::cout << "l_sizeOfPassedInformationMap = " << l_sizeOfPassedInformationMap << std::endl;
  #endif
      m_map->clearMap();
      BOOST_REQUIRE( m_map->sizeOfMap() == 0 );
    }
  }
}

BOOST_FIXTURE_TEST_CASE(checkIfExistFirstElementAndEraseElementFromTRBThresholdMapTest, PassedInformationMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfPassedInformationMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfPassedInformationMap == 0 );

    m_map->fillMap(l_runId);

    if(m_map->firstElement() != boost::none)
    {
      l_sizeOfPassedInformationMap = m_map->sizeOfMap();
      std::pair<DATA::PASSED_INFORMATION_MAP_KEY_TYPE, DATA::PASSED_INFORMATION_MAP_VALUE_TYPE > l_firstElementFromPassedInformationMap = *m_map->firstElement();
      DATA::PASSED_INFORMATION_MAP_KEY_TYPE l_firstKeyFromPassedInformationMap = l_firstElementFromPassedInformationMap.first;

  #if SHOW_DEBUG
      m_map->showMap();
      std::cout << "l_firstKeyFromPassedInformationMap = " << l_firstKeyFromPassedInformationMap << std::endl;
  #endif
      m_map->eraseElementFromMap(l_firstKeyFromPassedInformationMap);
      BOOST_CHECK( m_map->sizeOfMap() == (l_sizeOfPassedInformationMap - 1) );
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace TEST

} // namespace DB

#endif // PASSED_INFORMATION_MAP_TESTSUITE_H
