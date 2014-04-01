// PhotoMultiplier Map Test Suite - PhotoMultiplierMapTestSuite.cpp
#ifndef PHOTOMULTIPLIER_MAP_TESTSUITE_H
#define PHOTOMULTIPLIER_MAP_TESTSUITE_H

#define SHOW_DEBUG 0

#define BOOST_TEST_MODULE PhotoMultiplierMapTestSuite
#include <boost/test/included/unit_test.hpp>
#include "../HeaderFiles/PhotoMultiplierMap.h"
#include "SerializableMapBT.hpp"


namespace DB
{

namespace TEST
{

class PhotoMultiplierMapTestSuite : public SerializableMapBT<DATA::PhotoMultiplierMap >
{
public:
  PhotoMultiplierMapTestSuite(void);
  virtual ~PhotoMultiplierMapTestSuite(void);
};


PhotoMultiplierMapTestSuite::PhotoMultiplierMapTestSuite() : SerializableMapBT<DATA::PhotoMultiplierMap >()
{
}

PhotoMultiplierMapTestSuite::~PhotoMultiplierMapTestSuite()
{
}


// Tests
BOOST_AUTO_TEST_SUITE(PhotoMultiplierMapTS)

BOOST_FIXTURE_TEST_CASE(fillPhotoMultiplierMapCheckSizeTest, PhotoMultiplierMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  size_t l_sizeOfRunTable = getSizeOfRunTable();
  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfPhotoMultiplierMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfPhotoMultiplierMap == 0 );

    m_map->fillMap(l_runId);

    l_sizeOfPhotoMultiplierMap = m_map->sizeOfMap();

  #if SHOW_DEBUG
      std::cout << "l_sizeOfRunTable = " << l_sizeOfRunTable << " l_sizeOfPhotoMultiplierMap = " << l_sizeOfPhotoMultiplierMap << std::endl;
      m_map->showMap();
  #endif
      BOOST_REQUIRE( l_sizeOfRunTable == (l_sizeOfPhotoMultiplierMap/2) );
  }
}

BOOST_FIXTURE_TEST_CASE(pairOfPhotoMultiplierForSlotIdTest, PhotoMultiplierMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  std::string l_sqlQuerry = "select * from \"HVPMConnection\" ORDER BY slot_id";
  pqxx::result l_sqlResults = m_dbHandlerInstance.querry(l_sqlQuerry);
  #if SHOW_DEBUG
    std::cout << "l_sqlResults.size() = " << l_sqlResults.size() << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfPhotoMultiplierMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfPhotoMultiplierMap == 0 );

    m_map->fillMap(l_runId);

    l_sizeOfPhotoMultiplierMap = m_map->sizeOfMap();
    BOOST_CHECK( l_sizeOfPhotoMultiplierMap == (l_sqlResults.size()/2) );

    int l_loopCounter = 1;
    int l_photoMultiplierIdLeft = -1;

    for(pqxx::result::const_iterator row = l_sqlResults.begin(); row != l_sqlResults.end(); ++row)
    {
      if( ((l_loopCounter % 2) == 0) && (l_loopCounter > 0) )
      {
        int l_slotId = row["slot_id"].as<int>();
        int l_photoMultiplierIdRight = row["photomultiplier_id"].as<int>();

        boost::optional<std::pair<int, int> > l_pairOfPhotoMultiplierBoostOptionalForSlotId = m_map->valueFromMap(l_slotId);

        BOOST_REQUIRE( l_pairOfPhotoMultiplierBoostOptionalForSlotId != 0 );

        if(l_pairOfPhotoMultiplierBoostOptionalForSlotId)
        {
          std::pair<int, int> l_pairOfPhotoMultiplierForSlotId = l_pairOfPhotoMultiplierBoostOptionalForSlotId.get();
          BOOST_CHECK(l_photoMultiplierIdLeft == l_pairOfPhotoMultiplierForSlotId.first);
          BOOST_CHECK(l_photoMultiplierIdRight == l_pairOfPhotoMultiplierForSlotId.second);
  #if SHOW_DEBUG
          std::cout << "l_pairOfPhotoMultiplierForSlotId.first = " << l_pairOfPhotoMultiplierForSlotId.first << " l_pairOfPhotoMultiplierForSlotId.second = " << l_pairOfPhotoMultiplierForSlotId.second << std::endl;
          std::cout << "l_photoMultiplierIdLeft = " << l_photoMultiplierIdLeft << " l_photoMultiplierIdRight = " << l_photoMultiplierIdRight << std::endl;
  #endif
        }

        l_loopCounter = 1;
        continue;
      }

      l_photoMultiplierIdLeft = row["photomultiplier_id"].as<int>();
      ++l_loopCounter;
    }
  }
}

BOOST_FIXTURE_TEST_CASE(saveToFileAndRemoveFileWithPhotoMultiplierMapTest, PhotoMultiplierMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfPhotoMultiplierMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfPhotoMultiplierMap == 0 );

    m_map->fillMap(l_runId);
    std::string l_fileNameToSavePhotoMultiplierMap = "PhotoMultiplierMap.txt";
    m_map->saveMapToFile(l_fileNameToSavePhotoMultiplierMap);

    bool l_removeFileWithPhotoMultiplierMapSuccessfuly = m_map->removeFileWithMap();
    BOOST_CHECK(l_removeFileWithPhotoMultiplierMapSuccessfuly == false);
  }
}

BOOST_FIXTURE_TEST_CASE(clearPhotoMultiplierMapTest, PhotoMultiplierMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfPhotoMultiplierMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfPhotoMultiplierMap == 0 );

    m_map->fillMap(l_runId);

    l_sizeOfPhotoMultiplierMap = m_map->sizeOfMap();

    if(l_sizeOfPhotoMultiplierMap > 0)
    {
  #if SHOW_DEBUG
      std::cout << "l_sizeOfPhotoMultiplierMap = " << l_sizeOfPhotoMultiplierMap << std::endl;
  #endif
      m_map->clearMap();
      BOOST_REQUIRE( m_map->sizeOfMap() == 0 );
    }
  }
}

BOOST_FIXTURE_TEST_CASE(checkIfExistFirstElementAndEraseElementFromPhotoMultiplierMapTest, PhotoMultiplierMapTestSuite)
{
  #if SHOW_DEBUG
    std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
  #endif

  int l_runId = getFirstRunIdIfExist();

  if(l_runId != -1)
  {
    size_t l_sizeOfPhotoMultiplierMap = m_map->sizeOfMap();
    BOOST_REQUIRE( l_sizeOfPhotoMultiplierMap == 0 );

    m_map->fillMap(l_runId);

    if(m_map->firstElement() != boost::none)
    {
      l_sizeOfPhotoMultiplierMap = m_map->sizeOfMap();
      std::pair<DATA::PHOTOMULTIPLIER_MAP_KEY_TYPE, DATA::PHOTOMULTIPLIER_MAP_VALUE_TYPE > l_firstElementFromPhotoMultiplierMap = *m_map->firstElement();
      DATA::PHOTOMULTIPLIER_MAP_KEY_TYPE l_firstKeyFromPhotoMultiplierMap = l_firstElementFromPhotoMultiplierMap.first;

  #if SHOW_DEBUG
      m_map->showMap();
      std::cout << "l_firstKeyFromPhotoMultiplierMap = " << l_firstKeyFromPhotoMultiplierMap << std::endl;
  #endif
      m_map->eraseElementFromMap(l_firstKeyFromPhotoMultiplierMap);
      BOOST_CHECK( m_map->sizeOfMap() == (l_sizeOfPhotoMultiplierMap - 1) );
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace TEST

} // namespace DB

#endif // PHOTOMULTIPLIER_MAP_TESTSUITE_H
