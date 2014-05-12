// TRB Threshold Map Test Suite - TRBThresholdMapTestSuite.cpp
#ifndef TRB_THRESHOLD_MAP_TESTSUITE_H
#define TRB_THRESHOLD_MAP_TESTSUITE_H

#define SHOW_DEBUG 0

#define BOOST_TEST_MODULE TRBThresholdMapTestSuite
#include <boost/test/included/unit_test.hpp>
#include <boost/lexical_cast.hpp>
#include "../HeaderFiles/TRBThresholdMap.h"
#include "SerializableMapBT.hpp"


namespace DB
{

namespace TEST
{

class TRBThresholdMapTestSuite : public SerializableMapBT<DATA::TRBThresholdMap >
{
public:
  TRBThresholdMapTestSuite(void);
  virtual ~TRBThresholdMapTestSuite(void);
};


TRBThresholdMapTestSuite::TRBThresholdMapTestSuite() : SerializableMapBT<DATA::TRBThresholdMap >()
{
}

TRBThresholdMapTestSuite::~TRBThresholdMapTestSuite()
{
}


// Tests
BOOST_AUTO_TEST_SUITE(PhotoMultiplierMapTS)

BOOST_FIXTURE_TEST_CASE(fillPhotoMultiplierMapCheckSizeTest, TRBThresholdMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfTRBThresholdMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfTRBThresholdMap == 0 );

    m_map->fillMap(l_runId);

    l_sizeOfTRBThresholdMap = m_map->sizeOfMap();

    std::string l_run_id = boost::lexical_cast<std::string>(l_runId);
    std::string l_sqlQuerry = "SELECT * FROM thresholdFromTRBConfigEntryBasedOnTOMBInputIdFunction(" + l_run_id + ");";
    pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);

    size_t l_sizeResultQuerry = l_runDbResults.size();

  #if SHOW_DEBUG
      size_t l_sizeOfRunTable = getSizeOfRunTable();
      std::cout << "l_sizeOfRunTable = " << l_sizeOfRunTable << " l_sizeResultQuerry = " << l_sizeResultQuerry << " l_sizeOfTRBThresholdMap = " << l_sizeOfTRBThresholdMap << std::endl;
      m_map->showMap();
  #endif
      BOOST_REQUIRE( l_sizeResultQuerry == l_sizeOfTRBThresholdMap );
  }
}

BOOST_FIXTURE_TEST_CASE(thresholdForTOMBInputIdTest, TRBThresholdMapTestSuite)
{
#if SHOW_DEBUG
  std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
#endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    std::string l_run_id = boost::lexical_cast<std::string>(l_runId);
    std::string l_sqlQuerry = "SELECT * FROM thresholdFromTRBConfigEntryBasedOnTOMBInputIdFunction(" + l_run_id + ");";
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
        DATA::TRB_THRESHOLD_MAP_KEY_TYPE l_tombinput_id = row["tombinput_id"].as<DATA::TRB_THRESHOLD_MAP_KEY_TYPE >();
        DATA::TRB_THRESHOLD_MAP_VALUE_TYPE l_trbconfigentry_threshold = row["trbconfigentry_threshold"].as<DATA::TRB_THRESHOLD_MAP_VALUE_TYPE >();

        DATA::TRB_THRESHOLD_MAP_VALUE_TYPE l_trbconfigentryThresholdFromTRBThresholdMap = *m_map->valueFromMap(l_tombinput_id);

      #if SHOW_DEBUG
        std::cout << "l_tombinput_id = " << l_tombinput_id << " l_trbconfigentry_threshold = " << l_trbconfigentry_threshold << std::endl;
        std::cout << "l_trbconfigentryThresholdFromTRBThresholdMap = " << l_trbconfigentryThresholdFromTRBThresholdMap << std::endl;
      #endif
        BOOST_CHECK(l_trbconfigentryThresholdFromTRBThresholdMap == l_trbconfigentry_threshold);
      }
    }
  }
}

BOOST_FIXTURE_TEST_CASE(saveToFileAndRemoveFileWithTRBThresholdMapTest, TRBThresholdMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfTRBThresholdMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfTRBThresholdMap == 0 );

    m_map->fillMap(l_runId);
    std::string l_fileNameToSaveTRBThresholdMap = "TRBThresholdMap.txt";
    m_map->saveMapToFile(l_fileNameToSaveTRBThresholdMap);

    bool l_removeFileWithTRBThresholdMapSuccessfuly = m_map->removeFileWithMap();
    BOOST_CHECK(l_removeFileWithTRBThresholdMapSuccessfuly == false);
  }
}

BOOST_FIXTURE_TEST_CASE(clearTRBThresholdMapTest, TRBThresholdMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfTRBThresholdMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfTRBThresholdMap == 0 );

    m_map->fillMap(l_runId);

    l_sizeOfTRBThresholdMap = m_map->sizeOfMap();

    if(l_sizeOfTRBThresholdMap > 0)
    {
  #if SHOW_DEBUG
      std::cout << "l_sizeOfTRBThresholdMap = " << l_sizeOfTRBThresholdMap << std::endl;
  #endif
      m_map->clearMap();
      BOOST_REQUIRE( m_map->sizeOfMap() == 0 );
    }
  }
}

BOOST_FIXTURE_TEST_CASE(checkIfExistFirstElementAndEraseElementFromTRBThresholdMapTest, TRBThresholdMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfTRBThresholdMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfTRBThresholdMap == 0 );

    m_map->fillMap(l_runId);

    if(m_map->firstElement() != boost::none)
    {
      l_sizeOfTRBThresholdMap = m_map->sizeOfMap();
      std::pair<DATA::TRB_THRESHOLD_MAP_KEY_TYPE, DATA::TRB_THRESHOLD_MAP_VALUE_TYPE > l_firstElementFromTRBThresholdMap = *m_map->firstElement();
      DATA::TRB_THRESHOLD_MAP_KEY_TYPE l_firstKeyFromTRBThresholdMap = l_firstElementFromTRBThresholdMap.first;

  #if SHOW_DEBUG
      m_map->showMap();
      std::cout << "l_firstKeyFromTRBThresholdMap = " << l_firstKeyFromTRBThresholdMap << std::endl;
  #endif
      m_map->eraseElementFromMap(l_firstKeyFromTRBThresholdMap);
      BOOST_CHECK( m_map->sizeOfMap() == (l_sizeOfTRBThresholdMap - 1) );
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace TEST

} // namespace DB

#endif // TRB_THRESHOLD_MAP_TESTSUITE_H
