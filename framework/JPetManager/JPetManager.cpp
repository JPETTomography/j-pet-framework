/**
  *  @copyright Copyright (c) 2014, J-PET collaboration
  *  @file JPetManager.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "./JPetManager.h"

#include <cassert>
#include <ctime>
#include <string>
#include <TDSet.h>
#include <TThread.h>
#include "../JPetCmdParser/JPetCmdParser.h"
#include "../../JPetLoggerInclude.h"
#include "../CommonTools/CommonTools.h"


JPetManager& JPetManager::getManager()
{
  static JPetManager instance;
  return instance;
}

void JPetManager::run()
{
  INFO( "======== Starting processing all tasks: " + CommonTools::getTimeString() + " ========\n" );
  std::vector<JPetAnalysisRunner*> runners;
  std::vector<TThread*> threads;
  int i = 0;
  for (auto opt: fOptions) {
    JPetAnalysisRunner* runner = new JPetAnalysisRunner(ftaskGeneratorChain, i, opt);
    runners.push_back(runner);
    auto thr = runner->run();
    if (thr) {
      threads.push_back(thr);
    } else {
      ERROR("thread pointer is null");
    }
    i++;
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
  JPetCmdParser parser;
  fOptions = parser.parseAndGenerateOptions(argc, (const char**)argv);
}

JPetManager::~JPetManager()
{
}


void JPetManager::addTaskGeneratorChain(TaskGeneratorChain* taskGeneratorChain)
{
  ftaskGeneratorChain = taskGeneratorChain;
}
