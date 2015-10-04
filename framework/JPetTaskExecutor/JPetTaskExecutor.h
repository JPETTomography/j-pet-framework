//
// Created by karol on 12.05.15.
//

#ifndef FRAMEWORK_JPETTASKEXECUTOR_H
#define FRAMEWORK_JPETTASKEXECUTOR_H

#include <string>
#include <list>
#include <TThread.h>
#include <functional> // for TaskGenerator declaration
#include <vector> // for TaskGeneratorChain declaration
#include "../JPetTaskInterface/JPetTaskInterface.h"
#include "../JPetCmdParser/JPetCmdParser.h"
#include "../JPetParamManager/JPetParamManager.h"
#include "../JPetUnpacker/JPetUnpacker.h"
#include "../JPetOptions/JPetOptions.h"

using TaskGenerator = std::function< JPetTaskInterface* () >;
using TaskGeneratorChain = std::vector<TaskGenerator>;

class JPetTaskExecutor
{
public :
    JPetTaskExecutor(TaskGeneratorChain *taskGeneratorChain, int processedFile, JPetOptions opts);
    TThread* run();
    virtual ~JPetTaskExecutor();

private:
    static void* processProxy(void*);
    void process();
    void ProcessFromCmdLineArgs(int fileIndex);
    void UnpackFile();

    int fProcessedFile;
    JPetParamManager fParamManager;
    JPetUnpacker fUnpacker;
    std::list<JPetTaskInterface*> fTasks;
    std::list<JPetTaskInterface*>::iterator currentTask;
    TaskGeneratorChain* ftaskGeneratorChain;
    JPetOptions fOptions;
};


#endif //FRAMEWORK_JPETTASKEXECUTOR_H
