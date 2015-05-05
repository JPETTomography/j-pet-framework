#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ScopeReader
#define BOOST_TEST_LOG_LEVEL message

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "JPetScopeReaderFixtures.h"

#include <cstddef>
#include <functional>

#include "../../JPetManager/JPetManager.h"

BOOST_AUTO_TEST_SUITE (FirstSuite)

BOOST_AUTO_TEST_CASE (generate_root_file) {

  int   _argc    = 5;
  char* _argv[6];
        _argv[0] = const_cast<char*>("JPetScopeReaderTest.exe");
        _argv[1] = const_cast<char*>("-t");
        _argv[2] = const_cast<char*>("scope");
        _argv[3] = const_cast<char*>("-f");
        _argv[4] = const_cast<char*>("./test_file.info");
	_argv[5] = (char*)(NULL);

  JPetManager& manager = JPetManager::GetManager();
  manager.ParseCmdLine(_argc, _argv);
  manager.Run();

  BOOST_REQUIRE_MESSAGE(boost::filesystem::exists(test_root_filename), "File " << test_root_filename << " does not exitst.");
}

BOOST_FIXTURE_TEST_CASE (signal_generation_test, signal_generation_fixture) {

  check_header(
    [] (int osc_file_size, int reco_signal_size) -> void {
      BOOST_REQUIRE_EQUAL(osc_file_size, reco_signal_size);
    }
  );

  check_data(
    [] (float osc_file_time, float reco_signal_time, float osc_file_ampl, float reco_signal_ampl) -> void {
      BOOST_CHECK_CLOSE_FRACTION(osc_file_time, reco_signal_time, 1.f / 131072.f);
      BOOST_CHECK_CLOSE_FRACTION(osc_file_ampl, reco_signal_ampl, 1.f / 131072.f);
    }
  );
}

BOOST_FIXTURE_TEST_CASE (tref_correctness_test, tref_correctness_fixture) {
  
  check_tref_simple(
    [] (const void* tref_pointer) -> void {
      BOOST_CHECK_PREDICATE(std::not_equal_to <size_t> (), ((size_t) tref_pointer)((size_t) nullptr));
    }
  );
  //check_tref_simple(nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
