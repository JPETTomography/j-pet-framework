// PhotoMultiplier Id Map Test Suite - PhotoMultiplierIdMapTestSuite.cpp
#ifndef PHOTOMULTIPLIER_ID_MAP_TESTSUITE_H
#define PHOTOMULTIPLIER_ID_MAP_TESTSUITE_H

#define SHOW_DEBUG 0

#define BOOST_TEST_MODULE PhotoMultiplierIdMapTestSuite
#include <boost/test/included/unit_test.hpp>
#include "../HeaderFiles/PhotoMultiplierIdMap.h"
#include "SerializableMapBT.hpp"


namespace DB
{

namespace TEST
{

class PhotoMultiplierIdMapTestSuite : public SerializableMapBT<DATA::PhotoMultiplierIdMap >
{
public:
  PhotoMultiplierIdMapTestSuite(void);
  virtual ~PhotoMultiplierIdMapTestSuite(void);
};


PhotoMultiplierIdMapTestSuite::PhotoMultiplierIdMapTestSuite() : SerializableMapBT<DATA::PhotoMultiplierIdMap >()
{
}

PhotoMultiplierIdMapTestSuite::~PhotoMultiplierIdMapTestSuite()
{
}


// Tests
BOOST_AUTO_TEST_SUITE(PhotoMultiplierIdMapTS)

BOOST_FIXTURE_TEST_CASE(fillPhotoMultiplierIdMapCheckSizeTest, PhotoMultiplierIdMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfPhotoMultiplierIdMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfPhotoMultiplierIdMap == 0 );

    m_map->fillMap(l_runId);

    l_sizeOfPhotoMultiplierIdMap = m_map->sizeOfMap();

    std::string l_run_id = boost::lexical_cast<std::string>(l_runId);
    std::string l_sqlQuerry = "SELECT * FROM photomultiplierIdBasedOnTOMBInputIdFunction(" + l_run_id + ");";
    pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);

    size_t l_sizeResultQuerry = l_runDbResults.size();

  #if SHOW_DEBUG
      size_t l_sizeOfRunTable = getSizeOfRunTable();
      std::cout << "l_sizeOfRunTable = " << l_sizeOfRunTable << " l_sizeResultQuerry = " << l_sizeResultQuerry << " l_sizeOfPhotoMultiplierIdMap = " << l_sizeOfPhotoMultiplierIdMap << std::endl;
      m_map->showMap();
  #endif
      BOOST_REQUIRE( l_sizeResultQuerry == l_sizeOfPhotoMultiplierIdMap );
  }
}

BOOST_FIXTURE_TEST_CASE(photoMultiplierIdForTOMBInputIdTest, PhotoMultiplierIdMapTestSuite)
{
#if SHOW_DEBUG
  std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
#endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    std::string l_run_id = boost::lexical_cast<std::string>(l_runId);
    std::string l_sqlQuerry = "SELECT * FROM photomultiplierIdBasedOnTOMBInputIdFunction(" + l_run_id + ");";
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
        DATA::PHOTOMULTIPLIER_ID_MAP_KEY_TYPE l_tombinput_id = row["tombinput_id"].as<DATA::PHOTOMULTIPLIER_ID_MAP_KEY_TYPE >();
        DATA::PHOTOMULTIPLIER_ID_MAP_VALUE_TYPE l_photomultiplier_id = row["photomultiplier_id"].as<DATA::PHOTOMULTIPLIER_ID_MAP_VALUE_TYPE >();

        DATA::PHOTOMULTIPLIER_ID_MAP_VALUE_TYPE l_photomultiplierIdFromTRBThresholdMap = *m_map->valueFromMap(l_tombinput_id);

      #if SHOW_DEBUG
        std::cout << "l_tombinput_id = " << l_tombinput_id << " l_photomultiplier_id = " << l_photomultiplier_id << std::endl;
        std::cout << "l_photomultiplierIdFromTRBThresholdMap = " << l_photomultiplierIdFromTRBThresholdMap << std::endl;
      #endif
        BOOST_CHECK(l_photomultiplierIdFromTRBThresholdMap == l_photomultiplier_id);
      }
    }
  }
}

BOOST_FIXTURE_TEST_CASE(saveToFileAndRemoveFileWithPhotoMultiplierIdMapTest, PhotoMultiplierIdMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfPhotoMultiplierIdMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfPhotoMultiplierIdMap == 0 );

    m_map->fillMap(l_runId);
    std::string l_fileNameToSavePhotoMultiplierIdMap = "PhotoMultiplierIdMap.txt";
    m_map->saveMapToFile(l_fileNameToSavePhotoMultiplierIdMap);

    bool l_removeFileWithPhotoMultiplierIdMapSuccessfuly = m_map->removeFileWithMap();
    BOOST_CHECK(l_removeFileWithPhotoMultiplierIdMapSuccessfuly == false);
  }
}

BOOST_FIXTURE_TEST_CASE(clearPhotoMultiplierIdMapTest, PhotoMultiplierIdMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfPhotoMultiplierIdMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfPhotoMultiplierIdMap == 0 );

    m_map->fillMap(l_runId);

    l_sizeOfPhotoMultiplierIdMap = m_map->sizeOfMap();

    if(l_sizeOfPhotoMultiplierIdMap > 0)
    {
  #if SHOW_DEBUG
      std::cout << "l_sizeOfPhotoMultiplierIdMap = " << l_sizeOfPhotoMultiplierIdMap << std::endl;
  #endif
      m_map->clearMap();
      BOOST_REQUIRE( m_map->sizeOfMap() == 0 );
    }
  }
}

BOOST_FIXTURE_TEST_CASE(checkIfExistFirstElementAndEraseElementFromPhotoMultiplierIdMapTest, PhotoMultiplierIdMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfPhotoMultiplierIdMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfPhotoMultiplierIdMap == 0 );

    m_map->fillMap(l_runId);

    if(m_map->firstElement() != boost::none)
    {
      l_sizeOfPhotoMultiplierIdMap = m_map->sizeOfMap();
      std::pair<DATA::PHOTOMULTIPLIER_ID_MAP_KEY_TYPE, DATA::PHOTOMULTIPLIER_ID_MAP_VALUE_TYPE > l_firstElementFromPhotoMultiplierIdMap = *m_map->firstElement();
      int l_firstKeyFromPhotoMultiplierIdMap = l_firstElementFromPhotoMultiplierIdMap.first;

  #if SHOW_DEBUG
      m_map->showMap();
      std::cout << "l_firstKeyFromPhotoMultiplierIdMap = " << l_firstKeyFromPhotoMultiplierIdMap << std::endl;
  #endif
      m_map->eraseElementFromMap(l_firstKeyFromPhotoMultiplierIdMap);
      BOOST_CHECK( m_map->sizeOfMap() == (l_sizeOfPhotoMultiplierIdMap - 1) );
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace TEST

} // namespace DB

#endif // PHOTOMULTIPLIER_ID_MAP_TESTSUITE_H
