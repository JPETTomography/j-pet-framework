#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskIOTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetTaskIO/JPetTaskIO.h"
#include "TaskA.h"
#include "TaskB.h"
#include "TaskC1.h"
#include "TaskC2.h"
#include "TaskC3.h"
#include "TaskD.h"
#include "TaskE.h"

// methods
//virtual void init(const JPetTaskInterface::Options& opts);
//virtual void exec();
//virtual void terminate();
//virtual ~JPetTaskIO();
//virtual void addSubTask(JPetTaskInterface* subtask);
//void manageProgressBar(long long done, long long end);
//float setProgressBar(int currentEventNumber, int numberOfEvents);



using Options = std::map<std::string, std::string>;


BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( my_testA )
{
  Options options = {
    {"inputFile", "data_files/cosm_barrel.hld.root"},
    {"inputFileType", "hld"},
    {"outputFile", "data_files/cosm_barrel.tslot.raw.out.root"},
    {"outputFileType", "tslot.raw"},
    {"firstEvent", "1"},
    {"lastEvent", "10"},
    {"progressBar", "false"}
  };
  JPetParamManager myParamManager("../DBConfig/configDB.cfg.koza");
  //JPetParamManager myParamManager;
  myParamManager.getParametersFromDatabase(26);
  JPetTaskIO task;
  task.setParamManager(&myParamManager);
  auto myTask = new TaskA();
  myTask->setParamManager(&myParamManager);
  task.addSubTask(myTask); 
  task.init(options);
  task.exec();
  task.terminate();

  BOOST_REQUIRE(1 == 0);
}

BOOST_AUTO_TEST_CASE( my_testB )
{
  Options options = {
    {"inputFile", "data_files/cosm_barrel.tslot.raw.root"},
    {"inputFileType", "tslot.raw"},
    {"outputFile", "data_files/cosm_barrel.tslot.cal.out.root"},
    {"outputFileType", "tslot.cal"},
    {"firstEvent", "1"},
    {"lastEvent", "10"},
    {"progressBar", "false"}
  };
  //JPetParamManager myParamManager("../DBConfig/configDB.cfg.koza");
  JPetParamManager myParamManager;
  //myParamManager.getParametersFromDatabase(26);
  JPetTaskIO task;
  task.setParamManager(&myParamManager);
  auto myTask = new TaskB();
  myTask->setParamManager(&myParamManager);
  task.addSubTask(myTask); 
  task.init(options);
  task.exec();
  task.terminate();

  BOOST_REQUIRE(1 == 0);
}

BOOST_AUTO_TEST_CASE( my_testC1 )
{
  Options options = {
    {"inputFile", "data_files/cosm_barrel.tslot.cal.root"},
    {"inputFileType", "tslot.cal"},
    {"outputFile", "data_files/cosm_barrel.raw.sig.out.root"},
    {"outputFileType", "raw.sig"},
    {"firstEvent", "1"},
    {"lastEvent", "10"},
    {"progressBar", "false"}
  };
  //JPetParamManager myParamManager("../DBConfig/configDB.cfg.koza");
  JPetParamManager myParamManager;
  //myParamManager.getParametersFromDatabase(26);
  JPetTaskIO task;
  task.setParamManager(&myParamManager);
  auto myTask = new TaskC1();
  myTask->setParamManager(&myParamManager);
  task.addSubTask(myTask); 
  task.init(options);
  task.exec();
  task.terminate();

  BOOST_REQUIRE(1 == 0);
}

BOOST_AUTO_TEST_CASE( my_testC2 )
{
  Options options = {
    {"inputFile", "data_files/cosm_barrel.raw.sig.root"},
    {"inputFileType", "raw.sig"},
    {"outputFile", "data_files/cosm_barrel.reco.sig.out.root"},
    {"outputFileType", "reco.sig"},
    {"firstEvent", "1"},
    {"lastEvent", "10"},
    {"progressBar", "false"}
  };
  //JPetParamManager myParamManager("../DBConfig/configDB.cfg.koza");
  JPetParamManager myParamManager;
  //myParamManager.getParametersFromDatabase(26);
  auto myTask = new TaskC2();
  JPetTaskIO task;
  task.addSubTask(myTask); 
  task.setParamManager(&myParamManager);
  task.init(options);
  task.exec();
  task.terminate();

  BOOST_REQUIRE(1 == 0);
}

BOOST_AUTO_TEST_CASE( my_testC3 )
{
  Options options = {
    {"inputFile", "data_files/cosm_barrel.reco.sig.root"},
    {"inputFileType", "reco.sig"},
    {"outputFile", "data_files/cosm_barrel.phys.sig.out.root"},
    {"outputFileType", "phys.sig"},
    {"firstEvent", "1"},
    {"lastEvent", "10"},
    {"progressBar", "false"}
  };
  //JPetParamManager myParamManager("../DBConfig/configDB.cfg.koza");
  JPetParamManager myParamManager;
  //myParamManager.getParametersFromDatabase(26);
  auto myTask = new TaskC3();
  JPetTaskIO task;
  task.addSubTask(myTask); 
  task.setParamManager(&myParamManager);
  task.init(options);
  task.exec();
  task.terminate();

  BOOST_REQUIRE(1 == 0);
}

BOOST_AUTO_TEST_CASE( my_test1 )
{
  Options options = {
    {"inputFile", "data_files/cosm_barrel.phys.sig.root"},
    {"inputFileType", "phys.sig"},
    {"outputFile", "data_files/cosm_barrel.phys.hit.out.root"},
    {"outputFileType", "phys.hit"},
    {"firstEvent", "1"},
    {"lastEvent", "10"},
    {"progressBar", "false"}
  };
  //JPetParamManager myParamManager("../DBConfig/configDB.cfg.koza");
  JPetParamManager myParamManager;
  //myParamManager.getParametersFromDatabase(26);
  auto myTask = new TaskD();
  JPetTaskIO task;
  task.addSubTask(myTask); 
  task.setParamManager(&myParamManager);
  task.init(options);
  task.exec();
  task.terminate();

  BOOST_REQUIRE(1 == 0);
}
BOOST_AUTO_TEST_CASE( my_test2 )
{
  Options options = {
    {"inputFile", "data_files/cosm_barrel.phys.hit.root"},
    {"inputFileType", "phys.hit"},
    {"outputFile", "data_files/cosm_barrel.phys.eve.out.root"},
    {"outputFileType", "phys.eve"},
    {"firstEvent", "1"},
    {"lastEvent", "10"},
    {"progressBar", "false"}
  };
  //JPetParamManager myParamManager("../DBConfig/configDB.cfg.koza");
  //myParamManager.getParametersFromDatabase(26);
  JPetParamManager myParamManager;
  auto myTask = new TaskE();
  JPetTaskIO task;
  task.addSubTask(myTask); 
  task.setParamManager(&myParamManager);
  task.init(options);
  task.exec();
  task.terminate();

  BOOST_REQUIRE(1 == 0);
}

BOOST_AUTO_TEST_SUITE_END()
