// Run Data Test Suite - RunData.h
#ifndef RUN_DATA_TESTSUITE_H
#define RUN_DATA_TESTSUITE_H

#define BOOST_TEST_MODULE RunDataTestSuite
#include <boost/test/included/unit_test.hpp>
#include "../HeaderFiles/RunData.h"


namespace DB
{

namespace TEST
{

class RunDataTestSuite
{
protected:
  DATA::RunData *m_runData;

public:
  RunDataTestSuite(void);
  ~RunDataTestSuite(void);
};


RunDataTestSuite::RunDataTestSuite() : m_runData(new DATA::RunData("2014-03-05 11:46:59.065596", "/home/pet", "test", "test info"))
{
}

RunDataTestSuite::~RunDataTestSuite()
{
  delete m_runData;
}

// Tests
BOOST_AUTO_TEST_SUITE(RunDataTS)

BOOST_FIXTURE_TEST_CASE(equalityOperatorTest, RunDataTestSuite)
{
  DATA::RunData l_runDataObject = *m_runData;
  BOOST_REQUIRE( *m_runData == l_runDataObject );
}

BOOST_FIXTURE_TEST_CASE(comparisonOperatorTest, RunDataTestSuite)
{
  bool l_condition = ( *m_runData == DATA::RunData("2014-03-05 11:46:59.065596", "/home/pet", "test", "test info") );
  BOOST_REQUIRE( l_condition == true );
}

BOOST_FIXTURE_TEST_CASE(negationOperatorTest, RunDataTestSuite)
{
  bool l_condition = ( *m_runData != DATA::RunData("2014-03-05 11:46:59.065596", "/home/pet", "test", "test info") );
  BOOST_REQUIRE( l_condition == false );
}

BOOST_FIXTURE_TEST_CASE(runStartTest, RunDataTestSuite)
{
  BOOST_REQUIRE( strcmp(m_runData->runStart().c_str(), "2014-03-05 11:46:59.065596") == 0 );
}

BOOST_FIXTURE_TEST_CASE(filePathTest, RunDataTestSuite)
{
  BOOST_REQUIRE( strcmp(m_runData->filePath().c_str(), "/home/pet") == 0 );
}

BOOST_FIXTURE_TEST_CASE(runDescriptionTest, RunDataTestSuite)
{
  BOOST_REQUIRE( strcmp(m_runData->runDescription().c_str(), "test") == 0 );
}

BOOST_FIXTURE_TEST_CASE(informationTest, RunDataTestSuite)
{
  BOOST_REQUIRE( strcmp(m_runData->information().c_str(), "test info") == 0 );
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace TEST

} // namespace DB

#endif // RUN_DATA_TESTSUITE_H
