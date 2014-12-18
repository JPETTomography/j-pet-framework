#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetReaderTest
#include <boost/test/unit_test.hpp>

#define private public
#define protected public

#include <cstddef>
#include <iostream>
#include <vector>

#include "../../JPetScopeReader/JPetScopeReader.h"
#include "../../JPetSignal/JPetSignal.h"
#include "../../JPetSigCh/JPetSigCh.h"

BOOST_AUTO_TEST_SUITE (FirstSuite)


BOOST_AUTO_TEST_CASE (default_constructor)
{
  JPetScopeReader reader;

  BOOST_REQUIRE(reader.isFileOpen() == false);

//  BOOST_REQUIRE_EQUAL(reader.fSegments, 0);
  BOOST_REQUIRE_EQUAL(reader.fSegmentSize, 0);
}

BOOST_AUTO_TEST_CASE (open_file)
{
  JPetScopeReader reader;
  reader.openFile("C1_00000.txt");

  BOOST_REQUIRE(reader.isFileOpen());

//  BOOST_REQUIRE_EQUAL(reader.fSegments, 0);
  BOOST_REQUIRE_EQUAL(reader.fSegmentSize, 0);

  reader.readHeader();

//  BOOST_CHECK_EQUAL(reader.fSegments, 1);
  BOOST_CHECK_EQUAL(reader.fSegmentSize, 502);

  JPetSignal* sig = reader.readData();
  int points  = sig->getNumberOfLeadingEdgePoints();
      points += sig->getNumberOfTrailingEdgePoints();

  BOOST_CHECK_EQUAL(points, 502);

  reader.closeFile();

  BOOST_REQUIRE(reader.isFileOpen() == false);

}

BOOST_AUTO_TEST_SUITE_END()
