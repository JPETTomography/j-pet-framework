#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ScopeReader
#define BOOST_TEST_LOG_LEVEL message

#include <boost/test/unit_test.hpp>

#include "JPetScopeReaderFixtures.h"

#include <cstddef>

BOOST_AUTO_TEST_SUITE (FirstSuite)

BOOST_FIXTURE_TEST_CASE (signal_generation_test, signal_generate_fixture) {

  check_header(
    [](int osc_file_size, int reco_signal_size)->void {
      BOOST_CHECK_EQUAL(osc_file_size, reco_signal_size);
    }
  );

  check_data(
    [](float osc_file_time, float reco_signal_time, float osc_file_ampl, float reco_signal_ampl)->void {
      BOOST_CHECK_CLOSE(osc_file_time, reco_signal_time, osc_file_time / 131072.f);
      BOOST_CHECK_CLOSE(osc_file_ampl, reco_signal_ampl, osc_file_ampl / 131072.f);
    }
  );
}

BOOST_AUTO_TEST_SUITE_END()
