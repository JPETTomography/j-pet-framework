// TOMB Input Map Test Suite - TOMBInputMapTestSuite.cpp
#ifndef TOMB_INPUT_MAP_TESTSUITE_H
#define TOMB_INPUT_MAP_TESTSUITE_H

#define SHOW_DEBUG 0

#define BOOST_TEST_MODULE TOMBInuptMapTestSuite
#include <boost/test/included/unit_test.hpp>
#include "../HeaderFiles/TOMBInputMap.h"
#include "SerializableMapBT.hpp"


namespace DB
{

namespace TEST
{

class TOMBInputMapTestSuite : public SerializableMapBT<DATA::TOMBInputMap >
{
public:
  TOMBInputMapTestSuite(void);
  virtual ~TOMBInputMapTestSuite(void);
};


TOMBInputMapTestSuite::TOMBInputMapTestSuite() : SerializableMapBT<DATA::TOMBInputMap >()
{
}

TOMBInputMapTestSuite::~TOMBInputMapTestSuite()
{
}


// Tests
BOOST_AUTO_TEST_SUITE(TOMBInputMapTS)

BOOST_FIXTURE_TEST_CASE(fillPhotoMultiplierMapCheckSizeTest, TOMBInputMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfTOMBInputMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfTOMBInputMap == 0 );

    m_map->fillMap(l_runId);

    l_sizeOfTOMBInputMap = m_map->sizeOfMap();

    std::string l_run_id = boost::lexical_cast<std::string>(l_runId);
    std::string l_sqlQuerry = "SELECT * FROM tombinputIdBasedOnTRBIdAndTRBoutputIdFunction(" + l_run_id + ");";
    pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);

    size_t l_sizeResultQuerry = l_runDbResults.size();

  #if SHOW_DEBUG
      size_t l_sizeOfRunTable = getSizeOfRunTable();
      std::cout << "l_sizeOfRunTable = " << l_sizeOfRunTable << " l_sizeResultQuerry = " << l_sizeResultQuerry << " l_sizeOfTOMBInputMap = " << l_sizeOfTOMBInputMap << std::endl;
      m_map->showMap();
  #endif
      BOOST_REQUIRE( l_sizeResultQuerry == l_sizeOfTOMBInputMap );
  }
}

BOOST_FIXTURE_TEST_CASE(TOMBInputMapTestSuiteForTRBidAndTRBOutputTest, TOMBInputMapTestSuite)
{
#if SHOW_DEBUG
  std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
#endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    std::string l_run_id = boost::lexical_cast<std::string>(l_runId);
    std::string l_sqlQuerry = "SELECT * FROM tombinputIdBasedOnTRBIdAndTRBoutputIdFunction(" + l_run_id + ");";
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
        DATA::TOMB_INPUT_MAP_KEY_TYPE l_trb_id_trboutput_id = std::make_pair(row["trb_id"].as<int>(), row["trboutput_id"].as<int>());
        DATA::TOMB_INPUT_MAP_VALUE_TYPE l_tombinput_id = row["tombinput_id"].as<DATA::TOMB_INPUT_MAP_VALUE_TYPE >();

        DATA::TOMB_INPUT_MAP_VALUE_TYPE l_tombinputIdFromTOMBInputMap = *m_map->valueFromMap(l_trb_id_trboutput_id);

      #if SHOW_DEBUG
        std::cout << "l_trb_id_trboutput_id.first = " << l_trb_id_trboutput_id.first << " l_trb_id_trboutput_id.second = " << l_trb_id_trboutput_id.second << " l_tombinput_id = " << l_tombinput_id << std::endl;
        std::cout << "l_tombinputIdFromTOMBInputMap = " << l_tombinputIdFromTOMBInputMap << std::endl;
      #endif
        BOOST_CHECK(l_tombinputIdFromTOMBInputMap == l_tombinput_id);
      }
    }
  }
}

BOOST_FIXTURE_TEST_CASE(saveToFileAndRemoveFileWithTOMBInputMapTest, TOMBInputMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfTOMBInputMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfTOMBInputMap == 0 );

    m_map->fillMap(l_runId);
    std::string l_fileNameToSaveTOMBInputMap = "TOMBInputMap.txt";
    m_map->saveMapToFile(l_fileNameToSaveTOMBInputMap);

    bool l_removeFileWithTOMBInputMapSuccessfuly = m_map->removeFileWithMap();
    BOOST_CHECK(l_removeFileWithTOMBInputMapSuccessfuly == false);
  }
}

BOOST_FIXTURE_TEST_CASE(clearTOMBInputMapTest, TOMBInputMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfTOMBInputMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfTOMBInputMap == 0 );

    m_map->fillMap(l_runId);

    l_sizeOfTOMBInputMap = m_map->sizeOfMap();

    if(l_sizeOfTOMBInputMap > 0)
    {
  #if SHOW_DEBUG
      std::cout << "l_sizeOfTOMBInputMap = " << l_sizeOfTOMBInputMap << std::endl;
  #endif
      m_map->clearMap();
      BOOST_REQUIRE( m_map->sizeOfMap() == 0 );
    }
  }
}

BOOST_FIXTURE_TEST_CASE(checkIfExistFirstElementAndEraseElementFromTOMBInputMapTest, TOMBInputMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfTOMBInputMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfTOMBInputMap == 0 );

    m_map->fillMap(l_runId);

    if(m_map->firstElement() != boost::none)
    {
      l_sizeOfTOMBInputMap = m_map->sizeOfMap();
      std::pair<DATA::TOMB_INPUT_MAP_KEY_TYPE, DATA::TOMB_INPUT_MAP_VALUE_TYPE > l_firstElementFromTOMBInputMap = *m_map->firstElement();
      DATA::TOMB_INPUT_MAP_KEY_TYPE l_firstKeyFromTOMBInputMap = l_firstElementFromTOMBInputMap.first;

  #if SHOW_DEBUG
      m_map->showMap();
      std::cout << "l_firstKeyFromTOMBInputMap.first = " << l_firstKeyFromTOMBInputMap.first << " l_firstKeyFromTOMBInputMap.second = " << l_firstKeyFromTOMBInputMap.second << std::endl;
  #endif
      m_map->eraseElementFromMap(l_firstKeyFromTOMBInputMap);
      BOOST_CHECK( m_map->sizeOfMap() == (l_sizeOfTOMBInputMap - 1) );
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace TEST

} // namespace DB

#endif // TOMB_INPUT_MAP_TESTSUITE_H
