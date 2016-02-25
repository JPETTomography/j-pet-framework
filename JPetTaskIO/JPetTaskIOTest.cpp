#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskIOTest
#include <boost/test/unit_test.hpp>

#define private public
#define protected public
#include "../JPetTaskIO/JPetTaskIO.h"
#undef private
#undef protected
#include "../JPetCmdParser/JPetCmdParser.h"
//#include "TaskA.h"
//#include "TaskB.h"
//#include "TaskC1.h"
//#include "TaskC2.h"
//#include "TaskC3.h"
//#include "TaskD.h"
//#include "TaskE.h"

// methods
//virtual void init(const JPetTaskInterface::Options& opts);
//virtual void exec();
//virtual void terminate();
//virtual ~JPetTaskIO();
//virtual void addSubTask(JPetTaskInterface* subtask);
//void manageProgressBar(long long done, long long end);
//float setProgressBar(int currentEventNumber, int numberOfEvents);

///protected:
//virtual void createInputObjects(const char* inputFilename);
//virtual void createOutputObjects(const char* outputFilename);
//void setUserLimits(const JPetOptions& opts, long long& firstEvent, long long& lastEvent) const;



//using Options = std::map<std::string, std::string>;


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
    BOOST_REQUIRE_EQUAL(taskIO.setProgressBar(5, 100), 5);
    taskIO.manageProgressBar(5, 100);
}

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
  JPetTaskIO task;
  task.setUserLimits(optObject,10000, first,last); 
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
  JPetTaskIO task;
  task.setUserLimits(optObject,1, first,last); 
  BOOST_REQUIRE_EQUAL(first, 0);
  BOOST_REQUIRE_EQUAL(last, 0);
}

BOOST_AUTO_TEST_CASE( my_testA )
{
  //Options options = {
    //{"inputFile", "data_files/cosm_barrel.hld.root"},
    //{"inputFileType", "hld"},
    //{"outputFile", "data_files/cosm_barrel.tslot.raw.out.root"},
    //{"outputFileType", "tslot.raw"},
    //{"firstEvent", "1"},
    //{"lastEvent", "10"},
    //{"progressBar", "false"}
  //};
  //JPetParamManager myParamManager("../DBConfig/configDB.cfg.koza");
  ////JPetParamManager myParamManager;
  //myParamManager.getParametersFromDatabase(26);
  //JPetTaskIO task;
  //task.setParamManager(&myParamManager);
  //auto myTask = new TaskA();
  //myTask->setParamManager(&myParamManager);
  //task.addSubTask(myTask); 
  //task.init(options);
  //task.exec();
  //task.terminate();

  //BOOST_REQUIRE(1 == 0);
//}

//BOOST_AUTO_TEST_CASE( my_testB )
//{
  //Options options = {
    //{"inputFile", "data_files/cosm_barrel.tslot.raw.root"},
    //{"inputFileType", "tslot.raw"},
    //{"outputFile", "data_files/cosm_barrel.tslot.cal.out.root"},
    //{"outputFileType", "tslot.cal"},
    //{"firstEvent", "1"},
    //{"lastEvent", "10"},
    //{"progressBar", "false"}
  //};
  ////JPetParamManager myParamManager("../DBConfig/configDB.cfg.koza");
  //JPetParamManager myParamManager;
  ////myParamManager.getParametersFromDatabase(26);
  //JPetTaskIO task;
  //task.setParamManager(&myParamManager);
  //auto myTask = new TaskB();
  //myTask->setParamManager(&myParamManager);
  //task.addSubTask(myTask); 
  //task.init(options);
  //task.exec();
  //task.terminate();

  //BOOST_REQUIRE(1 == 0);
//}

//BOOST_AUTO_TEST_CASE( my_testC1 )
//{
  //Options options = {
    //{"inputFile", "data_files/cosm_barrel.tslot.cal.root"},
    //{"inputFileType", "tslot.cal"},
    //{"outputFile", "data_files/cosm_barrel.raw.sig.out.root"},
    //{"outputFileType", "raw.sig"},
    //{"firstEvent", "1"},
    //{"lastEvent", "10"},
    //{"progressBar", "false"}
  //};
  ////JPetParamManager myParamManager("../DBConfig/configDB.cfg.koza");
  //JPetParamManager myParamManager;
  ////myParamManager.getParametersFromDatabase(26);
  //JPetTaskIO task;
  //task.setParamManager(&myParamManager);
  //auto myTask = new TaskC1();
  //myTask->setParamManager(&myParamManager);
  //task.addSubTask(myTask); 
  //task.init(options);
  //task.exec();
  //task.terminate();

  //BOOST_REQUIRE(1 == 0);
//}

//BOOST_AUTO_TEST_CASE( my_testC2 )
//{
  //Options options = {
    //{"inputFile", "data_files/cosm_barrel.raw.sig.root"},
    //{"inputFileType", "raw.sig"},
    //{"outputFile", "data_files/cosm_barrel.reco.sig.out.root"},
    //{"outputFileType", "reco.sig"},
    //{"firstEvent", "1"},
    //{"lastEvent", "10"},
    //{"progressBar", "false"}
  //};
  ////JPetParamManager myParamManager("../DBConfig/configDB.cfg.koza");
  //JPetParamManager myParamManager;
  ////myParamManager.getParametersFromDatabase(26);
  //auto myTask = new TaskC2();
  //JPetTaskIO task;
  //task.addSubTask(myTask); 
  //task.setParamManager(&myParamManager);
  //task.init(options);
  //task.exec();
  //task.terminate();

  //BOOST_REQUIRE(1 == 0);
//}

//BOOST_AUTO_TEST_CASE( my_testC3 )
//{
  //Options options = {
    //{"inputFile", "data_files/cosm_barrel.reco.sig.root"},
    //{"inputFileType", "reco.sig"},
    //{"outputFile", "data_files/cosm_barrel.phys.sig.out.root"},
    //{"outputFileType", "phys.sig"},
    //{"firstEvent", "1"},
    //{"lastEvent", "10"},
    //{"progressBar", "false"}
  //};
  ////JPetParamManager myParamManager("../DBConfig/configDB.cfg.koza");
  //JPetParamManager myParamManager;
  ////myParamManager.getParametersFromDatabase(26);
  //auto myTask = new TaskC3();
  //JPetTaskIO task;
  //task.addSubTask(myTask); 
  //task.setParamManager(&myParamManager);
  //task.init(options);
  //task.exec();
  //task.terminate();

  //BOOST_REQUIRE(1 == 0);
//}

//BOOST_AUTO_TEST_CASE( my_test1 )
//{
  //Options options = {
    //{"inputFile", "data_files/cosm_barrel.phys.sig.root"},
    //{"inputFileType", "phys.sig"},
    //{"outputFile", "data_files/cosm_barrel.phys.hit.out.root"},
    //{"outputFileType", "phys.hit"},
    //{"firstEvent", "1"},
    //{"lastEvent", "10"},
    //{"progressBar", "false"}
  //};
  ////JPetParamManager myParamManager("../DBConfig/configDB.cfg.koza");
  //JPetParamManager myParamManager;
  ////myParamManager.getParametersFromDatabase(26);
  //auto myTask = new TaskD();
  //JPetTaskIO task;
  //task.addSubTask(myTask); 
  //task.setParamManager(&myParamManager);
  //task.init(options);
  //task.exec();
  //task.terminate();

  //BOOST_REQUIRE(1 == 0);
//}
//BOOST_AUTO_TEST_CASE( my_test2 )
//{
  //Options options = {
    //{"inputFile", "data_files/cosm_barrel.phys.hit.root"},
    //{"inputFileType", "phys.hit"},
    //{"outputFile", "data_files/cosm_barrel.phys.eve.out.root"},
    //{"outputFileType", "phys.eve"},
    //{"firstEvent", "1"},
    //{"lastEvent", "10"},
    //{"progressBar", "false"}
  //};
  ////JPetParamManager myParamManager("../DBConfig/configDB.cfg.koza");
  ////myParamManager.getParametersFromDatabase(26);
  //JPetParamManager myParamManager;
  //auto myTask = new TaskE();
  //JPetTaskIO task;
  //task.addSubTask(myTask); 
  //task.setParamManager(&myParamManager);
  //task.init(options);
  //task.exec();
  //task.terminate();

  //BOOST_REQUIRE(1 == 0);
}

BOOST_AUTO_TEST_SUITE_END()
