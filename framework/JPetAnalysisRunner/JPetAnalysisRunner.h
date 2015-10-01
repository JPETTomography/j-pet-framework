//
// Created by karol on 12.05.15.
//

#ifndef FRAMEWORK_JPETANALYSISRUNNER_H
#define FRAMEWORK_JPETANALYSISRUNNER_H

#include <string>
#include <list>
#include <TThread.h>
#include <functional> // for TaskGenerator declaration
#include <vector> // for TaskGeneratorChain declaration
//#include "../JPetAnalysisModule/JPetAnalysisModule.h"
//#include "../JPetCommonAnalysisModule/JPetCommonAnalysisModule.h"
#include "../JPetTaskInterface/JPetTaskInterface.h"
#include "../JPetCmdParser/JPetCmdParser.h"
#include "../JPetParamManager/JPetParamManager.h"
#include "../JPetUnpacker/JPetUnpacker.h"

#include "../JPetOptions/JPetOptions.h"


//using TaskGenerator = std::function< JPetTaskInterface* () >;
using TaskGenerator = std::function< JPetTaskInterface* () >;

//using TaskGenerator = std::function< JPetCommonAnalysisModule* () >;
using TaskGeneratorChain = std::vector<TaskGenerator>;

class JPetAnalysisRunner
{
public :
    JPetAnalysisRunner(TaskGeneratorChain *taskGeneratorChain, int processedFile, JPetOptions opts);
    TThread* run();
    virtual ~JPetAnalysisRunner();

private:
    static void* processProxy(void*);
    void process();
    void ProcessFromCmdLineArgs(int fileIndex);
    //std::vector<std::string> getFullInputFileNames() const;
    //std::string getBaseInputFileName(string name) const;
    //std::vector<std::string> getStrippedInputFileNames(const std::vector<std::string>& fileNames) const;

    //void UnpackFile() { if(fCmdParser.IsFileTypeSet()) fUnpacker.exec();}
    void UnpackFile() { }

    int fProcessedFile;
    JPetParamManager fParamManager;
    JPetUnpacker fUnpacker;
    std::list<JPetTaskInterface*> fTasks;
    std::list<JPetTaskInterface*>::iterator currentTask;
    TaskGeneratorChain* ftaskGeneratorChain;
    JPetOptions fOptions;
};


#endif //FRAMEWORK_JPETANALYSISRUNNER_H
