//
// Created by karol on 12.05.15.
//

#include "JPetAnalysisRunner.h"
#include "../JPetScopeReader/JPetScopeReader.h"

JPetAnalysisRunner::JPetAnalysisRunner(TaskGeneratorChain *taskGeneratorChain, int processedFile, JPetCmdParser& cmdParser) :
    ftaskGeneratorChain(taskGeneratorChain),
    fProcessedFile(processedFile),
    fCmdParser(cmdParser),
    fIsProgressBarEnabled(cmdParser.isProgressBarSet())
{
    for(auto taskGenerator: *ftaskGeneratorChain)
    {
        auto task = taskGenerator();
        task->setParamManager(&fParamManager);
        fTasks.push_back(task);
    }
}

void JPetAnalysisRunner::process()
{
    std::vector<std::string> fileNames = getInputFileNames();
    ProcessFromCmdLineArgs(fProcessedFile);
    currentTask = fTasks.begin();
    long long  kNevent = (*currentTask)->getEventNb();
    long long kFirstEvent = 0;
    long long kLastEvent = 0;
    for (currentTask = fTasks.begin(); currentTask != fTasks.end(); currentTask++)
    {
        prepareCurrentTaskForFile(fileNames[fProcessedFile]);
        setEventBounds(kFirstEvent, kLastEvent, kNevent);
        processEventsInRange(kFirstEvent, kLastEvent);
        (*currentTask)->terminate();
    }
}

void* JPetAnalysisRunner::processProxy(void* runner)
{
    static_cast<JPetAnalysisRunner*>(runner)->process();
}

TThread* JPetAnalysisRunner::run()
{
    TThread *thread = new TThread(to_string(fProcessedFile).c_str(), processProxy, (void*)this);
    thread->Run();
    return thread;
}

void JPetAnalysisRunner::prepareCurrentTaskForFile(const string& file)
{
    std::string tmpFile (file);
    (*currentTask)->createInputObjects( tmpFile.c_str() ); /// readers
    (*currentTask)->createOutputObjects( tmpFile.c_str() ); /// writers + histograms
}

void JPetAnalysisRunner::setEventBounds(long long& begin, long long& end, long long& eventCount)
{
    if (userBoundsAreCorrect(eventCount) && currentTask == fTasks.begin())
    {
        begin = fCmdParser.getLowerEventBound();
        end = fCmdParser.getHigherEventBound();
        eventCount = end - begin + 1;
    }
    else
    {
        eventCount = (*currentTask)->getEventNb();
        begin = 0;
        end = eventCount - 1;
    }
}

void JPetAnalysisRunner::processEventsInRange(long long begin, long long end)
{
    for (long long i = begin; i <= end; i++)
    {
        manageProgressBar(i, end);
        (*currentTask)->exec();
    }
}

bool JPetAnalysisRunner::userBoundsAreCorrect(long long numberOfEvents)
{
    return fCmdParser.getLowerEventBound() != -1 &&
           fCmdParser.getHigherEventBound() != -1 &&
           fCmdParser.getHigherEventBound() < numberOfEvents;
}

void JPetAnalysisRunner::manageProgressBar(long long done, long long end)
{
    if (fIsProgressBarEnabled) {
        printf("\r[%6.4f%% %%]", setProgressBar(done, end));
    }
}

float JPetAnalysisRunner::setProgressBar(int currentEventNumber, int numberOfEvents)
{
    return ( ((float)currentEventNumber) / numberOfEvents ) * 100;
}

void JPetAnalysisRunner::ProcessFromCmdLineArgs(int fileIndex)
{

    if (fCmdParser.isRunNumberSet()) { /// we should connect to the database
        fParamManager.getParametersFromDatabase(fCmdParser.getRunNumber()); /// @todo some error handling
    }
    if (fCmdParser.isProgressBarSet()) {
        fIsProgressBarEnabled = true;
    }
    if (fCmdParser.IsFileTypeSet()) {
        if (fCmdParser.getFileType() == "scope") {
            JPetScopeReader* module = new JPetScopeReader("JPetScopeReader", "Process Oscilloscope ASCII data into JPetRecoSignal structures.");
            module->setFileName(getInputFileNames()[fileIndex].c_str());
            fTasks.push_front(module);
        } else if (fCmdParser.getFileType() == "hld") {
            fUnpacker.setParams(fCmdParser.getFileNames()[fileIndex].c_str());
            UnpackFile();
        }
    }
}

std::vector<std::string> JPetAnalysisRunner::getInputFileNames() const
{
    std::vector<std::string> fileNames = fCmdParser.getFileNames();
    std::vector<std::string> parsedNames;
    for(int i = 0; i < fileNames.size(); i++){
        std::string name = fileNames[i].c_str();
        // strip suffixes of type .tslot.* and .phys.*
        int pos = name.find(".tslot");
        if ( pos == std::string::npos ) {
            pos = name.find(".phys");
        }
        if ( pos == std::string::npos ) {
            pos = name.find(".hld");
        }
        if ( pos == std::string::npos ) {
            pos = name.find(".root");
        }
        if ( pos != std::string::npos ) {
            name.erase( pos );
        }

        parsedNames.push_back(name);
    }
    return parsedNames;
}

std::string JPetAnalysisRunner::getBaseInputFileName(string name) const
{
    int pos = name.find(".");
    if ( pos != std::string::npos ) {
        name.erase( pos );
    }
    return name;
}

JPetAnalysisRunner::~JPetAnalysisRunner()
{
    for(auto task : fTasks)
    {
        delete task;
    }
}
