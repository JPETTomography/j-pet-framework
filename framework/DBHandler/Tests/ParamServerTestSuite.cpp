// Param Server Test Suite - ParamServer.h (Parameter Server)
#ifndef PARAMSERVER_TESTSUITE_H
#define PARAMSERVER_TESTSUITE_H

#define BOOST_TEST_MODULE ParamServerTestSuite
#include <boost/test/included/unit_test.hpp>
#include "../HeaderFiles/ParamServer.h"
#include "DBHandlerHelper.cpp"


namespace DB
{

namespace TEST
{

class ParamServerTestSuite
{
protected:
  SERVER::ParamServer *m_paramServer;
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
                                              m_paramServer(new DB::SERVER::ParamServer(DBHandlerHelper::getInstanceForTestsDemand())), // UWAGA
                                              m_dbHandlerInstance(DBHandlerHelper::getInstanceForTestsDemand()) // UWAGA
{
}

ParamServerTestSuite::~ParamServerTestSuite()
{
  delete m_paramServer;
  DB::SERVICES::DBHandler::deleteInstance();  // do przemyslenia!
}

// Tests
BOOST_AUTO_TEST_SUITE(ParamServerTS)

BOOST_FIXTURE_TEST_CASE(fillPhotoMultiplierMapCheckSizeTest, ParamServerTestSuite)
{
  std::string l_sqlQuerry = "SELECT * FROM \"Run\"";
  size_t l_sizeForRunResults = m_dbHandlerInstance.sizeForQuerry(l_sqlQuerry);

  m_paramServer->fillPhotoMultiplierMap();

  size_t l_sizeOfPhotoMultiplierMap = m_paramServer->sizeOfPhotoMultiplierMap();
  //std::cout << "l_sizeForRunResults = " << l_sizeForRunResults << " l_sizeOfPhotoMultiplierMap = " << l_sizeOfPhotoMultiplierMap << std::endl;
  BOOST_REQUIRE( l_sizeForRunResults == (l_sizeOfPhotoMultiplierMap/2) );
}

BOOST_FIXTURE_TEST_CASE(pairOfPhotoMultiplierForSlotIdTest, ParamServerTestSuite)
{
  std::string l_sqlQuerry = "select * from \"HVPMConnection\" ORDER BY slot_id";
  pqxx::result l_sqlResults = m_dbHandlerInstance.querry(l_sqlQuerry);
  //std::cout << "l_sqlResults.size() = " << l_sqlResults.size() << std::endl;

  m_paramServer->fillPhotoMultiplierMap();
  size_t l_sizeOfPhotoMultiplierMap = m_paramServer->sizeOfPhotoMultiplierMap();
  BOOST_CHECK( l_sizeOfPhotoMultiplierMap == (l_sqlResults.size()/2) );

  int l_loopCounter = 1;
  int l_photoMultiplierIdLeft = -1;

  for(pqxx::result::const_iterator row = l_sqlResults.begin(); row != l_sqlResults.end(); ++row)
  {
    if( ((l_loopCounter % 2) == 0) && (l_loopCounter > 0) )
    {
      int l_slotId = row["slot_id"].as<int>();
      int l_photoMultiplierIdRight = row["photomultiplier_id"].as<int>();

      boost::optional<std::pair<int, int> > l_pairOfPhotoMultiplierBoostOptionalForSlotId = m_paramServer->pairOfPhotoMultiplierForSlotId(l_slotId);

      BOOST_REQUIRE( l_pairOfPhotoMultiplierBoostOptionalForSlotId != 0 );

      if(l_pairOfPhotoMultiplierBoostOptionalForSlotId)
      {
        std::pair<int, int> l_pairOfPhotoMultiplierForSlotId = l_pairOfPhotoMultiplierBoostOptionalForSlotId.get();
        BOOST_CHECK(l_photoMultiplierIdLeft == l_pairOfPhotoMultiplierForSlotId.first);
        BOOST_CHECK(l_photoMultiplierIdRight == l_pairOfPhotoMultiplierForSlotId.second);
        std::cout << "l_pairOfPhotoMultiplierForSlotId.first = " << l_pairOfPhotoMultiplierForSlotId.first << " l_pairOfPhotoMultiplierForSlotId.second = " << l_pairOfPhotoMultiplierForSlotId.second << std::endl;
        std::cout << "l_photoMultiplierIdLeft = " << l_photoMultiplierIdLeft << " l_photoMultiplierIdRight = " << l_photoMultiplierIdRight << std::endl;
      }

      l_loopCounter = 1;
      continue;
    }

    l_photoMultiplierIdLeft = row["photomultiplier_id"].as<int>();
    ++l_loopCounter;
  }
}

BOOST_FIXTURE_TEST_CASE(savePhotoMultiplierMapToFileTest, ParamServerTestSuite)
{
  m_paramServer->fillPhotoMultiplierMap();
  std::string l_fileNameToSavePhotoMultiplierMap = "PhotoMultiplierMap.txt";
  m_paramServer->savePhotoMultiplierMapToFile(l_fileNameToSavePhotoMultiplierMap);

  bool l_ifFileWithMapsExists = ifFileExists(l_fileNameToSavePhotoMultiplierMap);
  BOOST_CHECK(l_ifFileWithMapsExists == true);

  BOOST_CHECK(remove(l_fileNameToSavePhotoMultiplierMap.c_str()) == 0);
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace TEST

} // namespace DB

#endif // PARAMSERVER_TESTSUITE_H
