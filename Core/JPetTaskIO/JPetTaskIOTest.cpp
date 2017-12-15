#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskIOTest
#include <boost/test/unit_test.hpp>
#include "./JPetCmdParser/JPetCmdParser.h"
#include "./JPetTaskIO/JPetTaskIO.h"
#include "./JPetOptionsGenerator/JPetOptionsGenerator.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(progressBarTest)
{
  JPetTaskIO taskIO;
  taskIO.displayProgressBar(5, 100);
}

//BOOST_AUTO_TEST_CASE(progressBarTest)
//{
  //JPetTaskIO taskIO;
  //taskIO.displayProgressBar(5, 100);
//}
//class JPetTaskIO_test: public JPetTaskIO
//{
//public:
  //JPetTaskIO_test() {}
  //virtual ~JPetTaskIO_test() {}

  //using JPetTaskIO::setUserLimits;
//};

////std::vector<JPetOptions> getOptionsBasedOnCmdLineArgs(const std::string& cmdLine)
////{
  ////auto args_char = JPetCommonTools::createArgs(cmdLine);
  ////auto argc = args_char.size();
  ////auto argv = args_char.data();

  ////JPetCmdParser parser;
  ////JPetOptionsGenerator optGenerator;
  ////return optGenerator.generateOptions(parser.parseCmdLineArgs(argc, const_cast<const char**>(argv)));
////}

//BOOST_AUTO_TEST_CASE( setUserLimits)
//{
  //auto commandLine = "./main.x -t root -f unitTestData/JPetTaskIOTest/cosm_barrel.hld.root -i 26 -r 1000 1001";
  //auto options = getOptionsBasedOnCmdLineArgs(commandLine); //optGenerator.generateOptions(parser.parseCmdLineArgs(argc, const_cast<const char**>(argv)));
  //auto first = 0ll;
  //auto last = 0ll;
  //auto opt = options.front().getOptions();
  //JPetOptions optObject(opt);
  //JPetTaskIO_test task;
  //task.setUserLimits(optObject, 10000, first, last);
  //BOOST_REQUIRE_EQUAL(first, 1000);
  //BOOST_REQUIRE_EQUAL(last, 1001);
//}

//BOOST_AUTO_TEST_CASE( setUserLimits2 )
//{
  //auto commandLine = "./main.x -t root -f unitTestData/JPetTaskIOTest/cosm_barrel.hld.root -i 26 -r 1000 1001";
  //auto options = getOptionsBasedOnCmdLineArgs(commandLine);
  //auto first = 0ll;
  //auto last = 0ll;
  //auto opt = options.front().getOptions();
  //JPetOptions optObject(opt);
  //JPetTaskIO_test task;
  //task.setUserLimits(optObject, 1, first, last);
  //BOOST_REQUIRE_EQUAL(first, 0);
  //BOOST_REQUIRE_EQUAL(last, 0);
//}

BOOST_AUTO_TEST_SUITE_END()
