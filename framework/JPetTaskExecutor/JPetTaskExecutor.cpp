//
// Created by karol on 12.05.15.
//

#include "JPetTaskExecutor.h"
#include <cassert>
#include "../JPetTaskInterface/JPetTaskInterface.h"
#include "../JPetScopeReader/JPetScopeReader.h"

JPetTaskExecutor::JPetTaskExecutor(TaskGeneratorChain* taskGeneratorChain, int processedFileId, JPetOptions opt) :
  ftaskGeneratorChain(taskGeneratorChain),
  fProcessedFile(processedFileId),
  fOptions(opt)
{
  if (taskGeneratorChain) {
    for (auto taskGenerator : *ftaskGeneratorChain) {
      auto task = taskGenerator();
      task->setParamManager(&fParamManager); // maybe that should not be here
      fTasks.push_back(task);
    }
  } else {
    ERROR("taskGeneratorChain is null while constructing JPetTaskExecutor");
  }
}

void JPetTaskExecutor::process()
{
  processFromCmdLineArgs(fProcessedFile);
  for (auto currentTask = fTasks.begin(); currentTask != fTasks.end(); currentTask++) {
    (*currentTask)->init(fOptions.getOptions());
    (*currentTask)->exec();
    (*currentTask)->terminate();
  }
}

void* JPetTaskExecutor::processProxy(void* runner)
{
  static_cast<JPetTaskExecutor*>(runner)->process();
}

TThread* JPetTaskExecutor::run()
{
  TThread* thread = new TThread(to_string(fProcessedFile).c_str(), processProxy, (void*)this);
  assert(thread);
  thread->Run();
  return thread;
}

void JPetTaskExecutor::processFromCmdLineArgs(int fileIndex)
{
  auto runNum = fOptions.getRunNumber();
  if (runNum >= 0) {
    fParamManager.getParametersFromDatabase(runNum); /// @todo some error handling
  }
  auto inputFileType = fOptions.getInputFileType();
  auto inputFile = fOptions.getInputFile();
  if (inputFileType == JPetOptions::kScope) {
    JPetScopeReader* module = new JPetScopeReader("JPetScopeReader", "Process Oscilloscope ASCII data into JPetRecoSignal structures.");
    module->setFileName(inputFile);
    fTasks.push_front(module);
  } else if (inputFileType == JPetOptions::kHld) {
    fUnpacker.setParams(fOptions.getInputFile());
    unpackFile();
  }
}

void JPetTaskExecutor::unpackFile()
{
  if (fOptions.getInputFileType() == JPetOptions::kHld) {
    fUnpacker.exec();
  } else {
    WARNING("Input file is not hld and unpacker was supposed to be called!");
  }
}

JPetTaskExecutor::~JPetTaskExecutor()
{
  for (auto task : fTasks) {
    delete task;
  }
}
