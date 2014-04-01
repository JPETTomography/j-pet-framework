// Run Data Map Test Suite - RunDataMapTestSuite.cpp
#ifndef RUN_DATA_MAP_TESTSUITE_H
#define RUN_DATA_MAP_TESTSUITE_H

#define SHOW_DEBUG 0

#define BOOST_TEST_MODULE RunDataMapTestSuite
#include <boost/test/included/unit_test.hpp>
#include "../HeaderFiles/RunDataMap.h"
#include "SerializableMapBT.hpp"


namespace DB
{

namespace TEST
{

class RunDataMapTestSuite : public SerializableMapBT<DATA::RunDataMap >
{
public:
  RunDataMapTestSuite(void);
  virtual ~RunDataMapTestSuite(void);
};


RunDataMapTestSuite::RunDataMapTestSuite() : SerializableMapBT<DATA::RunDataMap >()
{
}

RunDataMapTestSuite::~RunDataMapTestSuite()
{
}


// Tests
BOOST_AUTO_TEST_SUITE(RunDataMapTS)

BOOST_FIXTURE_TEST_CASE(fillRunDataMapCheckSizeTest, RunDataMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  size_t l_sizeOfRunTable = getSizeOfRunTable();

  if(l_sizeOfRunTable > 0)
  {
    size_t l_sizeOfRunDataMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfRunDataMap == 0 );

    m_map->fillMap();

    l_sizeOfRunDataMap = m_map->sizeOfMap();

  #if SHOW_DEBUG
    std::cout << "l_sizeOfRunTable = " << l_sizeOfRunTable << " l_sizeOfRunDataMap = " << l_sizeOfRunDataMap << std::endl;
    m_map->showMap();
  #endif
    BOOST_REQUIRE( l_sizeOfRunTable == l_sizeOfRunDataMap );
  }
}

BOOST_FIXTURE_TEST_CASE(runDataTest, RunDataMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  std::string l_sqlQuerry = "select * from runDataFunction()";
  pqxx::result l_sqlResults = m_dbHandlerInstance.querry(l_sqlQuerry);

  size_t l_sqlResultsSize = l_sqlResults.size();

  #if SHOW_DEBUG
    std::cout << "l_sqlResults.size() = " << l_sqlResultsSize << std::endl;
  #endif

  if(l_sqlResultsSize)
  {
    m_map->fillMap();

    for(pqxx::result::const_iterator row = l_sqlResults.begin(); row != l_sqlResults.end(); ++row)
    {
      int l_runId = row["run_id"].as<int>();
      std::string l_runStart = row["runstart"].as<std::string>();
      std::string l_filePath = row["filepath"].as<std::string>();
      std::string l_runDescription = row["rundescription"].as<std::string>();
      std::string l_information = row["information"].as<std::string>();

      DATA::RUN_DATA_MAP_VALUE_TYPE l_runData = *m_map->valueFromMap(l_runId);

  #if SHOW_DEBUG
    std::cout << l_runData;
  #endif

      BOOST_CHECK(l_runData.runStart() == l_runStart);
      BOOST_CHECK(l_runData.filePath() == l_filePath);
      BOOST_CHECK(l_runData.runDescription() == l_runDescription);
      BOOST_CHECK(l_runData.information() == l_information);
    }
  }
}

BOOST_FIXTURE_TEST_CASE(saveToFileAndRemoveFileWithRunDataMapTest, RunDataMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  size_t l_sizeOfRunDataMap = m_map->sizeOfMap();
  BOOST_REQUIRE( l_sizeOfRunDataMap == 0 );

  m_map->fillMap();
  std::string l_fileNameToSaveRunDataMap = "RunDataMap.txt";
  m_map->saveMapToFile(l_fileNameToSaveRunDataMap);

  bool l_removeFileWithRunDataMapSuccessfuly = m_map->removeFileWithMap();
  BOOST_CHECK(l_removeFileWithRunDataMapSuccessfuly == false);
}

BOOST_FIXTURE_TEST_CASE(clearRunDataMapTest, RunDataMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  size_t l_sizeOfRunDataMap = m_map->sizeOfMap();
  BOOST_REQUIRE( l_sizeOfRunDataMap == 0 );

  m_map->fillMap();

  l_sizeOfRunDataMap = m_map->sizeOfMap();

  if(l_sizeOfRunDataMap > 0)
  {
  #if SHOW_DEBUG
    std::cout << "l_sizeOfRunDataMap = " << l_sizeOfRunDataMap << std::endl;
  #endif
    m_map->clearMap();
    BOOST_REQUIRE( m_map->sizeOfMap() == 0 );
  }
}

BOOST_FIXTURE_TEST_CASE(checkIfExistFirstElementAndEraseElementFromRunDataMapTest, RunDataMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  size_t l_sizeOfRunDataMap = m_map->sizeOfMap();
  BOOST_REQUIRE( l_sizeOfRunDataMap == 0 );

  m_map->fillMap();

  //if(m_map->firstElement() != boost::none) // ??
  {
    l_sizeOfRunDataMap = m_map->sizeOfMap();
    std::pair<DATA::RUN_DATA_MAP_KEY_TYPE, DATA::RUN_DATA_MAP_VALUE_TYPE > l_firstElementFromRunDataMap = *m_map->firstElement();
    DATA::RUN_DATA_MAP_KEY_TYPE l_firstKeyFromRunDataMap = l_firstElementFromRunDataMap.first;

  #if SHOW_DEBUG
    m_map->showMap();
    std::cout << "l_firstKeyFromRunDataMap = " << l_firstKeyFromRunDataMap << std::endl;
  #endif
    m_map->eraseElementFromMap(l_firstKeyFromRunDataMap);
    BOOST_CHECK( m_map->sizeOfMap() == (l_sizeOfRunDataMap - 1) );
  }
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace TEST

} // namespace DB

#endif // RUN_DATA_MAP_TESTSUITE_H
