/**
  *  @copyright Copyright (c) 2014, J-PET collaboration
  *  @file JPetManager.cp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "./JPetManager.h"

#include <cassert>
#include <ctime>
#include <string>
#include <TDSet.h>
#include <TThread.h>
#include "../../JPetLoggerInclude.h"
#include "../CommonTools/CommonTools.h"


JPetManager& JPetManager::getManager()
{
  static JPetManager instance;
  return instance;
}

void JPetManager::run()
{
  vector<JPetAnalysisRunner*> runners;
  vector<TThread*> threads;

  int numberOfFiles = getFullInputFileNames().size();
  for (int i = 0; i < numberOfFiles; i++) {
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

  INFO( "======== Finished processing all tasks: " + CommonTools::getTimeString() + " ========\n" );
}

void JPetManager::parseCmdLine(int argc, char** argv)
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

std::vector<std::string> JPetManager::getFullInputFileNames() const
{
  return fCmdParser.getFileNames();
}


void JPetManager::addTaskGeneratorChain(TaskGeneratorChain* taskGeneratorChain)
{
  ftaskGeneratorChain = taskGeneratorChain;
}
