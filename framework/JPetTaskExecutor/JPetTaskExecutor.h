//
// Created by karol on 12.05.15.
//

#ifndef FRAMEWORK_JPETTASKEXECUTOR_H
#define FRAMEWORK_JPETTASKEXECUTOR_H

#include <list>
#include <TThread.h>
#include <functional> // for TaskGenerator declaration
#include <vector> // for TaskGeneratorChain declaration
#include "../JPetParamManager/JPetParamManager.h"
#include "../JPetUnpacker/JPetUnpacker.h"
#include "../JPetOptions/JPetOptions.h"

class JPetTaskInterface;
using TaskGenerator = std::function< JPetTaskInterface* () >;
using TaskGeneratorChain = std::vector<TaskGenerator>;


class JPetTaskExecutor
{
public :
  JPetTaskExecutor(TaskGeneratorChain* taskGeneratorChain, int processedFile, JPetOptions opts);
  TThread* run();
  virtual ~JPetTaskExecutor();

private:
  static void* processProxy(void*);
  void process();
  void processFromCmdLineArgs(int fileIndex);
  void unpackFile();

  int fProcessedFile;
  JPetParamManager fParamManager;
  JPetUnpacker fUnpacker;
  std::list<JPetTaskInterface*> fTasks;
  TaskGeneratorChain* ftaskGeneratorChain;
  JPetOptions fOptions;
};


#endif //FRAMEWORK_JPETTASKEXECUTOR_H
