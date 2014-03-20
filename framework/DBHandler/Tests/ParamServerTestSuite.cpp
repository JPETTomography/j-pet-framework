// Param Server Test Suite - ParamServer.h (Parameter Server)
#ifndef PARAMSERVER_TESTSUITE_H
#define PARAMSERVER_TESTSUITE_H

#define BOOST_TEST_MODULE ParamServerTestSuite

#define SHOW_DEBUG 0

#include <boost/test/included/unit_test.hpp>
#include "../HeaderFiles/ParamServer.h"
#include "DBHandlerHelper.cpp"
#include "ParamServerHelper.cpp"


namespace DB
{

namespace TEST
{

class ParamServerTestSuite
{
protected:
  ParamServerHelper *m_paramServerHelper;
  SERVICES::DBHandler &m_dbHandlerInstance;

public:
  ParamServerTestSuite(void);
  ~ParamServerTestSuite(void);

protected:
  inline bool ifFileExists(std::string p_fileName)
  {
    std::ifstream l_file(p_fileName.c_str());
    return l_file;
  }
};


ParamServerTestSuite::ParamServerTestSuite() :
                                              m_paramServerHelper(new ParamServerHelper(DBHandlerHelper::getInstanceForTestsDemand())), // UWAGA
                                              m_dbHandlerInstance(DBHandlerHelper::getInstanceForTestsDemand()) // UWAGA
{
}

ParamServerTestSuite::~ParamServerTestSuite()
{
  delete m_paramServerHelper;
  DB::SERVICES::DBHandler::deleteInstance();  // do przemyslenia!
}

// Tests
BOOST_AUTO_TEST_SUITE(ParamServerTS)

BOOST_FIXTURE_TEST_CASE(fillPhotoMultiplierMapCheckSizeTest, ParamServerTestSuite)
{
  std::string l_sqlQuerry = "SELECT * FROM \"Run\"";
  size_t l_sizeForRunResults = m_dbHandlerInstance.sizeForQuerry(l_sqlQuerry);

  m_paramServerHelper->fillPhotoMultiplierMap();

  size_t l_sizeOfPhotoMultiplierMap = m_paramServerHelper->sizeOfPhotoMultiplierMap();
#if SHOW_DEBUG
  std::cout << "l_sizeForRunResults = " << l_sizeForRunResults << " l_sizeOfPhotoMultiplierMap = " << l_sizeOfPhotoMultiplierMap << std::endl;
  m_paramServerHelper->showPhotoMultiplierMap();
#endif
  BOOST_REQUIRE( l_sizeForRunResults == (l_sizeOfPhotoMultiplierMap/2) );
}

BOOST_FIXTURE_TEST_CASE(fillRunDataMapCheckSizeTest, ParamServerTestSuite)
{
  std::string l_sqlQuerry = "SELECT * FROM \"Run\"";
  size_t l_sizeForRunResults = m_dbHandlerInstance.sizeForQuerry(l_sqlQuerry);

  m_paramServerHelper->fillRunDataMap();

  size_t l_sizeOfRunDataMap = m_paramServerHelper->sizeOfRunDataMap();
#if SHOW_DEBUG
  std::cout << "l_sizeForRunResults = " << l_sizeForRunResults << " l_sizeOfRunDataMap = " << l_sizeOfRunDataMap << std::endl;
  m_paramServerHelper->showRunDataMap();
#endif
  BOOST_REQUIRE( l_sizeForRunResults == l_sizeOfRunDataMap );
}

BOOST_FIXTURE_TEST_CASE(pairOfPhotoMultiplierForSlotIdTest, ParamServerTestSuite)
{
  std::string l_sqlQuerry = "select * from \"HVPMConnection\" ORDER BY slot_id";
  pqxx::result l_sqlResults = m_dbHandlerInstance.querry(l_sqlQuerry);
  //std::cout << "l_sqlResults.size() = " << l_sqlResults.size() << std::endl;

  m_paramServerHelper->fillPhotoMultiplierMap();
  size_t l_sizeOfPhotoMultiplierMap = m_paramServerHelper->sizeOfPhotoMultiplierMap();
  BOOST_CHECK( l_sizeOfPhotoMultiplierMap == (l_sqlResults.size()/2) );

  int l_loopCounter = 1;
  int l_photoMultiplierIdLeft = -1;

  for(pqxx::result::const_iterator row = l_sqlResults.begin(); row != l_sqlResults.end(); ++row)
  {
    if( ((l_loopCounter % 2) == 0) && (l_loopCounter > 0) )
    {
      int l_slotId = row["slot_id"].as<int>();
      int l_photoMultiplierIdRight = row["photomultiplier_id"].as<int>();

      boost::optional<std::pair<int, int> > l_pairOfPhotoMultiplierBoostOptionalForSlotId = m_paramServerHelper->pairOfPhotoMultiplierForSlotId(l_slotId);

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

BOOST_FIXTURE_TEST_CASE(compareDataFromRunDataMapWithDataFromDBTest, ParamServerTestSuite)
{
  std::string l_sqlQuerry = "SELECT * FROM runDataFunction();";
  pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);

  size_t l_sizeOfRunDbResultsFromQuerry = l_runDbResults.size();

  m_paramServerHelper->fillRunDataMap();
  size_t l_sizeOfRunDataMap = m_paramServerHelper->sizeOfRunDataMap();

  BOOST_REQUIRE( l_sizeOfRunDbResultsFromQuerry == l_sizeOfRunDataMap );

  if(l_sizeOfRunDbResultsFromQuerry)
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row)
    {
      int l_runId = row["run_id"].as<int>();
      std::string l_runStartFromDB = row["runstart"].as<std::string>();
      std::string l_filePathFromDB = row["filepath"].as<std::string>();
      std::string l_runDescriptionFromDB = row["rundescription"].as<std::string>();
      std::string l_informationFromDB = row["information"].as<std::string>();

      std::map<int, DATA::RunData>::iterator l_runDataMapIterator = m_paramServerHelper->m_runDataMap.find(l_runId);

      BOOST_REQUIRE( l_runDataMapIterator != m_paramServerHelper->m_runDataMap.end() );

      DATA::RunData l_runData = l_runDataMapIterator->second;

      std::string l_runStartFromMap = l_runData.runStart();
      std::string l_filePathFromMap = l_runData.filePath();
      std::string l_runDescriptionFromMap = l_runData.runDescription();
      std::string l_informationFromMap = l_runData.information();

      BOOST_CHECK( l_runStartFromDB == l_runStartFromMap );
      BOOST_CHECK( l_filePathFromMap == l_filePathFromDB );
      BOOST_CHECK( l_runDescriptionFromMap == l_runDescriptionFromDB );
      BOOST_CHECK( l_informationFromMap == l_informationFromDB );
    }
  }
}

BOOST_FIXTURE_TEST_CASE(savePhotoMultiplierMapToFileTest, ParamServerTestSuite)
{
  m_paramServerHelper->fillPhotoMultiplierMap();
  std::string l_fileNameToSavePhotoMultiplierMap = "PhotoMultiplierMap.txt";
  m_paramServerHelper->savePhotoMultiplierMapToFile(l_fileNameToSavePhotoMultiplierMap);

  bool l_ifFileWithMapsExists = ifFileExists(l_fileNameToSavePhotoMultiplierMap);
  BOOST_CHECK(l_ifFileWithMapsExists == true);

  BOOST_CHECK(remove(l_fileNameToSavePhotoMultiplierMap.c_str()) == 0);
}

BOOST_FIXTURE_TEST_CASE(clearPhotoMultiplierMapTest, ParamServerTestSuite)
{
  //std::cout << m_paramServerHelper->sizeOfPhotoMultiplierMap() << std::endl;
  BOOST_CHECK(m_paramServerHelper->sizeOfPhotoMultiplierMap() == 0);
  m_paramServerHelper->fillPhotoMultiplierMap();

  size_t l_sizeOfPhotoMultiplierMap = m_paramServerHelper->sizeOfPhotoMultiplierMap();
  if(l_sizeOfPhotoMultiplierMap > 0)
  {
    //std::cout << m_paramServerHelper->sizeOfPhotoMultiplierMap() << std::endl;
    m_paramServerHelper->clearPhotoMultiplierMap();
    BOOST_CHECK(m_paramServerHelper->sizeOfPhotoMultiplierMap() == 0);
  }
}

BOOST_FIXTURE_TEST_CASE(clearRunDataMapTest, ParamServerTestSuite)
{
  //std::cout << m_paramServerHelper->sizeOfRunDataMap() << std::endl;
  BOOST_CHECK(m_paramServerHelper->sizeOfRunDataMap() == 0);
  m_paramServerHelper->fillRunDataMap();

  size_t l_sizeOfRunDataMap = m_paramServerHelper->sizeOfRunDataMap();
  if(l_sizeOfRunDataMap > 0)
  {
    //std::cout << m_paramServerHelper->sizeOfRunDataMap() << std::endl;
    m_paramServerHelper->clearRunDataMap();
    BOOST_CHECK(m_paramServerHelper->sizeOfRunDataMap() == 0);
  }
}

BOOST_FIXTURE_TEST_CASE(eraseElementFromPhotoMultiplierMapTest, ParamServerTestSuite)
{
  m_paramServerHelper->fillPhotoMultiplierMap();
  size_t l_sizeOfPhotoMultiplierMap = m_paramServerHelper->sizeOfPhotoMultiplierMap();

  if(l_sizeOfPhotoMultiplierMap > 0)
  {
    int l_firstKeyFromPhotoMultiplierMap = m_paramServerHelper->m_photoMultiplierMap.begin()->first;
#if SHOW_DEBUG
    m_paramServerHelper->showPhotoMultiplierMap();
    std::cout << "l_firstKeyFromPhotoMultiplierMap = " << l_firstKeyFromPhotoMultiplierMap << std::endl;
#endif
    m_paramServerHelper->eraseElementFromPhotoMultiplierMap(l_firstKeyFromPhotoMultiplierMap);

    BOOST_CHECK( m_paramServerHelper->sizeOfPhotoMultiplierMap() == (l_sizeOfPhotoMultiplierMap - 1) );
  }
}

BOOST_FIXTURE_TEST_CASE(eraseElementFromRunDataMapTest, ParamServerTestSuite)
{
  m_paramServerHelper->fillRunDataMap();
  size_t l_sizeOfRunDataMap = m_paramServerHelper->sizeOfRunDataMap();

  if(l_sizeOfRunDataMap > 0)
  {
    int l_firstKeyFromRunDataMap = m_paramServerHelper->m_runDataMap.begin()->first;
#if SHOW_DEBUG
    m_paramServerHelper->showRunDataMap();
    std::cout << "l_firstKeyFromRunDataMap = " << l_firstKeyFromRunDataMap << std::endl;
#endif
    m_paramServerHelper->eraseElementFromRunDataMap(l_firstKeyFromRunDataMap);

    BOOST_CHECK( m_paramServerHelper->sizeOfRunDataMap() == (l_sizeOfRunDataMap - 1) );
  }
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace TEST

} // namespace DB

#endif // PARAMSERVER_TESTSUITE_H
