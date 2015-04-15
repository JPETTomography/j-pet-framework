#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ScopeReader
#define BOOST_TEST_LOG_LEVEL message

#include <boost/test/unit_test.hpp>

#include "JPetScopeReaderFixtures.h"

#include <cstddef>

BOOST_AUTO_TEST_SUITE (FirstSuite)

BOOST_FIXTURE_TEST_CASE (signal_generation_test, signal_generate_fixture) {
  check_header();
  check_data();
}

BOOST_AUTO_TEST_SUITE_END()
