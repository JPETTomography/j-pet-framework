/**
  *  @copyright Copyright (c) 2015, J-PET collaboration
  *  @file JPetManager.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "./JPetManager.h"

#include <cassert>
#include <ctime>
#include <string>

#include "../JPetLoggerInclude.h"
#include "../JPetScopeReader/JPetScopeReader.h"
#include "../CommonTools/CommonTools.h"
#include "../JPetCmdParser/JPetCmdParser.h"

#include <TDSet.h>
#include <TThread.h>




JPetManager& JPetManager::getManager()
{
  static JPetManager instance;
  return instance;
}

void JPetManager::run()
{
  INFO( "======== Starting processing all tasks: " + CommonTools::getTimeString() + " ========\n" );
  std::vector<JPetTaskExecutor*> executors;
  std::vector<TThread*> threads;
  auto i = 0;
  for (auto opt : fOptions) {
    JPetTaskExecutor* executor = new JPetTaskExecutor(fTaskGeneratorChain, i, opt);
    executors.push_back(executor);
    auto thr = executor->run();
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
  for (auto executor : executors) {
    delete executor;
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
  /**/
}

void JPetManager::registerTask(const TaskGenerator& taskGen)
{
  assert(fTaskGeneratorChain);
  fTaskGeneratorChain->push_back(taskGen);
}
