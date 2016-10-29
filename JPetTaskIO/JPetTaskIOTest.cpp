#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskIOTest
#include <boost/test/unit_test.hpp>
#include "../DBHandler/HeaderFiles/DBHandler.h"
#include "../JPetCmdParser/JPetCmdParser.h"
#include "../JPetTaskIO/JPetTaskIO.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)


char* convertStringToCharP(const std::string& s)
{
  char* pc = new char[s.size() + 1];
  std::strcpy(pc, s.c_str());
  return pc;
}

std::vector<char*> createArgs(const std::string& commandLine)
{
  std::istringstream iss(commandLine);
  std::vector<std::string> args {std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>{}
                                };
  std::vector<char*> args_char;
  std::transform(args.begin(), args.end(), std::back_inserter(args_char), convertStringToCharP);
  return args_char;
}

BOOST_AUTO_TEST_CASE(progressBarTest)
{
  JPetTaskIO taskIO;
  taskIO.displayProgressBar(5, 100);
}
class JPetTaskIO_test: public JPetTaskIO
{
public:
  JPetTaskIO_test() {}
  virtual ~JPetTaskIO_test() {}

  using JPetTaskIO::setUserLimits;
};
BOOST_AUTO_TEST_CASE( setUserLimits)
{
  auto commandLine = "./main.x -t root -f unitTestData/JPetTaskIOTest/cosm_barrel.hld.root -i 26 -r 1000 1001";
  auto args_char = createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  JPetCmdParser parser;
  auto options = parser.parseAndGenerateOptions(argc, const_cast<const char**>(argv));
  auto first = 0ll;
  auto last = 0ll;
  auto opt = options.front().getOptions();
  JPetOptions optObject(opt);
  JPetTaskIO_test task;
  task.setUserLimits(optObject, 10000, first, last);
  BOOST_REQUIRE_EQUAL(first, 1000);
  BOOST_REQUIRE_EQUAL(last, 1001);
}

BOOST_AUTO_TEST_CASE( setUserLimits2 )
{
  auto commandLine = "./main.x -t root -f unitTestData/JPetTaskIOTest/cosm_barrel.hld.root -i 26 -r 1000 1001";
  auto args_char = createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  JPetCmdParser parser;
  auto options = parser.parseAndGenerateOptions(argc, const_cast<const char**>(argv));
  auto first = 0ll;
  auto last = 0ll;
  auto opt = options.front().getOptions();
  JPetOptions optObject(opt);
  JPetTaskIO_test task;
  task.setUserLimits(optObject, 1, first, last);
  BOOST_REQUIRE_EQUAL(first, 0);
  BOOST_REQUIRE_EQUAL(last, 0);
}

BOOST_AUTO_TEST_SUITE_END()
