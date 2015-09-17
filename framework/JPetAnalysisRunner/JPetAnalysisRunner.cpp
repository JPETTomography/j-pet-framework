//
// Created by karol on 12.05.15.
//

#include "JPetAnalysisRunner.h"
#include <cassert>
#include "../JPetScopeReader/JPetScopeReader.h"

JPetAnalysisRunner::JPetAnalysisRunner(TaskGeneratorChain* taskGeneratorChain, int processedFileId, JPetCmdParser& cmdParser) :
  ftaskGeneratorChain(taskGeneratorChain),
  fProcessedFile(processedFileId),
  fCmdParser(cmdParser),
  fIsProgressBarEnabled(cmdParser.isProgressBarSet())
{
  if (taskGeneratorChain) {
    for (auto taskGenerator : *ftaskGeneratorChain) {
      auto task = taskGenerator();
      //task->setParamManager(&fParamManager);
      fTasks.push_back(task);
    }
  } else {
    ERROR("taskGeneratorChain is null while constructing JPetAnalysisRunner");
  }
}

void JPetAnalysisRunner::process()
{
  std::cout <<"processing in Analysis Runner" <<std::endl;
  std::vector<std::string> fileNames = getFullInputFileNames();
  ProcessFromCmdLineArgs(fProcessedFile);
  for (currentTask = fTasks.begin(); currentTask != fTasks.end(); currentTask++) {
    std::map<std::string,std::string> opts;
    opts["inputFile"]=fileNames[fProcessedFile];
    opts["outputFile"]=fileNames[fProcessedFile];
    //setEventBounds(kFirstEvent, kLastEvent, kNevent);
    opts["firstEvent"]="100";
    opts["lastEvent"]="200";
    opts["progressBar"]="true";
    (*currentTask)->init(opts);
    (*currentTask)->exec();
    (*currentTask)->terminate();
  }
}

void* JPetAnalysisRunner::processProxy(void* runner)
{
  static_cast<JPetAnalysisRunner*>(runner)->process();
}

TThread* JPetAnalysisRunner::run()
{
  //if (!ftaskGeneratorChain) {
    //ERROR("no task generator chain set");
    //return 0;
  //}
  TThread* thread = new TThread(to_string(fProcessedFile).c_str(), processProxy, (void*)this);
  assert(thread);
  thread->Run();
  return thread;
}


//void JPetAnalysisRunner::setEventBounds(long long& begin, long long& end, long long& eventCount)
//{
  //if (userBoundsAreCorrect(eventCount) && currentTask == fTasks.begin()) {
    //begin = fCmdParser.getLowerEventBound();
    //end = fCmdParser.getHigherEventBound();
    //eventCount = end - begin + 1;
  //} else {
    //eventCount = (*currentTask)->getEventNb();
    //begin = 0;
    //end = eventCount - 1;
  //}
//}


//bool JPetAnalysisRunner::userBoundsAreCorrect(long long numberOfEvents)
//{
  //return fCmdParser.getLowerEventBound() != -1 &&
         //fCmdParser.getHigherEventBound() != -1 &&
         //fCmdParser.getHigherEventBound() < numberOfEvents;
//}


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
      module->setFileName(getFullInputFileNames()[fileIndex].c_str());
      //fTasks.push_front(module);
    } else if (fCmdParser.getFileType() == "hld") {
      fUnpacker.setParams(fCmdParser.getFileNames()[fileIndex].c_str());
      UnpackFile();
    }
  }
}

std::vector<std::string> JPetAnalysisRunner::getFullInputFileNames() const 
{
  return fCmdParser.getFileNames();
}

/**
 * @brief Get Stripped Input File name stripped off the extension and the suffixes like .tslot.* or .phys.*
 *
 * Example: if the file given on command line was ../file.phys.hit.root, this method will return ../file
 */

std::vector<std::string> JPetAnalysisRunner::getStrippedInputFileNames(const std::vector<std::string>& fileNames) const
{
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
  for (auto task : fTasks) {
    delete task;
  }
}
