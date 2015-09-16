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

//using TaskGenerator = std::function< JPetTaskInterface* () >;
using TaskGenerator = std::function< JPetTaskInterface* () >;
//using TaskGenerator = std::function< JPetCommonAnalysisModule* () >;
using TaskGeneratorChain = std::vector<TaskGenerator>;

class JPetAnalysisRunner
{
public :
    JPetAnalysisRunner(TaskGeneratorChain *taskGeneratorChain, int processedFile, JPetCmdParser& cmdParse);
    TThread* run();
    virtual ~JPetAnalysisRunner();

private:
    static void* processProxy(void*);
    void process();
    void ProcessFromCmdLineArgs(int fileIndex);
    float setProgressBar(int currentEventNumber, int numberOfEvents);
    void prepareCurrentTaskForFile(const string& file);
    void setEventBounds(long long& begin, long long& end, long long& eventCount);
    void processEventsInRange(long long begin, long long end);
    bool userBoundsAreCorrect(long long checkedEvent);
    void manageProgressBar(long long done, long long end);
    std::vector<std::string> getFullInputFileNames() const;
    std::string getBaseInputFileName(string name) const;
    std::vector<std::string> getStrippedInputFileNames(const std::vector<std::string>& fileNames) const;

    void UnpackFile() { if(fCmdParser.IsFileTypeSet()) fUnpacker.exec();}

    int fProcessedFile;
    JPetCmdParser& fCmdParser;
    JPetParamManager fParamManager;
    JPetUnpacker fUnpacker;
    std::list<JPetTaskInterface*> fTasks;
    std::list<JPetTaskInterface*>::iterator currentTask;
    //std::list<JPetAnalysisModule*> fTasks;
    //std::list<JPetAnalysisModule*>::iterator currentTask;
    TaskGeneratorChain* ftaskGeneratorChain;
    bool fIsProgressBarEnabled;

};


#endif //FRAMEWORK_JPETANALYSISRUNNER_H
