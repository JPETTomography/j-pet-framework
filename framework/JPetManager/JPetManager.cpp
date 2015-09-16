/**
  *  @copyright Copyright (c) 2014, J-PET collaboration
  *  @file JPetManager.cp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "./JPetManager.h"

#include <cassert>
#include <ctime>
#include <string>

#include "../../JPetLoggerInclude.h"

#include <TDSet.h>
#include <TThread.h>

JPetManager& JPetManager::GetManager()
{
  static JPetManager instance;
  return instance;
}

JPetManager::JPetManager(): TNamed("JPetMainManager", "JPetMainManager")
{

}

void JPetManager::Run()
{
  vector<string> fileNames = getInputFileNames();
  vector<JPetAnalysisRunner*> runners;
  vector<TThread*> threads;

  for (int i = 0; i < fileNames.size(); i++) {
    JPetAnalysisRunner* runner = new JPetAnalysisRunner(ftaskGeneratorChain, i, fCmdParser);
    runners.push_back(runner);
    auto thr = runner->run();
    if (thr) {
      threads.push_back(thr);
    } else {
      ERROR("thread pointer is null");
    }
  }
  for (auto thread : threads) {
    thread->Join();
  }
  for (auto runner : runners) {
    delete runner;
  }

  INFO( "======== Finished processing all tasks: " + GetTimeString() + " ========\n" );
}

void JPetManager::ParseCmdLine(int argc, char** argv)
{
  fCmdParser.parse(argc, (const char**)argv);
}

int JPetManager::getRunNumber() const
{
  if (fCmdParser.isRunNumberSet()) {
    return fCmdParser.getRunNumber();
  }
  return -1;
}

JPetManager::~JPetManager()
{
}

/**
 * @brief Get Input File name stripped off the extension and the suffixes like .tslot.* or .phys.*
 *
 * Example: if the file given on command line was ../file.phys.hit.root, this method will return ../file
 */

std::vector<std::string> JPetManager::getInputFileNames() const
{
  std::vector<std::string> fileNames = fCmdParser.getFileNames();
  std::vector<std::string> parsedNames;
  for (int i = 0; i < fileNames.size(); i++) {
    std::string name = fileNames[i].c_str();
    // strip suffixes of type .tslot.* and .phys.*
    int pos = name.find(".tslot");
    if (pos == std::string::npos) {
      pos = name.find(".phys");
    }
    if (pos == std::string::npos) {
      pos = name.find(".hld");
    }
    if (pos == std::string::npos) {
      pos = name.find(".root");
    }
    if (pos != std::string::npos) {
      name.erase(pos);
    }
    parsedNames.push_back(name);
  }
  return parsedNames;
}

/**
 * @brief returns the time TString in the format dd.mm.yyyy HH:MM
 */
TString JPetManager::GetTimeString() const
{
  time_t _tm = time(NULL );
  struct tm* curtime = localtime ( &_tm );
  char buf[100];
  strftime( buf, 100, "%d.%m.%Y %R", curtime);

  return TString( buf );
}

void JPetManager::AddTaskGeneratorChain(TaskGeneratorChain* taskGeneratorChain)
{
  ftaskGeneratorChain = taskGeneratorChain;
}
