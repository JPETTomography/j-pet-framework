#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ScopeReader
#define BOOST_TEST_LOG_LEVEL message
#include <cstddef>
#include <functional>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include "../JPetManager/JPetManager.h"

#include "JPetScopeReaderFixtures.h"
#include "../JPetScopeReader/JPetScopeReader.h"


BOOST_AUTO_TEST_SUITE (JPetScopeReaderTestSuite)
BOOST_AUTO_TEST_CASE (generate_root_file) {

  int   _argc    = 5;
  char* _argv[6];
        _argv[0] = const_cast<char*>("JPetScopeReaderTest.exe");
        _argv[1] = const_cast<char*>("-t");
        _argv[2] = const_cast<char*>("scope");
        _argv[3] = const_cast<char*>("-f");
        _argv[4] = const_cast<char*>("unitTestData/JPetScopeReaderTest/test_file.info");
	_argv[5] = (char*)(NULL);

  JPetManager& manager = JPetManager::getManager();
  manager.parseCmdLine(_argc, _argv);
  manager.run();
  BOOST_REQUIRE_MESSAGE(boost::filesystem::exists(gTest_root_filename), "File " << gTest_root_filename << " does not exist.");
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

BOOST_AUTO_TEST_CASE (createInputScopeFileNames) 
{
  using VecOfStrings = std::vector<std::string>;
  JPetScopeReader reader(0);
  BOOST_REQUIRE(reader.createInputScopeFileNames("").empty());
  BOOST_REQUIRE(reader.createInputScopeFileNames("non_existing").empty());
  BOOST_REQUIRE(!reader.createInputScopeFileNames("unitTestData/JPetScopeReaderTest/scope_files/0").empty());
  VecOfStrings expectedRes {
    "C1_00003.txt",  "C2_00003.txt",  "C3_00003.txt",  "C4_00003.txt",
    "C1_00004.txt",  "C2_00004.txt",  "C3_00004.txt",  "C4_00004.txt"
  };
  std::string pathToFiles = "unitTestData/JPetScopeReaderTest/scope_files/0";
  std::transform(expectedRes.begin(), expectedRes.end(),expectedRes.begin(), 
                [&](std::string name) {
                  return pathToFiles + "/"+name;
                }); 
   
  auto obtainedRes = reader.createInputScopeFileNames(pathToFiles);
  BOOST_REQUIRE(!obtainedRes.empty());
  /// to assure the same order of elements for comparison
  std::sort(obtainedRes.begin(), obtainedRes.end());
  std::sort(expectedRes.begin(), expectedRes.end());
  BOOST_REQUIRE_EQUAL_COLLECTIONS(obtainedRes.begin(), obtainedRes.end(), expectedRes.begin(), expectedRes.end());
}

BOOST_AUTO_TEST_CASE (isCorrectScopeFileName) 
{
  JPetScopeReader reader(0);
  BOOST_REQUIRE(!reader.isCorrectScopeFileName(""));
  BOOST_REQUIRE(!reader.isCorrectScopeFileName("C1_004.gif"));
  BOOST_REQUIRE(!reader.isCorrectScopeFileName("C1004.txt"));
  BOOST_REQUIRE(!reader.isCorrectScopeFileName("004.txt"));
  BOOST_REQUIRE(!reader.isCorrectScopeFileName("C5_abc.txt"));
  BOOST_REQUIRE(reader.isCorrectScopeFileName("C1_023.txt"));
  BOOST_REQUIRE(reader.isCorrectScopeFileName("C5_000.txt"));
  BOOST_REQUIRE(reader.isCorrectScopeFileName("AA_004.txt"));
  BOOST_REQUIRE(reader.isCorrectScopeFileName("AA_004.txt"));
}

BOOST_AUTO_TEST_SUITE_END()
